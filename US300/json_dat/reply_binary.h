#ifndef REPLY_BINARY_H
#define REPLY_BINARY_H
#include <string>
#include "reply.h"

using std::string;
class Reply_Binary : public Reply
{

protected:
    virtual void process(const std::string &reply) override;
    virtual std::string create() override;

public:
    Reply_Binary();
    ~Reply_Binary();
};
#endif //REPLY_BINARY_H