#include "request_binary.h"
#include <cstring>
Request_Binary::Request_Binary()
{
}

void Request_Binary::create(char *msg, int &sz) 
{
    UATStart *uatStart = new UATStart;
    uatStart->address = 0756;
    uatStart->Mode = 13;
    sz = sizeof(UATStart);
    msg = (char*)malloc(sz);
    memcpy(msg, uatStart, sizeof(UATStart));
}
void Request_Binary::process(const std::string &msg) 
{
    UATStart uatStart;
    size_t sz = sizeof(UATStart);
    memcpy(&uatStart, msg.c_str(), sz);
}

Request_Binary::~Request_Binary()
{
}
