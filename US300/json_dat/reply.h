#ifndef REPLY_H
#define REPLY_H
#include <string>
using std::string;
class Reply
{
protected:
  struct UATADSBSummary
  {
    std::string callsign;
    /*complete the data structure by adding reset of the properties from CUATADSBSummary*/
  };
 
  virtual void process(const std::string &reply) = 0;
  virtual std::string create() = 0;

public:
  Reply();
  void Process(const std::string &reply);
  std::string Create();
  ~Reply();
};
#endif //REPLY_H