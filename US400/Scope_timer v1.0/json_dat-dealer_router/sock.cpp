#include "sock.h"
const char *ENDPOINT = "tcp://127.0.0.1:6000";
Sock::Sock() : m_socket(*getCtx(), ZMQ_DEALER)
{
    m_socket.connect(ENDPOINT);
}
void Sock::Listen(std::function<std::string(const std::string&)> &&cb)
{
    std::thread([this, cb]() {
        zmq::socket_t socket(*getCtx(), ZMQ_ROUTER);
        socket.bind(ENDPOINT);
        zmq::pollitem_t items[] = {
            {socket, 0, ZMQ_POLLIN, 0}};

        while (true)
        {
            zmq::message_t message;
            zmq::poll(&items[0], 1, 500);

            if (items[0].revents & ZMQ_POLLIN)
            {
                socket.recv(&message);
                std::string smessage(static_cast<char *>(message.data()), message.size());
                string response = cb(smessage);
                if (response.size() > 0)
                {
                    zmq::message_t responseMsg(response.size());
                    memcpy(responseMsg.data(), response.c_str(), response.size());
                    // printf("Router: Sending response..");
                    socket.send(message, ZMQ_SNDMORE);
                    socket.send(responseMsg);
                }
            }
        }
        socket.unbind(ENDPOINT);
        socket.close();
    }).detach();
}
std::string Sock::Send(const char *msg, int sz)
{
    zmq::message_t message(sz);
    memcpy(message.data(), msg, sz);
    m_socket.send(message);
    zmq::message_t reply;
    m_socket.recv(&reply);
    std::string smessage(static_cast<char *>(reply.data()), reply.size());
    return smessage;
}
Sock::~Sock()
{
    delete getCtx();
}