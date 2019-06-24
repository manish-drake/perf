#ifndef REQUEST_BINARY_H
#define REQUEST_BINARY_H
#include <string>
#include "request.h"
using std::string;
class Request_Binary:public Request
{
protected:
    virtual void create(char **reqMsg, int &reqSz) override;
    virtual void process(char *reqMsg, int reqSz) override;

public:
    Request_Binary();
    ~Request_Binary();
};
#endif //REQUEST_BINARY_H