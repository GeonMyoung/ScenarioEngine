#ifndef DZ1_MFC_HTML_UTIL_H
#define DZ1_MFC_HTML_UTIL_H

#include <dz1_elastic_buf.h>

#include <dz1_mfc.h>
#include <Dz1MfcDefUtil.h>

DZ1_CPPLINK Dz1Str				 Dz1MfcHtmlGetSource(Dz1Str url, Dz1Error *err);
DZ1_CPPLINK Dz1Error			 Dz1MfcHtmlDownload(Dz1Str url, Dz1Str fn);
DZ1_CPPLINK Dz1Error			 Dz1MfcHtmlDownload2(Dz1Str url, Dz1Str path, Dz1Str name);
DZ1_CPPLINK Dz1Error			 Dz1MfcHtmlDownload3(Dz1Str url, Dz1Str path, Dz1Str name, Dz1Str ext);

DZ1_CPPLINK Dz1ElasticBuf		*Dz1MfcHtmlDownloadBuf(Dz1Str url, Dz1Str hdr_opt, Dz1Error *err);
DZ1_CPPLINK Dz1ElasticBuf		*Dz1MfcHtmlDownloadBuf2(Dz1Str url, Dz1MfcProgressInfo *prog, Dz1Error *err);
DZ1_CPPLINK Dz1ElasticBuf		*Dz1MfcHtmlDownloadBuf3(Dz1Str url, Dz1Str _referer, Dz1MfcProgressInfo *prog, Dz1Error *err);

DZ1_CPPLINK Dz1MfcHtmlTag		*Dz1MfcHtmlTag_parse(Dz1Str src, Dz1Str *ret_src, Dz1Error *err);
DZ1_CPPLINK Dz1MfcHtmlTagAttr	*Dz1MfcHtmlTag_getAttr(Dz1MfcHtmlTag *tag, Dz1Str id);

#endif