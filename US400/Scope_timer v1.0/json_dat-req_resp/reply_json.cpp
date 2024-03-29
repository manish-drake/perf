#include "reply_json.h"
Reply_Json::Reply_Json()
{
}
void Reply_Json::process(const std::string &reply) 
{
    CUATADSBSummary uatADSBSummary;
    uatADSBSummary.setMessage(reply);
    UATADSBSummary data;
    parse(uatADSBSummary, data);
}
std::string Reply_Json::create()
{
    CUATADSBSummary uatADSBSummary;
    uatADSBSummary.setCallsign("0735");
    uatADSBSummary.setAddress(11422302);
    uatADSBSummary.setFlightID("DELTA");
    uatADSBSummary.setCallsignID(7);
    uatADSBSummary.setEmitterCategory(1);
    uatADSBSummary.setMode3ACode(1);
    uatADSBSummary.setEmergencyStatus(0);
    uatADSBSummary.setTCASOperational(false);
    uatADSBSummary.setUATIn(true);
    uatADSBSummary.setES1090In(true);
    uatADSBSummary.setIdentActive(false);
    uatADSBSummary.setATCServices(1);
    uatADSBSummary.setTCASResolutionAdvisory(0);
    uatADSBSummary.setTXMSO(63);
    uatADSBSummary.setNACp(0);
    uatADSBSummary.setNACv(0);
    uatADSBSummary.setSIL(0);
    uatADSBSummary.setSDA(2);
    uatADSBSummary.setGeometricVerticalAccuracy(1);
    uatADSBSummary.setMOPSVersion(3);
    uatADSBSummary.setSILSupplement(0);
    uatADSBSummary.setSingleAntenna(0);
    uatADSBSummary.setNICBaro(0);
    uatADSBSummary.setNICSupp(0);
    uatADSBSummary.setNIC(1);
    uatADSBSummary.setAirGroundState(0);
    uatADSBSummary.setLatitude(39.34);
    uatADSBSummary.setLongitude(-95.24);
    uatADSBSummary.setAltitude(3900);
    uatADSBSummary.setEastVel(2);
    uatADSBSummary.setNorthVel(4294967291);
    uatADSBSummary.setVerticalVelocity(1024);
    uatADSBSummary.setVerticalVelocitySource(0);
    uatADSBSummary.setUTCCoupling(0);
    uatADSBSummary.setSecondaryAltitude(25984);
    uatADSBSummary.setSelectedAltitude(25984);
    uatADSBSummary.setSelectedAltitudeType(1);
    uatADSBSummary.setBaroSetting(10250);
    uatADSBSummary.setSelectedHeading(90);
    uatADSBSummary.setMCPFCUStatus(false);
    uatADSBSummary.setModeAutoPilotEngaged(false);
    uatADSBSummary.setModeVNAV(true);
    uatADSBSummary.setModeAltitudeHold(true);
    uatADSBSummary.setModeApproach(true);
    uatADSBSummary.setModeLNAV(true);  
    return uatADSBSummary.getMessage();
}

Reply_Json::~Reply_Json()
{
}
