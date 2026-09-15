..\..\ASN.1.GITSN.COMPILER\ASN1COMPILER.exe -g -s -p -B -PU -PA iso14827-1.asn iso14827-2.asn
del ..\iso14827_?.c
del ..\iso14827_?.h
move iso14827_?.c ..
move iso14827_?.h ..
pause