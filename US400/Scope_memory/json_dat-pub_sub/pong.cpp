#include "pong.h"
Pong::Pong()
{
    m_sock.Listen([this](char *reqMsg, int reqSz, char **repMsg, int &repSz) -> void {
        m_request->Process(reqMsg, reqSz);
        m_reply->Create(repMsg, repSz);
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