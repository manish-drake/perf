#ifndef REQUEST_JSON_H
#define REQUEST_JSON_H
#include "request.h"
#include "UATStart.h"

#include <string>
using std::string;
class Request_Json : public Request
{
  static void parse(CUATStart &request, UATStart &data)
  {
    data.address = request.getAddress();
    data.Mode = request.getMode();
  }

protected:
  virtual void create(char *msg, int &sz) override;
  virtual void process(const std::string &msg) override;

public:
  Request_Json();
  ~Request_Json();
};
#endif //REQUEST_JSON_H
