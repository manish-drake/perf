#ifndef PONG_H
#define PONG_H
#include <string>
#include "sock.h"
#include "request.h"
#include "reply.h"

using std::string;
class Pong
{    
    Sock m_sock;
    Request *m_request;
    Reply *m_reply;
public:
    Pong();
    void Create(Request *request, Reply *reply);
    ~Pong();
};
#endif //PONG_H