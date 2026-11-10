"""Prepare an isolated test-only VS project using the existing codec references."""
import argparse
import re
import xml.etree.ElementTree as ET
from pathlib import Path

p = argparse.ArgumentParser()
p.add_argument('--output', required=True)
a = p.parse_args()
root = Path(__file__).resolve().parents[2]
out = Path(a.output).resolve()
out.mkdir(parents=True, exist_ok=True)
original = root / 'mqttv2nconformance/project/vs2022/MqttPayload.vcxproj'
ns = '{http://schemas.microsoft.com/developer/msbuild/2003}'
ET.register_namespace('', ns[1:-1])
tree = ET.parse(original)
project = tree.getroot()
for node in project.iter():
    if node.tag == ns + 'ProjectReference':
        node.set('Include', str((original.parent / node.get('Include')).resolve()))
    if node.tag == ns + 'AdditionalIncludeDirectories':
        node.text = ';'.join(str((original.parent / s).resolve()) if s.startswith('..') else s
                             for s in node.text.split(';'))
    if node.tag == ns + 'OutDir':
        node.text = str(out / 'bin') + '\\'
    if node.tag == ns + 'IntDir':
        node.text = str(out / 'obj') + '\\'
    if node.tag == ns + 'ProjectGuid':
        node.text = '{B2A6F1E5-40F3-46C0-BE14-2973EA7D00F1}'
for group in project.findall(ns + 'ItemGroup'):
    for item in list(group):
        if item.tag == ns + 'ClCompile':
            group.remove(item)
group = ET.SubElement(project, ns + 'ItemGroup')
ET.SubElement(group, ns + 'ClCompile', Include=str(root / 'mqttv2nconformance/tests/regional_fixtures.c'))
tree.write(out / 'MqttRegionalFixtures.vcxproj', encoding='utf-8', xml_declaration=True)
samples = (root / 'datexconformance/src/DatexSamples.h').read_text()
tim = re.search(r'unsigned char tim\[\] = \{([^}]+)', samples).group(1)
(out / 'tim.bin').write_bytes(bytes(int(h, 16) for h in re.findall(r'0x([0-9a-fA-F]+)', tim)))
print(out / 'MqttRegionalFixtures.vcxproj')
