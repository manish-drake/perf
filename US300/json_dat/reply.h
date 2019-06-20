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
 
  virtual void process(char *repMsg, int &repSz) = 0;
  virtual void create(char **repMsg, int &repSz) = 0;

public:
  Reply();
  void Process(char *repMsg, int &repSz);
  void Create(char **repMsg, int &repSz);
  ~Reply();
};
#endif //REPLY_H