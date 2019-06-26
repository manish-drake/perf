#include "reply.h"
Reply::Reply()
{
}

void Reply::Process(char *repMsg, int repSz)
{
    process(repMsg, repSz);
}
void Reply::Create(char **repMsg, int &repSz)
{
    create(repMsg, repSz);
}
Reply::~Reply()
{
}