#include "pong.h"
Pong::Pong()
{
    m_sock.Listen([this](const std::string &msg) -> std::string {
        m_request->Process(msg);
        return m_reply->Create();
    });
}

void Pong::Create(Request *request, Reply *reply)
{
    m_request = request;
    m_reply = reply;
}

Pong::~Pong()
{
}