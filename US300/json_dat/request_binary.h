#ifndef REQUEST_BINARY_H
#define REQUEST_BINARY_H

#include "request.h"

#include <string>
using std::string;
class Request_Binary : public Request
{

protected:
  virtual void create(char *msg, int &sz) override;
  virtual void process(const std::string &msg) override;

public:
  Request_Binary();
  ~Request_Binary();
};
#endif //REQUEST_BINARY_H