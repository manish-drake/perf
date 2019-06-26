#ifndef PING_H
#define PING_H
#include <string>
#include "request.h"
#include "reply.h"

using std::string;
class Ping
{
    
Request *m_request;
Reply *m_reply;
public:
    Ping();
    ~Ping();
    void Create(Request *request, Reply *reply);
    void Start();
};
#endif //PING_H