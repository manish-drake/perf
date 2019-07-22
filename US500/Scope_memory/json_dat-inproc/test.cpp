#include "test.h"
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
Test::Test()
{
}

void Test::Setup()
{
    /*
    #1 Create a class-object that serializes some json data
    #2 create zmq context
    */
    m_ping.Create(&m_request, &m_reply);
    m_pong.Create(&m_request, &m_reply);
}

void Test::Run()
{
    /*
    Create a loop that:
    #1 sends some json data over tcp
    #2 receives data 
    #3 parses data
    #4 sends back
    #5 repeat for 10k iterations
    */
    scope_memself s;
    m_ping.Start();
}

void Test::Teardown()
{
    /*
    destroy zmq context
    */
}

Test::~Test()
{
}
