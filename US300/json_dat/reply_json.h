#ifndef REPLY_JSON_H
#define REPLY_JSON_H
#include <string>
#include "reply.h"
#include "UATADSBSummary.h"

using std::string;
class Reply_Json : public Reply
{
    static void parse(CUATADSBSummary &reply, UATADSBSummary &data)
    {
        data.callsign = reply.getCallsign();
    }

protected:
    virtual void process(char *repMsg, int &repSz) override;
    virtual void create(char **repMsg, int &repSz) override;

public:
    Reply_Json();
    ~Reply_Json();
};
#endif //REPLY_JSON_H