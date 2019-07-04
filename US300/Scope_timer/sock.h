#ifndef SOCK_H
#define SOCK_H
#include <string>
#include <zmq.hpp>
#include <thread>
#include <functional>

using std::string;
class Sock
{
    zmq::context_t *getCtx()
    {
        static auto context = zmq::context_t(1);
        return &context;
    }
    bool m_closed = false;
public:
    Sock();
    void Listen(std::function<void(char *reqMsg, int reqSz, char **repMsg, int &repSz)> &&cb);
    void Send(char *reqMsg, int reqSz, char **repMsg, int &repSz);
    ~Sock();
};
#endif //SOCK_H