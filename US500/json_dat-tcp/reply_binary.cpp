#include "reply_binary.h"
#include <cstring>

Reply_Binary::Reply_Binary()
{
}
void Reply_Binary::process(char *repMsg, int repSz)
{
    UATADSBSummary uatADSBSummary;
    size_t sz = sizeof(UATADSBSummary);
    memcpy(&uatADSBSummary, repMsg, sz);
}
void Reply_Binary::create(char **repMsg, int &repSz)
{
    UATADSBSummary uatADSBSummary;
    repSz = sizeof(UATADSBSummary);
    *repMsg = (char*)malloc(repSz);
    memcpy(*repMsg, &uatADSBSummary, sizeof(UATADSBSummary));
}

Reply_Binary::~Reply_Binary()
{
}