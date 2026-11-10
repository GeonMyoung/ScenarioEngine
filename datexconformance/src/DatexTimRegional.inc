/* Decode the two KOR open types used by P3 Annex II. No traffic decision rules. */
_gitsn_asn_util_decode_eam(TravelerInformation_KOR);
_gitsn_asn_util_decode_eam(GeographicalPath_KOR);
_gitsn_get_uper_encode_declare(TravelerInformation_KOR);
_gitsn_get_uper_encode_declare(GeographicalPath_KOR);

typedef struct TimRegionalCounts {
    unsigned traveler, path, opaque, omitted;
    char values[8192]; size_t used;
} TimRegionalCounts;
static int regional_quoted(char *out, size_t capacity, size_t *used, UTF8Str *value) {
    if (!value || (!value->asnstring && value->nchar) || value->nchar > 512) return 0;
    if (!append_json(out, capacity, used, "\"")) return 0;
    for (unsigned i = 0; i < value->nchar; ++i) {
        unsigned char c = value->asnstring[i];
        if (c == '"' || c == '\\') { if (!append_json(out, capacity, used, "\\%c", c)) return 0; }
        else if (c < 32) { if (!append_json(out, capacity, used, "\\u%04x", c)) return 0; }
        else if (!append_json(out, capacity, used, "%c", c)) return 0;
    }
    return append_json(out, capacity, used, "\"");
}
static void regional_add(TimRegionalCounts *counts, const char *entry, int valid) {
    size_t n = strlen(entry);
    if (!valid || counts->used + n + 2 >= sizeof(counts->values)) { ++counts->omitted; return; }
    if (counts->used) counts->values[counts->used++] = ',';
    memcpy(counts->values + counts->used, entry, n + 1); counts->used += n;
}
static void regional_path_values(GeographicalPath_KOR *path, TimRegionalCounts *counts) {
    for (unsigned i = 1; i <= path->regions.count; ++i) {
        RegionDescribedByID_KOR *region = ASN1_Get_Node_Index(&path->regions, i);
        char text[1536] = {0}; size_t used = 0; int valid = region != NULL;
        if (!region) { ++counts->omitted; continue; }
        valid &= append_json(text, sizeof(text), &used, "{\"kind\":\"path\",\"type\":%llu,\"value\":", (unsigned long long)region->M);
        switch (region->M) {
        case DEF_RegionDescribedByID_KOR_linkID: valid &= regional_quoted(text,sizeof(text),&used,&region->elements.linkID); break;
        case DEF_RegionDescribedByID_KOR_areaID: valid &= regional_quoted(text,sizeof(text),&used,&region->elements.areaID); break;
        case DEF_RegionDescribedByID_KOR_laneID: valid &= append_json(text,sizeof(text),&used,"%lld",(long long)region->elements.laneID); break;
        case DEF_RegionDescribedByID_KOR_segmentID: valid &= append_json(text,sizeof(text),&used,"%lld",(long long)region->elements.segmentID); break;
        case DEF_RegionDescribedByID_KOR_detectLane: valid &= append_json(text,sizeof(text),&used,"%d",(int)region->elements.detectLane); break;
        case DEF_RegionDescribedByID_KOR_intersections: valid &= append_json(text,sizeof(text),&used,"%lld",(long long)region->elements.intersections); break;
        default: valid = 0;
        }
        valid &= append_json(text, sizeof(text), &used, "}"); regional_add(counts,text,valid);
    }
}
static void regional_traveler_values(TravelerInformation_KOR *tim, TimRegionalCounts *counts) {
    if (!tim->DEF_TravelerInformation_KOR_additionalInfo) return;
    for (unsigned i = 1; i <= tim->additionalInfo.count; ++i) {
        TravelerDataFrameAdditionalInformation_KOR *info = ASN1_Get_Node_Index(&tim->additionalInfo, i);
        if (!info || !info->DEF_TravelerDataFrameAdditionalInformation_KOR_events || !info->events || !info->events->DEF_EventOrSvcInfo_KOR_text) continue;
        for (unsigned j = 1; j <= info->events->text.count; ++j) {
            UTF8Str *value = ASN1_Get_Node_Index(&info->events->text, j);
            char text[1536] = {0}; size_t used = 0;
            int valid = append_json(text,sizeof(text),&used,"{\"kind\":\"text\",\"frameIndex\":%lld,\"value\":",(long long)info->dataFrameIndex);
            valid &= regional_quoted(text,sizeof(text),&used,value);
            valid &= append_json(text,sizeof(text),&used,"}"); regional_add(counts,text,valid);
        }
    }
}

