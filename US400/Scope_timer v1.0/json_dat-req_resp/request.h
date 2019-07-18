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

    virtual void create(char *msg, int &sz) = 0;
    virtual void process(const std::string &msg) = 0;

public:
    Request();
    void Create(char *msg, int &sz);
    void Process(const std::string &msg);
    ~Request();
};
#endif //REQUEST_H