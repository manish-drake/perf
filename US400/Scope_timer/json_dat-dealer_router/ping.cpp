#include "ping.h"
#include "sock.h"
#include <iostream>
#include "UATADSBSummary.h"
#include "request.h"
#include <time.h>
#include <sys/time.h>

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
    struct timeval start, end;
    gettimeofday(&start, NULL);

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
    std::cout << "done!" ;

    gettimeofday(&end, NULL);
    std::cout << "Total time was "<< ((end.tv_sec * 1000000 + end.tv_usec)
                  - (start.tv_sec * 1000000 + start.tv_usec)) << " uSec ";
}

Ping::~Ping()
{
}