#ifndef REPLY_JSON_H
#define REPLY_JSON_H
#include <string>
#include "reply.h"
#include "UATADSBSummary.h"

using std::string;
class Reply_Json : public Reply
{
    static void parse(CUATADSBSummary &reply, UATADSBSummary &data)
    {
        data.callsign = reply.getCallsign();
        data.address = reply.getAddress();
        data.flightID = reply.getFlightID();
        data.callsignID = reply.getCallsignID();
        data.emitterCategory = reply.getEmitterCategory();
        data.mode3ACode = reply.getMode3ACode();
        data.emergencyStatus = reply.getEmergencyStatus();
        data.tcasOperational = reply.getTCASOperational();
        data.uatIn = reply.getUATIn();
        data.es1090In = reply.getES1090In();
        data.identActive = reply.getIdentActive();
        data.atcServices = reply.getATCServices();
        data.tcasResolutionAdvisory = reply.getTCASResolutionAdvisory();
        data.txMSO = reply.getTXMSO();
        data.nacp = reply.getNACp();
        data.nacv = reply.getNACv();
        data.sil = reply.getSIL();
        data.sda = reply.getSDA();
        data.geometricVerticalAccuracy = reply.getGeometricVerticalAccuracy();
        data.mopsVersion = reply.getMOPSVersion();
        data.silSupplement = reply.getSILSupplement();
        data.singleAntenna = reply.getSingleAntenna();
        data.nicBaro = reply.getNICBaro();
        data.nicSupp = reply.getNICSupp();
        data.nic = reply.getNIC();
        data.airGroundState = reply.getAirGroundState();
        data.latitude = reply.getLatitude();
        data.longitude = reply.getLongitude();
        data.altitude = reply.getAltitude();
        data.eastVel = reply.getEastVel();
        data.northVel = reply.getNorthVel();
        data.verticalVelocity = reply.getVerticalVelocity();
        data.verticalVelocitySource = reply.getVerticalVelocitySource();
        data.utcCoupling = reply.getUTCCoupling();
        data.secondaryAltitude = reply.getSecondaryAltitude();
        data.selectedAltitude = reply.getSelectedAltitude();
        data.selectedAltitudeType = reply.getSelectedAltitudeType();
        data.baroSetting = reply.getBaroSetting();
        data.selectedHeading = reply.getSelectedHeading();
        data.mcpFCUStatus = reply.getMCPFCUStatus();
        data.modeAutoPilotEngaged = reply.getModeAutoPilotEngaged();
        data.modeVNAV = reply.getModeVNAV();
        data.modeAltitudeHold = reply.getModeAltitudeHold();
        data.modeApproach = reply.getModeApproach();
        data.modeLNAV = reply.getModeLNAV();   
    }

protected:
    virtual void process(const std::string &reply) override;
    virtual std::string create() override;

public:
    Reply_Json();
    ~Reply_Json();
};
#endif //REPLY_JSON_H