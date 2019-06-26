#ifndef __UATStart_h
#define __UATStart_h

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "TServerMessage.h"

class CUATStart:public TServerMessage
{
    const int mFormatVersion = 2;
    char* json_string;

public:
    static const unsigned int mCmdID=0x2;
    CUATStart(void)
    {
        setCmdID(mCmdID);
    }

    CUATStart(Json::Value obj):TServerMessage(obj)
    {
        set(obj);
        setCmdID(mCmdID);
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

    void setMode(unsigned int value)
    {
        write("Mode",value);
    }

    unsigned int getMode(void)

    {
        return getUInt("Mode");
    }

    bool isModeValid(void)
    {
        return isValid("Mode");

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
