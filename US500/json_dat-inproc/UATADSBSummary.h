#ifndef __UATADSBSummary_h
#define __UATADSBSummary_h

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "TServerMessage.h"



class CUATADSBSummary:public TServerMessage
{
    const int mFormatVersion = 2;
    char* json_string;
 
public:
    static const unsigned int mCmdID=0x1;
    CUATADSBSummary(void)
    {
        setCmdID(mCmdID);
    }
    CUATADSBSummary(Json::Value obj):TServerMessage(obj)
    {
        set(obj);
        setCmdID(mCmdID);
    }
    void setCallsign(std::string value)
    {
        write("Callsign",value);
    }

    std::string getCallsign(void)

    {
        return getString("Callsign");
    }

    bool isCallsignValid(void)
    {
        return isValid("Callsign");

    }

    void setAddress(unsigned int value)
    {
        write("Address",value);
    }

    unsigned int getAddress(void)

    {
        return getUInt("Address");
    }

    bool isAddressValid(void)
    {
        return isValid("Address");

    }

    void setFlightID(std::string value)
    {
        write("FlightID",value);
    }

    std::string getFlightID(void)

    {
        return getString("FlightID");
    }

    bool isFlightIDValid(void)
    {
        return isValid("FlightID");

    }

    void setCallsignID(unsigned int value)
    {
        write("CallsignID",value);
    }

    unsigned int getCallsignID(void)

    {
        return getUInt("CallsignID");
    }

    bool isCallsignIDValid(void)
    {
        return isValid("CallsignID");

    }

    void setEmitterCategory(unsigned int value)
    {
        write("EmitterCategory",value);
    }

    unsigned int getEmitterCategory(void)

    {
        return getUInt("EmitterCategory");
    }

    bool isEmitterCategoryValid(void)
    {
        return isValid("EmitterCategory");

    }

    void setMode3ACode(unsigned int value)
    {
        write("Mode3ACode",value);
    }

    unsigned int getMode3ACode(void)

    {
        return getUInt("Mode3ACode");
    }

    bool isMode3ACodeValid(void)
    {
        return isValid("Mode3ACode");

    }

    void setEmergencyStatus(unsigned int value)
    {
        write("EmergencyStatus",value);
    }

    unsigned int getEmergencyStatus(void)

    {
        return getUInt("EmergencyStatus");
    }

    bool isEmergencyStatusValid(void)
    {
        return isValid("EmergencyStatus");

    }

    void setTCASOperational(bool value)
    {
        write("TCASOperational",value);
    }

    bool getTCASOperational(void)

    {
        return getBool("TCASOperational");
    }

    bool isTCASOperationalValid(void)
    {
        return isValid("TCASOperational");

    }

    void setUATIn(bool value)
    {
        write("UATIn",value);
    }

    bool getUATIn(void)

    {
        return getBool("UATIn");
    }

    bool isUATInValid(void)
    {
        return isValid("UATIn");

    }

    void setES1090In(bool value)
    {
        write("ES1090In",value);
    }

    bool getES1090In(void)

    {
        return getBool("ES1090In");
    }

    bool isES1090InValid(void)
    {
        return isValid("ES1090In");

    }

    void setIdentActive(bool value)
    {
        write("IdentActive",value);
    }

    bool getIdentActive(void)

    {
        return getBool("IdentActive");
    }

    bool isIdentActiveValid(void)
    {
        return isValid("IdentActive");

    }

    void setATCServices(bool value)
    {
        write("ATCServices",value);
    }

    bool getATCServices(void)

    {
        return getBool("ATCServices");
    }

    bool isATCServicesValid(void)
    {
        return isValid("ATCServices");

    }

    void setTCASResolutionAdvisory(bool value)
    {
        write("TCASResolutionAdvisory",value);
    }

    bool getTCASResolutionAdvisory(void)

    {
        return getBool("TCASResolutionAdvisory");
    }

    bool isTCASResolutionAdvisoryValid(void)
    {
        return isValid("TCASResolutionAdvisory");

    }

    void setTXMSO(unsigned int value)
    {
        write("TXMSO",value);
    }

    unsigned int getTXMSO(void)

    {
        return getUInt("TXMSO");
    }

    bool isTXMSOValid(void)
    {
        return isValid("TXMSO");

    }

    void setNACp(unsigned int value)
    {
        write("NACp",value);
    }

    unsigned int getNACp(void)

    {
        return getUInt("NACp");
    }

