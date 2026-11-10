#pragma once
#include "RestMethod.h"
namespace rest {
struct ReviewResult { std::string status,finalVerdict,path; };
ReviewResult completeEvidenceReview(const MethodConfig &,const Result &,std::atomic<bool> &,const Sink &);
}
