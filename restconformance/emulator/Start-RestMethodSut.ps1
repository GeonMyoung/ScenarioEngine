[CmdletBinding()]
param(
 [Parameter(Mandatory)][ValidateSet('SC07','SC11','SC28','SC32','SC11-SMT','SC32-SMT')][string]$Scenario,
 [ValidateSet('normal','empty','absent')][string]$DataState='normal',
 [ValidateRange(0,36000)][int]$Requests=0,
 [string]$Config,
 [string]$OutputDirectory
)
$ErrorActionPreference='Stop'
$restWorkspace=[IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..'))
$restCases=@{SC07='uticServer2center_v1';SC11='microClient2center_v1';SC28='centerClient2utic_v1';SC32='centerServer2micro_v1';'SC11-SMT'='microClient2center_smart_v1';'SC32-SMT'='centerServer2micro_smart_v1'}
if(-not $Config){$Config=Join-Path $restWorkspace ('restconformance\registration\'+$restCases[$Scenario]+'.example.json')}
$restSettings=Get-Content -LiteralPath $Config -Raw | ConvertFrom-Json
$restProvider=$Scenario -in @('SC11','SC28','SC11-SMT')
$restFormat=if($Scenario -in @('SC07','SC28')){'xml'}else{'json'}
$restInformation=if($Scenario -like '*-SMT'){'smart'}else{'vds'}
$restRole=if($restProvider){'provider'}else{'requester'}
$restPort=if($restProvider){([Uri]$restSettings.sut_base_url).Port}else{[int]$restSettings.local_port}
if(-not $OutputDirectory){$OutputDirectory=Join-Path $restWorkspace ('.local\rest-method-sut\'+$Scenario+'-'+(Get-Date -Format 'yyyyMMdd-HHmmss-ffff'))}
$restAbsent=if($restSettings.PSObject.Properties.Name -contains 'no_data_error_status'){$restSettings.no_data_error_status}else{404}
if($Requests -eq 0){$restSelected=@($restSettings.PSObject.Properties | Where-Object {$_.Name -like 'test_*' -and $_.Value -eq $true});$Requests=$restSelected.Count*[int]$restSettings.repetitions;if($Requests -lt 1){throw 'Select test items or specify Requests'}}
$restPriorCredential=$env:REST_TEST_CREDENTIAL
try{
 $env:REST_TEST_CREDENTIAL=if($restFormat -eq 'xml'){$restSettings.api_key}else{$restSettings.bearer_token}
 $restBad=if($restSettings.PSObject.Properties.Name -contains 'bad_request_status'){$restSettings.bad_request_status}else{400}
 $restAuth=if($restSettings.PSObject.Properties.Name -contains 'unauthorized_status'){$restSettings.unauthorized_status}else{401}
 $restEmpty=if($restSettings.PSObject.Properties.Name -contains 'no_data_status'){$restSettings.no_data_status}else{200}
 & python -X utf8 (Join-Path $PSScriptRoot 'rest_method_sut.py') --role $restRole --format $restFormat --information $restInformation --port $restPort --output $OutputDirectory --requests $Requests --data $DataState --bad-request-status $restBad --auth-status $restAuth --empty-status $restEmpty --absence-status $restAbsent
 $restExit=$LASTEXITCODE
}finally{$env:REST_TEST_CREDENTIAL=$restPriorCredential}
exit $restExit
