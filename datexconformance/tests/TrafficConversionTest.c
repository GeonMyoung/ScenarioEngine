#include <GitsnAsnUtil.h>
#include <dz1_gasn_support.h>

bool_t DatexTravelerFromASN(TravelerInformation *, Gitsn_TravelerInformation *, Dz1Error *);

/* Compare a decoded ASN.1 object with its separately allocated result model.
   Nonzero source values and a second choice exercise the former pointer casts. */
int DatexTrafficConversionRegression(unsigned char *bytes, unsigned size) {
    Dz1Error e = DZ1_ERROR_INITIALIZER;
    Dz1Binary input = {bytes, size}, *raw = NULL;
    ASN1WorkSpace ws;
    TravelerInformation asn;
    Gitsn_TravelerInformation converted;
    Gitsn_TravelerDataFrame **frames = NULL;
    Gitsn_GeographicalPath **regions = NULL;
    Gitsn_NodeXY **nodes = NULL;
    Gitsn_SegmentAttributeXY *disabled = NULL, *enabled = NULL;
    unsigned count = 0;
    int id = 0, result = 0;
    memset(&converted, 0, sizeof(converted));
    ASN1_INIT_WS_INFO(&ws);
    raw = GitsnAsnUtil_getValueFromMessageFrame(&input, &id, &e);
    if (!raw || id != 31 || !TravelerInformation_uper_decode(&ws, raw, &asn, &e)) goto done;
    TravelerDataFrame *sourceFrame = ASN1_Get_Node_Index(&asn.dataFrames, 1);
    if (!sourceFrame) goto done;
    GeographicalPath *sourceRegion = ASN1_Get_Node_Index(&sourceFrame->regions, 1);
    if (!sourceRegion || !sourceRegion->id) goto done;
    sourceRegion->id->region = 731;
    sourceRegion->id->id = 4095;
    NodeXY *sourceNode = ASN1_Get_Node_Index(&sourceRegion->description->elements.path->offset->elements.xy->elements.nodes, 1);
    if (!sourceNode || !sourceNode->attributes) goto done;
    SegmentAttributeXY *sourceDisabled = ASN1_Get_Node_Index(&sourceNode->attributes->disabled, 1);
    SegmentAttributeXY *sourceEnabled = ASN1_Get_Node_Index(&sourceNode->attributes->enabled, 1);
    if (!sourceDisabled || !sourceEnabled) goto done;
    *sourceDisabled = 3;
    *sourceEnabled = 4;
    if (!DatexTravelerFromASN(&asn, &converted, &e)) goto done;
    frames = converted.dataFrames->get_array(converted.dataFrames, &count, &e);
    if (!frames || count != 1) goto done;
    regions = frames[0]->regions->get_array(frames[0]->regions, &count, &e);
    if (!regions || count != 1 || regions[0]->id->region != 731 || regions[0]->id->id != 4095) goto done;
    Gitsn_NodeSetXY *nodeList = regions[0]->description->x.path->offset->x.xy->x.nodes;
    nodes = nodeList->get_array(nodeList, &count, &e);
    if (!nodes || count < 1) goto done;
    disabled = nodes[0]->attributes->disabled->get_array(nodes[0]->attributes->disabled, &count, &e);
    if (!disabled || count != 1 || disabled[0] != 3) goto done;
    enabled = nodes[0]->attributes->enabled->get_array(nodes[0]->attributes->enabled, &count, &e);
    if (!enabled || count != 1 || enabled[0] != 4) goto done;
    Dz1Free(frames); frames = NULL;
    Dz1Free(regions); regions = NULL;
    Dz1Free(nodes); nodes = NULL;
    Dz1Free(disabled); disabled = NULL;
    Dz1Free(enabled); enabled = NULL;
    Gitsn_TravelerInformation_purge(&converted);
    memset(&converted, 0, sizeof(converted));
    RoadSignID sign;
    Position3D position;
    unsigned char view[2] = {0x80, 0x00};
    memset(&sign, 0, sizeof(sign));
    memset(&position, 0, sizeof(position));
    position.lat = 373679200;
    position.lon = 1267232020;
    sign.position = &position;
    sign.viewAngle.data = view;
    sign.viewAngle.numbits = 16;
    sourceFrame->msgId->M = DEF_TravelerDataFrame_msgId_roadSignID;
    sourceFrame->msgId->elements.roadSignID = &sign;
    if (!DatexTravelerFromASN(&asn, &converted, &e)) goto done;
    frames = converted.dataFrames->get_array(converted.dataFrames, &count, &e);
    if (!frames || count != 1 || frames[0]->msgId->present != Gitsn_TravelerDataFrame_msgIdPresent_roadSignID) goto done;
    if (frames[0]->msgId->x.roadSignID->position->lat != position.lat ||
        frames[0]->msgId->x.roadSignID->position->lon != position.lon) goto done;
    result = 1;
done:
    if (frames) Dz1Free(frames);
    if (regions) Dz1Free(regions);
    if (nodes) Dz1Free(nodes);
    if (disabled) Dz1Free(disabled);
    if (enabled) Dz1Free(enabled);
    Gitsn_TravelerInformation_purge(&converted);
    Dz1Binary_del(raw);
    ASN1_INIT_WS_INFO_cancel(&ws);
    return result;
}

#include <TechnicalRegulation1MsgStructAPI.h>
int DatexSignalEnvelopeRegression(unsigned char *bytes, unsigned size, unsigned expected) {
    Dz1Error e = DZ1_ERROR_INITIALIZER;
    Dz1Binary input = {bytes, size};
    Iso14827TestMsgStructAPI *api = Iso14827TestMsgSet_findAPI(TechnicalRegulation1_PolicePrj4C2CMsgSet, "1.0.14827.1.1.0", NULL);
    void *decoded = api->struct_decode(&input, Dz1Asn1Codec_ber, &e);
    if (!decoded) return 0;
    Dz1ExtentionCommPDUResponse *list = decoded;
    unsigned count = 0;
    Dz1ExtentionCommPDU **items = list->get_array(list, &count, &e);
    int valid = items && count == 1 && items[0]->aid == 2 && items[0]->payloadType && *items[0]->payloadType == 1;
    if (valid) {
        Dz1Binary payload = {items[0]->payload->data, items[0]->payload->size};
        int id = 0;
        Dz1Binary *body = GitsnAsnUtil_getValueFromMessageFrame(&payload, &id, &e);
        valid = body && id == expected;
        Dz1Binary_del(body);
    }
    if (items) Dz1Free(items);
    api->struct_delAndSetNull(&decoded);
    return valid;
}
