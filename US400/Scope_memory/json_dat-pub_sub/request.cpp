#include "request.h"
Request::Request()
{
}

void Request::Create(char *msg, int &sz)
{
    create(msg, sz);
}

void Request::Process(const std::string &msg)
{
    process(msg);
}

Request::~Request()
{

}
