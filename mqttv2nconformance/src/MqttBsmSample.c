/* BSM samples use the adopted J2735_20240923_KSR1600 schema. */
#include <GitsnAsnUtil.h>

_gitsn_get_uper_encode_declare(MessageFrame);

Dz1Binary *MqttBsm_sample(unsigned char *template_bytes, size_t size,
                         unsigned sequence, unsigned sec_mark, unsigned vehicle_id) {
    Dz1Error err = DZ1_ERROR_INITIALIZER;
    Dz1Binary src = {template_bytes, (u32_t)size};
    Dz1Binary *raw = NULL, *encoded = NULL, *result = NULL;
    ASN1WorkSpace ws;
    BasicSafetyMessage bsm;
    MessageFrame frame = {0};
    int id = 0;
    unsigned n;
    if (sequence < 1 || sequence > 1000 || sec_mark > 59999) return NULL;
    n = sequence - 1;
    ASN1_INIT_WS_INFO(&ws);
    raw = GitsnAsnUtil_getValueFromMessageFrame(&src, &id, &err);
    if (!raw || id != 20 || !BasicSafetyMessage_uper_decode(&ws, raw, &bsm, &err)) goto done;
    if (!bsm.coreData || bsm.coreData->id.numbits != 4) goto done;
    bsm.coreData->msgCnt = n % 128;
    bsm.coreData->secMark = sec_mark;
    for (unsigned i = 0; i < 4; ++i)
        bsm.coreData->id.data[i] = (unsigned char)(vehicle_id >> (24 - i * 8));
    bsm.coreData->lat = 370000000 + n * 100;
    bsm.coreData->lon = 1270000000 + n * 100;
    bsm.coreData->elev = 100 + n % 100;
    bsm.coreData->transmission = TransmissionState_forwardGears;
    bsm.coreData->speed = 500 + n % 100;
    bsm.coreData->heading = 7200 + n % 100;
    bsm.coreData->angle = n % 21;
    bsm.coreData->accelSet->lon = 0;
    bsm.coreData->accelSet->lat = 0;
    bsm.coreData->accelSet->vert = 0;
    bsm.coreData->accelSet->yaw = 0;
    bsm.coreData->brakes->wheelBrakes.data[0] = 0xa0;
    bsm.coreData->brakes->traction = TractionControlStatus_on;
    bsm.coreData->brakes->abs = AntiLockBrakeStatus_on;
    bsm.coreData->brakes->scs = StabilityControlStatus_on;
    bsm.coreData->brakes->brakeBoost = BrakeBoostApplied_on;
    bsm.coreData->brakes->auxBrakes = AuxiliaryBrakeStatus_on;
    bsm.coreData->size->width = 400;
    bsm.coreData->size->length = 300;
    encoded = BasicSafetyMessage_get_uper_encoded(&bsm, &err);
    if (!encoded) goto done;
    frame.messageId = 20;
    frame.value.numocts = encoded->size;
    frame.value.data = encoded->data;
    result = MessageFrame_get_uper_encoded(&frame, &err);
done:
    Dz1Binary_del(encoded);
    Dz1Binary_del(raw);
    ASN1_INIT_WS_INFO_cancel(&ws);
    return result;
}
