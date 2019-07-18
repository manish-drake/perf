#include "sock.h"
#include <exception>
#include <iostream>

const char *ENDPOINT = "tcp://127.0.0.1:6000";
Sock::Sock() : m_socket(*getCtx(), ZMQ_REQ)
{
    m_socket.connect(ENDPOINT);
}
void Sock::Listen(std::function<void(char *reqMsg, int reqSz, char **repMsg, int &repSz)> &&cb)
{
    std::thread([this, cb]() {
        zmq::socket_t socket(*getCtx(), ZMQ_REP);
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
                auto reqSz = message.size();
                char *repMsg;
                int repSz;

                cb(reqMsg, reqSz, &repMsg, repSz);

                if (repSz > 0)
                {
                    zmq::message_t responseMsg(repSz);
                    memcpy(responseMsg.data(), repMsg, repSz);
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
    if (getCtx())
    {
        zmq::message_t message(reqSz);
        memcpy(message.data(), reqMsg, reqSz);
        m_socket.send(message);

        zmq::message_t reply;
        m_socket.recv(&reply);
        *repMsg = (char *)reply.data();
        repSz = reply.size();
        // std::cout << *repMsg << std::endl;
    }
}
Sock::~Sock()
{
    m_closed = true;
}