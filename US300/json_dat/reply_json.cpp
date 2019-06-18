#include "reply_json.h"
Reply_Json::Reply_Json()
{
}
void Reply_Json::process(const std::string &reply) 
{
    CUATADSBSummary uatADSBSummary;
    uatADSBSummary.setMessage(reply);
    UATADSBSummary data;
    parse(uatADSBSummary, data);
}
std::string Reply_Json::create()
{
    CUATADSBSummary uatADSBSummary;
    uatADSBSummary.setCallsign("0735");
    return uatADSBSummary.getMessage();
}

Reply_Json::~Reply_Json()
{
}
