#ifndef REQUEST_H
#define REQUEST_H
#include <string>
using std::string;
class Request
{
protected:
    struct UATStart
    {
        int address;
        /*complete the data structure by adding reset of the properties from CUATStart*/
    };

    virtual void create(char **reqMsg, int &reqSz) = 0;
    virtual void process(char *reqMsg, int reqSz) = 0;

public:
    Request();
    void Create(char **reqMsg, int &reqSz);
    void Process(char *reqMsg, int reqSz);
    ~Request();
};
#endif //REQUEST_H