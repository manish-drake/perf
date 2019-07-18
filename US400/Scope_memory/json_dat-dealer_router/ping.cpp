#include "ping.h"
#include "sock.h"
#include <iostream>
#include "UATADSBSummary.h"
#include "request.h"
#include "scope_memself.h"

Ping::Ping()
{
}

void Ping::Create(Request *request, Reply *reply)
{
    m_request = request;
    m_reply = reply;    
}

void Ping::Start()
{
    scope_memself s;
    s.Reset("start");
    Sock sock;
    for (int i = 0; i < 10000; i++)
    {
        char msg[1024] = {0};
        int sz = 0;
        m_request->Create(msg, sz);  //Create the message CUATStart      
        auto reply = sock.Send(msg, sz);
        m_reply->Process(reply); //Process the reply CUATADSBSummary
        
        std::cout << "Loop: " << i << std::endl;
    }
    std::cout << "done!" << std::endl;
    s.Dispose();
}

Ping::~Ping()
{
}