static int tim_regional_list(ASN1List *list, int path, TimRegionalCounts *counts) {
    for (unsigned i = 1; i <= list->count; ++i) {
        RegionalExtension *ext = ASN1_Get_Node_Index(list, i);
        if (!ext) return 0;
        if (ext->regionId != 4) { ++counts->opaque; continue; }
        if (!ext->regExtValue.data || !ext->regExtValue.numocts) return 0;
        ASN1WorkSpace ws;
        ASN1_INIT_WS_INFO(&ws);
        Dz1Error e = DZ1_ERROR_INITIALIZER;
        Dz1Binary input = {ext->regExtValue.data, ext->regExtValue.numocts};
        int valid;
        if (path) {
            GeographicalPath_KOR v;
            valid = GeographicalPath_KOR_uper_decode(&ws, &input, &v, &e);
            if (valid && !e.code) regional_path_values(&v, counts);
        } else {
            TravelerInformation_KOR v;
            valid = TravelerInformation_KOR_uper_decode(&ws, &input, &v, &e);
            if (valid && !e.code) regional_traveler_values(&v, counts);
        }
        /* Some legacy primitives consume zero-filled workspace bytes past the
           supplied open type. A successful return must also fit its length. */
        size_t consumed = (size_t)(ws.buffer.current - ws.buffer.data) * 8 + (8 - ws.buffer.bitOffset);
        if (ws.buffer.bitOffset > 8 || (consumed + 7) / 8 != input.size) valid = 0;
        ASN1_INIT_WS_INFO_cancel(&ws);
        if (!valid || e.code) return 0;
        if (path) ++counts->path; else ++counts->traveler;
    }
    return 1;
}
static int tim_regional(TravelerInformation *tim, TimRegionalCounts *counts) {
    memset(counts, 0, sizeof(*counts));
    if (tim->DEF_TravelerInformation_regional && !tim_regional_list(&tim->regional, 0, counts)) return 0;
    for (unsigned i = 1; i <= tim->dataFrames.count; ++i) {
        TravelerDataFrame *frame = ASN1_Get_Node_Index(&tim->dataFrames, i);
        if (!frame) return 0;
        for (unsigned j = 1; j <= frame->regions.count; ++j) {
            GeographicalPath *path = ASN1_Get_Node_Index(&frame->regions, j);
            if (!path || (path->DEF_GeographicalPath_regional && !tim_regional_list(&path->regional, 1, counts))) return 0;
        }
    }
    return 1;
}
static int tim_regional_from_payload(unsigned char *bytes, size_t size, TimRegionalCounts *counts) {
    if (!bytes || !size || size > UINT32_MAX) return 0;
    Dz1Error e = DZ1_ERROR_INITIALIZER;
    Dz1Binary input = {bytes, (u32_t)size}, *raw = NULL;
    ASN1WorkSpace ws;
    ASN1_INIT_WS_INFO(&ws);
    TravelerInformation tim;
    int id = 0, valid = 0;
    raw = GitsnAsnUtil_getValueFromMessageFrame(&input, &id, &e);
    if (raw && id == 31 && TravelerInformation_uper_decode(&ws, raw, &tim, &e)) valid = tim_regional(&tim, counts);
    Dz1Binary_del(raw);
    ASN1_INIT_WS_INFO_cancel(&ws);
    return valid;
}
Dz1Binary *DatexPayload_timRegionalSummary(unsigned char *bytes, size_t size) {
    TimRegionalCounts counts;
    if (!tim_regional_from_payload(bytes, size, &counts)) return NULL;
    char text[8600];
    int n = snprintf(text, sizeof(text), "{\"travelerInformationKor\":%u,\"geographicalPathKor\":%u,\"opaqueOtherRegions\":%u,\"values\":[%s],\"summaryOmitted\":%u}", counts.traveler, counts.path, counts.opaque, counts.values, counts.omitted);
    Dz1Error e = DZ1_ERROR_INITIALIZER;
    return n > 0 && (size_t)n < sizeof(text) ? Dz1Binary_new((unsigned char *)text, n, &e) : NULL;
}

/* Fixture variants: normal, truncated traveler/path open type, both, other region.
   The outer TIM is re-encoded correctly in every variant. */
