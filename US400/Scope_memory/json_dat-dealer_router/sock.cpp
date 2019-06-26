#include "sock.h"
<<<<<<< HEAD:US400/Scope_memory/json_dat-dealer_router/sock.cpp
const char *ENDPOINT = "tcp://127.0.0.1:6000";
=======
#include <exception>
#include <iostream>

const char *ENDPOINT = "inproc://sock";
>>>>>>> 9111d71f0c5aef856a661d6528154deb5eac7c4b:US500/json_dat-inproc/sock.cpp
Sock::Sock()
{
}
void Sock::Listen(std::function<void(char *reqMsg, int reqSz, char **repMsg, int &repSz)> &&cb)
{
    std::thread([this, cb]() {
        zmq::socket_t socket(*getCtx(), ZMQ_ROUTER);
        socket.bind(ENDPOINT);
        zmq::pollitem_t items[] = {
            {socket, 0, ZMQ_POLLIN, 0}};

        while (!m_closed)
        {
            zmq::message_t message;
            zmq::poll(&items[0], 1, 500);

            if (items[0].revents & ZMQ_POLLIN)
            {
                socket.recv(&message);
                auto reqMsg = (char *)message.data();
                // std::cout << reqMsg << std::endl;
                auto reqSz = message.size();
                char *repMsg;
                int repSz;

                cb(reqMsg, reqSz, &repMsg, repSz);

                if (repSz > 0)
                {
<<<<<<< HEAD:US400/Scope_memory/json_dat-dealer_router/sock.cpp
                    zmq::message_t responseMsg(response.size());
                    memcpy(responseMsg.data(), response.c_str(), response.size());
                    // printf("Router: Sending response..");
                    socket.send(message, ZMQ_SNDMORE);
=======
                    zmq::message_t responseMsg(repSz);
                    memcpy(responseMsg.data(), repMsg, repSz);
>>>>>>> 9111d71f0c5aef856a661d6528154deb5eac7c4b:US500/json_dat-inproc/sock.cpp
                    socket.send(responseMsg);
                }
                free(repMsg);
            }
        }
        socket.unbind(ENDPOINT);
        socket.close();
    })
        .detach();
}
void Sock::Send(char *reqMsg, int reqSz, char **repMsg, int &repSz)
{
<<<<<<< HEAD:US400/Scope_memory/json_dat-dealer_router/sock.cpp
    zmq::socket_t socket(*getCtx(), ZMQ_DEALER);
    socket.connect(ENDPOINT);

    zmq::message_t message(sz);
    memcpy(message.data(), msg, sz);
    socket.send(message);
    zmq::message_t reply;
    socket.recv(&reply);
    std::string smessage(static_cast<char *>(reply.data()), reply.size());
    return smessage;
=======
    if (getCtx())
    {
        zmq::socket_t socket(*getCtx(), ZMQ_REQ);
        zmq::message_t message(reqSz);
        memcpy(message.data(), reqMsg, reqSz);
        socket.connect(ENDPOINT);
        socket.send(message);

        zmq::message_t reply;
        socket.recv(&reply);
        *repMsg = (char *)reply.data();
        repSz = reply.size();
        // std::cout << *repMsg << std::endl;
    }
>>>>>>> 9111d71f0c5aef856a661d6528154deb5eac7c4b:US500/json_dat-inproc/sock.cpp
}
Sock::~Sock()
{
    m_closed = true;
}