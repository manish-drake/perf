#ifndef REQUEST_H
#define REQUEST_H
#include <string>
using std::string;
class Request
{
protected:
    struct UATStart 
    {
        unsigned int address;
        unsigned int Mode;
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