    bool isNACpValid(void)
    {
        return isValid("NACp");

    }

    void setNACv(unsigned int value)
    {
        write("NACv",value);
    }

    unsigned int getNACv(void)

    {
        return getUInt("NACv");
    }

    bool isNACvValid(void)
    {
        return isValid("NACv");

    }

    void setSIL(unsigned int value)
    {
        write("SIL",value);
    }

    unsigned int getSIL(void)

    {
        return getUInt("SIL");
    }

    bool isSILValid(void)
    {
        return isValid("SIL");

    }

    void setSDA(unsigned int value)
    {
        write("SDA",value);
    }

    unsigned int getSDA(void)

    {
        return getUInt("SDA");
    }

    bool isSDAValid(void)
    {
        return isValid("SDA");

    }

    void setGeometricVerticalAccuracy(unsigned int value)
    {
        write("GeometricVerticalAccuracy",value);
    }

    unsigned int getGeometricVerticalAccuracy(void)

    {
        return getUInt("GeometricVerticalAccuracy");
    }

    bool isGeometricVerticalAccuracyValid(void)
    {
        return isValid("GeometricVerticalAccuracy");

    }

    void setMOPSVersion(unsigned int value)
    {
        write("MOPSVersion",value);
    }

    unsigned int getMOPSVersion(void)

    {
        return getUInt("MOPSVersion");
    }

    bool isMOPSVersionValid(void)
    {
        return isValid("MOPSVersion");

    }

    void setSILSupplement(unsigned int value)
    {
        write("SILSupplement",value);
    }

    unsigned int getSILSupplement(void)

    {
        return getUInt("SILSupplement");
    }

    bool isSILSupplementValid(void)
    {
        return isValid("SILSupplement");

    }

    void setSingleAntenna(unsigned int value)
    {
        write("SingleAntenna",value);
    }

    unsigned int getSingleAntenna(void)

    {
        return getUInt("SingleAntenna");
    }

    bool isSingleAntennaValid(void)
    {
        return isValid("SingleAntenna");

    }

    void setNICBaro(unsigned int value)
    {
        write("NICBaro",value);
    }

    unsigned int getNICBaro(void)

    {
        return getUInt("NICBaro");
    }

    bool isNICBaroValid(void)
    {
        return isValid("NICBaro");

    }

    void setNICSupp(unsigned int value)
    {
        write("NICSupp",value);
    }

    unsigned int getNICSupp(void)

    {
        return getUInt("NICSupp");
    }

    bool isNICSuppValid(void)
    {
        return isValid("NICSupp");

    }

    void setNIC(unsigned int value)
    {
        write("NIC",value);
    }

    unsigned int getNIC(void)

    {
        return getUInt("NIC");
    }

    bool isNICValid(void)
    {
        return isValid("NIC");

    }

    void setAirGroundState(unsigned int value)
    {
        write("AirGroundState",value);
    }

    unsigned int getAirGroundState(void)

    {
        return getUInt("AirGroundState");
    }

    bool isAirGroundStateValid(void)
    {
        return isValid("AirGroundState");

    }

    void setLatitude(float value)
    {
        write("Latitude",value);
    }

    float getLatitude(void)

    {
        return getFloat("Latitude");
    }

    bool isLatitudeValid(void)
    {
        return isValid("Latitude");

    }

    void setLongitude(float value)
    {
        write("Longitude",value);
    }

    float getLongitude(void)

    {
        return getFloat("Longitude");
    }

    bool isLongitudeValid(void)
    {
        return isValid("Longitude");

    }

    void setAltitude(int value)
    {
        write("Altitude",value);
    }

    int getAltitude(void)

    {
        return getInt("Altitude");
    }

    bool isAltitudeValid(void)
    {
        return isValid("Altitude");

    }

    void setEastVel(int value)
    {
        write("EastVel",value);
    }

    int getEastVel(void)

    {
        return getInt("EastVel");
    }

    bool isEastVelValid(void)
    {
        return isValid("EastVel");

    }

    void setNorthVel(unsigned int value)
    {
        write("NorthVel",value);
    }

    unsigned int getNorthVel(void)

    {
        return getUInt("NorthVel");
    }

    bool isNorthVelValid(void)
    {
        return isValid("NorthVel");

    }

    void setVerticalVelocity(int value)
    {
        write("VerticalVelocity",value);
    }

    int getVerticalVelocity(void)

