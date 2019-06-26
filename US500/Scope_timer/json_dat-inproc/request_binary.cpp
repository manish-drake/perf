#include "request_binary.h"
#include <cstring>

Request_Binary::Request_Binary()
{
}

void Request_Binary::create(char **reqMsg, int &reqSz) 
{
    UATStart uatStart;
    reqSz = sizeof(UATStart);
    *reqMsg = (char*)malloc(reqSz);
    memcpy(*reqMsg, &uatStart, sizeof(UATStart));
}

void Request_Binary::process(char *reqMsg, int reqSz) 
{
    UATStart uatStart;
    size_t sz = sizeof(UATStart);
    memcpy(&uatStart, reqMsg, sz);
}

Request_Binary::~Request_Binary()
{
}