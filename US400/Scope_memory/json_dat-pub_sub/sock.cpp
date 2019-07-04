#include "sock.h"
const char *ENDPOINT = "tcp://127.0.0.1:6000";
Sock::Sock()
{
}
void Sock::Listen(std::function<std::string(const std::string&)> &&cb)
{
    std::thread([this, cb]() {
        zmq::socket_t pub_socket(*getCtx(), ZMQ_PUB);
        pub_socket.bind(ENDPOINT);
        // zmq::pollitem_t items[] = {
        //     {pub_socket, 0, ZMQ_POLLIN, 0}};

        while (true)
        {
            zmq::message_t message;
            // zmq::poll(&items[0], 1, 500);

            // if (items[0].revents & ZMQ_POLLIN)
            // {
                pub_socket.recv(&message);
                std::string smessage(static_cast<char *>(message.data()), message.size());
                string response = cb(smessage);
                if (response.size() > 0)
                {
                    zmq::message_t responseMsg(response.size());
                    memcpy(responseMsg.data(), response.c_str(), response.size());
                    printf("Router: Sending response..");
                    pub_socket.send(message, ZMQ_SNDMORE);
                    pub_socket.send(responseMsg);
                }
            // }
        }
        pub_socket.unbind(ENDPOINT);
        pub_socket.close();
    }).detach();
}
std::string Sock::Send(const char *msg, int sz)
{
    zmq::socket_t sub_socket(*getCtx(), ZMQ_SUB);
    sub_socket.connect(ENDPOINT);

    zmq::message_t message(sz);
    memcpy(message.data(), msg, sz);
    sub_socket.send(message);
    zmq::message_t reply;
    sub_socket.recv(&reply);
    std::string smessage(static_cast<char *>(reply.data()), reply.size());
    return smessage;
}
Sock::~Sock()
{
    delete getCtx();
}