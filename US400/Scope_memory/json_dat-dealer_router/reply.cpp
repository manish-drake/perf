#include "reply.h"
Reply::Reply()
{
}

void Reply::Process(const std::string &reply)
{
    process(reply);
}
std::string Reply::Create()
{
    return create();
}
Reply::~Reply()
{
}