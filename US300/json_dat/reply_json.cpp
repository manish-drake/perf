#include "reply_json.h"
#include <cstring>
Reply_Json::Reply_Json()
{
}
void Reply_Json::process(char *repMsg, int &repSz) 
{
    CUATADSBSummary uatADSBSummary;
    uatADSBSummary.setMessage(repMsg);
    UATADSBSummary data;
    parse(uatADSBSummary, data);
}
void Reply_Json::create(char **repMsg, int &repSz)
{
    CUATADSBSummary uatADSBSummary;
    uatADSBSummary.setCallsign("0735");
    std::string data = uatADSBSummary.getMessage();
    const char *cdata = data.c_str();
    repSz = data.size();
    *repMsg = strdup(const_cast<char*>(cdata));
}

Reply_Json::~Reply_Json()
{
}
