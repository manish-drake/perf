#ifndef TEST_H
#define TEST_H
#include <string>
#include "ping.h"
#include "pong.h"
#include "request_json.h"
#include "reply_json.h"
#include "scope_memself.h"
// #include "request_binary.h"
// #include "reply_binary.h"

using std::string;

class Test
{
  Request_Json m_request;
  Reply_Json m_reply;
  Ping m_ping;
  Pong m_pong;
  public:
    Test();
    
    void Setup();
    void Run();
    void Teardown();

    ~Test();
};
#endif //TEST_H