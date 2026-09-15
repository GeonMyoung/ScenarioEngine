..\..\ASN.1.GITSN.COMPILER2\ASN.1.COMPILER2.exe iso14827-1.asn iso14827-2.asn
del ..\iso14827_?.c
del ..\iso14827_?.h
move iso14827_?.c ..
move iso14827_?.h ..
pause