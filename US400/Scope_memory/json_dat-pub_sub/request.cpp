#include "request.h"
Request::Request()
{
}

void Request::Create(char **reqMsg, int &reqSz)
{
    create(reqMsg, reqSz);
}

void Request::Process(char *reqMsg, int reqSz)
{
    process(reqMsg, reqSz);
}

Request::~Request()
{

}
