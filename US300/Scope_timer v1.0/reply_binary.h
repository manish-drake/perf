#ifndef REPLY_BINARY_H
#define REPLY_BINARY_H
#include <string>
#include "reply.h"
using std::string;
class Reply_Binary: public Reply
{
protected:
    virtual void process(char *repMsg, int repSz) override;
    virtual void create(char **repMsg, int &repSz) override;

public:
    Reply_Binary();
    ~Reply_Binary();
};
#endif //REPLY_BINARY_H