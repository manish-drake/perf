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
    int address;
    std::string flightID;
    unsigned int callsignID;
    unsigned int emitterCategory;
    unsigned int mode3ACode;
    unsigned int emergencyStatus;
    bool tcasOperational;
    bool uatIn;
    bool es1090In;
    bool identActive;
    bool atcServices;
    bool tcasResolutionAdvisory;
    unsigned int txMSO;
    unsigned int nacp;
    unsigned int nacv;
    unsigned int sil;
    unsigned int sda;
    unsigned int geometricVerticalAccuracy;
    unsigned int mopsVersion;
    unsigned int silSupplement;
    unsigned int singleAntenna;
    unsigned int nicBaro;
    unsigned int nicSupp;
    unsigned int nic;
    unsigned int airGroundState;
    float latitude;
    float longitude;
    int altitude;
    int eastVel;
    unsigned int northVel;
    int verticalVelocity;
    unsigned int verticalVelocitySource;
    unsigned int utcCoupling;
    int secondaryAltitude;
    int selectedAltitude;
    unsigned int selectedAltitudeType;
    float baroSetting;
    float selectedHeading;
    bool mcpFCUStatus;
    bool modeAutoPilotEngaged;
    bool modeVNAV;
    bool modeAltitudeHold;
    bool modeApproach;
    bool modeLNAV;    
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