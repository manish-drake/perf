#ifndef SOCK_H
#define SOCK_H
#include <string>
#include <zmq.hpp>
#include <thread>
#include <functional>
#include <iostream>

using namespace std;
using std::string;
class Sock
{
    zmq::context_t *getCtx()
    {
        static auto context = zmq::context_t(1);
        return &context;
    }
    zmq::socket_t m_socket;

public:
    Sock();
    void Listen(std::function<std::string(const std::string&)> &&cb);
    std::string Send(const char *msz, int sz);
    ~Sock();
};
#endif //SOCK_H