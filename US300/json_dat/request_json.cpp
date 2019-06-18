#include "request_json.h"
#include <cstring>
Request_Json::Request_Json()
{
}

void Request_Json::create(char *msg, int &sz) 
{
    CUATStart uatStart;
    uatStart.setAddress(2019);
    std::string strMsg = uatStart.getMessage();
    strcpy(msg, strMsg.c_str());
    sz = strMsg.size();
}
void Request_Json::process(const std::string &msg) 
{
    CUATStart uatStart;
    uatStart.setMessage(msg);
    UATStart data;
    parse(uatStart, data);
}

Request_Json::~Request_Json()
{
}
