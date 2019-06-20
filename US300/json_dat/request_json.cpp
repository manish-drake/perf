#include "request_json.h"
#include <cstring>
Request_Json::Request_Json()
{
}

void Request_Json::create(char **reqMsg, int &reqSz) 
{
    CUATStart uatStart;
    uatStart.setAddress(2019);
    std::string strMsg = uatStart.getMessage();
    *reqMsg = strdup(const_cast<char*>(strMsg.c_str()));
    reqSz = strMsg.size();
}
void Request_Json::process(char *reqMsg, int reqSz) 
{
    CUATStart uatStart;
    uatStart.setMessage(reqMsg);
    UATStart data;
    parse(uatStart, data);
}

Request_Json::~Request_Json()
{
}
