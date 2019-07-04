#include "ping.h"
#include "sock.h"
#include <iostream>
#include "UATADSBSummary.h"
#include "request.h"


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
    Sock sock;
    for (int i = 0; i < 10000; i++)
    {
        char *reqMsg;
        int sz = 0;
        m_request->Create(&reqMsg, sz);  //Create the message CUATStart   

        char *repMsg;
        int  repSz;
        sock.Send(reqMsg, sz, &repMsg, repSz);
        m_reply->Process(repMsg, repSz); //Process the reply CUATADSBSummary
        free(reqMsg);
        std::cout << "Loop: " << i << std::endl;
    }
    std::cout << "done!" ;
}

Ping::~Ping()
{
}