    {
        return getInt("VerticalVelocity");
    }

    bool isVerticalVelocityValid(void)
    {
        return isValid("VerticalVelocity");

    }

    void setVerticalVelocitySource(unsigned int value)
    {
        write("VerticalVelocitySource",value);
    }

    unsigned int getVerticalVelocitySource(void)

    {
        return getUInt("VerticalVelocitySource");
    }

    bool isVerticalVelocitySourceValid(void)
    {
        return isValid("VerticalVelocitySource");

    }

    void setUTCCoupling(unsigned int value)
    {
        write("UTCCoupling",value);
    }

    unsigned int getUTCCoupling(void)

    {
        return getUInt("UTCCoupling");
    }

    bool isUTCCouplingValid(void)
    {
        return isValid("UTCCoupling");

    }

    void setSecondaryAltitude(int value)
    {
        write("SecondaryAltitude",value);
    }

    int getSecondaryAltitude(void)

    {
        return getInt("SecondaryAltitude");
    }

    bool isSecondaryAltitudeValid(void)
    {
        return isValid("SecondaryAltitude");

    }

    void setSelectedAltitude(unsigned int value)
    {
        write("SelectedAltitude",value);
    }

    unsigned int getSelectedAltitude(void)

    {
        return getUInt("SelectedAltitude");
    }

    bool isSelectedAltitudeValid(void)
    {
        return isValid("SelectedAltitude");

    }

    void setSelectedAltitudeType(unsigned int value)
    {
        write("SelectedAltitudeType",value);
    }

    unsigned int getSelectedAltitudeType(void)

    {
        return getUInt("SelectedAltitudeType");
    }

    bool isSelectedAltitudeTypeValid(void)
    {
        return isValid("SelectedAltitudeType");

    }

    void setBaroSetting(float value)
    {
        write("BaroSetting",value);
    }

    float getBaroSetting(void)

    {
        return getFloat("BaroSetting");
    }

    bool isBaroSettingValid(void)
    {
        return isValid("BaroSetting");

    }

    void setSelectedHeading(float value)
    {
        write("SelectedHeading",value);
    }

    float getSelectedHeading(void)

    {
        return getFloat("SelectedHeading");
    }

    bool isSelectedHeadingValid(void)
    {
        return isValid("SelectedHeading");

    }

    void setMCPFCUStatus(bool value)
    {
        write("MCPFCUStatus",value);
    }

    bool getMCPFCUStatus(void)

    {
        return getBool("MCPFCUStatus");
    }

    bool isMCPFCUStatusValid(void)
    {
        return isValid("MCPFCUStatus");

    }

    void setModeAutoPilotEngaged(bool value)
    {
        write("ModeAutoPilotEngaged",value);
    }

    bool getModeAutoPilotEngaged(void)

    {
        return getBool("ModeAutoPilotEngaged");
    }

    bool isModeAutoPilotEngagedValid(void)
    {
        return isValid("ModeAutoPilotEngaged");

    }

    void setModeVNAV(bool value)
    {
        write("ModeVNAV",value);
    }

    bool getModeVNAV(void)

    {
        return getBool("ModeVNAV");
    }

    bool isModeVNAVValid(void)
    {
        return isValid("ModeVNAV");

    }

    void setModeAltitudeHold(bool value)
    {
        write("ModeAltitudeHold",value);
    }

    bool getModeAltitudeHold(void)

    {
        return getBool("ModeAltitudeHold");
    }

    bool isModeAltitudeHoldValid(void)
    {
        return isValid("ModeAltitudeHold");

    }

    void setModeApproach(bool value)
    {
        write("ModeApproach",value);
    }

    bool getModeApproach(void)

    {
        return getBool("ModeApproach");
    }

    bool isModeApproachValid(void)
    {
        return isValid("ModeApproach");

    }

    void setModeLNAV(bool value)
    {
        write("ModeLNAV",value);
    }

    bool getModeLNAV(void)

    {
        return getBool("ModeLNAV");
    }

    bool isModeLNAVValid(void)
    {
        return isValid("ModeLNAV");

    }

    void setMessage(std::string jsonstring)
    {

        TServerMessage::setMessage(jsonstring);

    }

    void set(Json::Value obj)
    {

        TServerMessage::set(obj);

    }

    std::string getMessage(void)
    {
        return TServerMessage::getMessage();
    }

    Json::Value get(void)
    {
        return TServerMessage::get();
    }

};




#endif