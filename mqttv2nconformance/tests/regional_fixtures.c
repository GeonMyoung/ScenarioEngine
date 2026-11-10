/* Test-only fixture producer, linked with the unchanged legacy encoder. */
#include <GitsnAsnUtil.h>
#include <dz1_thread.h>
#include <dz1_cleanup.h>
#include <stdio.h>

extern Dz1Binary *DatexPayload_timRegionalFixture(unsigned char *, size_t, unsigned);

static Dz1Binary *edit_tim(Dz1Binary *src, unsigned edit) {
    Dz1Error e = DZ1_ERROR_INITIALIZER;
    ASN1WorkSpace ws, encoded;
    ASN1_INIT_WS_INFO(&ws); ASN1_INIT_WS_INFO(&encoded);
    int id = 0;
    Dz1Binary *raw = GitsnAsnUtil_getValueFromMessageFrame(src, &id, &e), *body = NULL, *result = NULL;
    TravelerInformation tim;
    if (!raw || id != 31 || !TravelerInformation_uper_decode(&ws, raw, &tim, &e)) goto done;
    if (edit == 0) tim.DEF_TravelerInformation_packetID = 0;
    if (edit == 1) {
        for (unsigned i = 1; i <= tim.dataFrames.count; ++i) {
            TravelerDataFrame *frame = ASN1_Get_Node_Index(&tim.dataFrames, i);
            frame->DEF_TravelerDataFrame_startYear = 0;
        }
    }
    if (edit >= 2) {
        RegionalExtension *ext;
        if (edit == 2) ext = ASN1_Get_Node_Index(&tim.regional, 1);
        else {
            TravelerDataFrame *frame = ASN1_Get_Node_Index(&tim.dataFrames, 1);
            GeographicalPath *path = ASN1_Get_Node_Index(&frame->regions, 1);
            ext = ASN1_Get_Node_Index(&path->regional, 1);
        }
        unsigned length = ext->regExtValue.numocts;
        unsigned char *extra = mpool_malloc(ws.Pmemory, length + 1);
        memcpy(extra, ext->regExtValue.data, length); extra[length] = 0;
        ext->regExtValue.data = extra; ext->regExtValue.numocts = length + 1;
    }
    body = TravelerInformation_get_uper_encoded(&tim, &e);
    if (body) {
        MessageFrame frame = {0}; frame.messageId = 31;
        frame.value.data = body->data; frame.value.numocts = body->size;
        if (ASN1_PER_UNAlign_Enc_MessageFrame(&encoded, &frame) >= 0)
            result = Dz1Binary_new(ASN1WorkSpace_getEncodePtr(&encoded),
                                   ASN1WorkSpace_getEncodedSize(&encoded, Dz1Asn1Codec_uper), &e);
    }
done:
    Dz1Binary_del(body); Dz1Binary_del(raw);
    ASN1_INIT_WS_INFO_cancel(&encoded); ASN1_INIT_WS_INFO_cancel(&ws);
    return result;
}

static int emit(FILE *out, const char *name, int valid, Dz1Binary *value, int comma) {
    if (!value) return 0;
    fprintf(out, "%s{\"name\":\"%s\",\"expected\":%s,\"hex\":\"", comma ? "," : "", name, valid ? "true" : "false");
    for (unsigned i = 0; i < value->size; ++i) fprintf(out, "%02x", value->data[i]);
    fprintf(out, "\"}");
    Dz1Binary_del(value);
    return 1;
}

int main(int argc, char **argv) {
    if (argc != 3) return 1;
    Dz1Cleanup_init(); Dz1Error e = DZ1_ERROR_INITIALIZER; Dz1Thread_init(0, &e);
    FILE *input = fopen(argv[1], "rb"), *output = fopen(argv[2], "wb");
    if (!input || !output) return 1;
    unsigned char seed[4096]; size_t size = fread(seed, 1, sizeof(seed), input); fclose(input);
    const char *names[] = {"tim-kor-valid", "tim-kor-traveler-cut", "tim-kor-path-cut", "tim-kor-both-cut", "tim-other-region-opaque"};
    fprintf(output, "[");
    for (unsigned fault = 0; fault <= 4; ++fault)
        if (!emit(output, names[fault], fault == 0 || fault == 4,
                  DatexPayload_timRegionalFixture(seed, size, fault), fault != 0)) return 2;
    Dz1Binary original = {seed, (u32_t)size};
    if (!emit(output, "general-tim-without-packetID", 1, edit_tim(&original, 0), 1) ||
        !emit(output, "general-tim-without-startYear", 1, edit_tim(&original, 1), 1)) return 2;
    Dz1Binary *regional = DatexPayload_timRegionalFixture(seed, size, 0);
    if (!regional || !emit(output, "tim-kor-traveler-tail", 0, edit_tim(regional, 2), 1) ||
        !emit(output, "tim-kor-path-tail", 0, edit_tim(regional, 3), 1)) return 2;
    Dz1Binary_del(regional);
    fprintf(output, "]\n"); fclose(output);
    return 0;
}
