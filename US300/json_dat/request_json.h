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
  }

protected:
  virtual void create(char **reqMsg, int &reqSz) override;
  virtual void process(char *reqMsg, int reqSz) override;

public:
  Request_Json();
  ~Request_Json();
};
#endif //REQUEST_JSON_H