Dz1Binary *DatexPayload_timRegionalFixture(unsigned char *bytes, size_t size, unsigned fault) {
    if (!bytes || !size || size > UINT32_MAX || fault > 4) return NULL;
    ASN1WorkSpace ws, encoded;
    ASN1_INIT_WS_INFO(&ws); ASN1_INIT_WS_INFO(&encoded);
    Dz1Error e = DZ1_ERROR_INITIALIZER;
    Dz1Binary input = {bytes, (u32_t)size}, *raw = NULL, *traw = NULL, *praw = NULL, *body = NULL, *result = NULL;
    TravelerInformation tim;
    int id = 0;
    raw = GitsnAsnUtil_getValueFromMessageFrame(&input, &id, &e);
    if (!raw || id != 31 || !TravelerInformation_uper_decode(&ws, raw, &tim, &e)) goto regional_fixture_done;
    TravelerDataFrame *frame = ASN1_Get_Node_Index(&tim.dataFrames, 1);
    GeographicalPath *path = frame ? ASN1_Get_Node_Index(&frame->regions, 1) : NULL;
    if (!path) goto regional_fixture_done;
    TravelerInformation_KOR tk = {0};
    TravelerDataFrameAdditionalInformation_KOR info = {0};
    EventOrSvcInfo_KOR event = {0};
    UTF8Str text = {8, (unsigned char *)"SPEED 50"};
    tk.DEF_TravelerInformation_KOR_additionalInfo = 1;
    info.dataFrameIndex = 1;
    info.DEF_TravelerDataFrameAdditionalInformation_KOR_events = 1; info.events = &event;
    event.DEF_EventOrSvcInfo_KOR_text = 1;
    if (ASN1_Creat_Init_List(&ws, &tk.additionalInfo) < 0 || ASN1_Insert_Node(&ws, &tk.additionalInfo, &info) < 0 ||
        ASN1_Creat_Init_List(&ws, &event.text) < 0 || ASN1_Insert_Node(&ws, &event.text, &text) < 0) goto regional_fixture_done;
    GeographicalPath_KOR pk = {0};
    RegionDescribedByID_KOR area = {0};
    area.M = DEF_RegionDescribedByID_KOR_linkID;
    area.elements.linkID.nchar = 11; area.elements.linkID.asnstring = (unsigned char *)"BeltId_0001";
    if (ASN1_Creat_Init_List(&ws, &pk.regions) < 0 || ASN1_Insert_Node(&ws, &pk.regions, &area) < 0) goto regional_fixture_done;
    traw = TravelerInformation_KOR_get_uper_encoded(&tk, &e);
    praw = GeographicalPath_KOR_get_uper_encoded(&pk, &e);
    if (!traw || !praw || traw->size < 2 || praw->size < 2) goto regional_fixture_done;
    RegionalExtension te = {0}, pe = {0};
    te.regionId = pe.regionId = fault == 4 ? 9 : 4;
    te.regExtValue.data = traw->data; te.regExtValue.numocts = (fault == 1 || fault == 3) ? 1 : traw->size;
    pe.regExtValue.data = praw->data; pe.regExtValue.numocts = (fault == 2 || fault == 3) ? 1 : praw->size;
    tim.DEF_TravelerInformation_regional = 1; path->DEF_GeographicalPath_regional = 1;
    if (ASN1_Creat_Init_List(&ws, &tim.regional) < 0 || ASN1_Insert_Node(&ws, &tim.regional, &te) < 0 ||
        ASN1_Creat_Init_List(&ws, &path->regional) < 0 || ASN1_Insert_Node(&ws, &path->regional, &pe) < 0) goto regional_fixture_done;
    body = TravelerInformation_get_uper_encoded(&tim, &e);
    if (!body) goto regional_fixture_done;
    MessageFrame message = {0}; message.messageId = 31;
    message.value.data = body->data; message.value.numocts = body->size;
    if (ASN1_PER_UNAlign_Enc_MessageFrame(&encoded, &message) < 0) goto regional_fixture_done;
    result = Dz1Binary_new(ASN1WorkSpace_getEncodePtr(&encoded), ASN1WorkSpace_getEncodedSize(&encoded, Dz1Asn1Codec_uper), &e);
regional_fixture_done:
    Dz1Binary_del(body); Dz1Binary_del(traw); Dz1Binary_del(praw); Dz1Binary_del(raw);
    ASN1_INIT_WS_INFO_cancel(&encoded); ASN1_INIT_WS_INFO_cancel(&ws);
    return result;
}
