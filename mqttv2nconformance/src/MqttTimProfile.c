/* MQTT-only TIM presence metadata. Does not change the shared ASN.1 schema. */
#include <GitsnAsnUtil.h>
#include <stdio.h>

Dz1Binary *MqttTim_profile(unsigned char *bytes, size_t size) {
    Dz1Error e = DZ1_ERROR_INITIALIZER;
    Dz1Binary input = {bytes,(u32_t)size}, *raw = NULL, *out = NULL;
    ASN1WorkSpace ws;
    TravelerInformation v;
    int id = 0, n;
    char text[1024], packet[19] = {0};
    ASN1_INIT_WS_INFO(&ws);
    raw = GitsnAsnUtil_getValueFromMessageFrame(&input,&id,&e);
    if (!raw || id != 31 || !TravelerInformation_uper_decode(&ws,raw,&v,&e)) goto done;
    if (v.DEF_TravelerInformation_packetID && v.packetID.numbits == 9)
        for (unsigned i=0;i<9;++i) snprintf(packet+i*2,3,"%02x",v.packetID.data[i]);
    TravelerDataFrame *frame = v.dataFrames.count == 1 ? ASN1_Get_Node_Index(&v.dataFrames,1) : NULL;
    n=snprintf(text,sizeof(text),"{\"packetIdPresent\":%s,\"packetIdHex\":\"%s\",\"frameCount\":%u,\"startYearPresent\":%s,\"regionCount\":%u}",
        v.DEF_TravelerInformation_packetID?"true":"false",packet,(unsigned)v.dataFrames.count,
        frame&&frame->DEF_TravelerDataFrame_startYear?"true":"false",frame?(unsigned)frame->regions.count:0);
    if(n>0 && n<sizeof(text))out=Dz1Binary_new((unsigned char*)text,n,&e);
done:
    Dz1Binary_del(raw);ASN1_INIT_WS_INFO_cancel(&ws);return out;
}
