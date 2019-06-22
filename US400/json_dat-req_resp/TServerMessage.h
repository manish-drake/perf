/// \file TServerMessage.h
/// \brief  <Description>

#ifndef __TservMessage__h
#define __TservMessage__h

#include <time.h>
#include <math.h>
#include <string>
#include "json.h"

//TODO: Add error handling if reading from object which
//hasn't been parsed

class TServerMessage
{

    bool    mReadValid;
    bool    mWriteValid;

    Json::Reader            mReader;
    Json::FastWriter        mWriter;
    Json::Value             mReadRoot;
    Json::Value             mWriteRoot;

    const char* mCommandKey="CommandID";
    public:

    TServerMessage(void)
    {
        mReadValid=false;       //No data yet
        mWriteValid=false;
    }

    TServerMessage(Json::Value& obj)
    {
        mReadRoot=obj;
    }


    ~TServerMessage(void)
    {
    }

    void print(Json::Value obj)
    {
        std::string s=mWriter.write(obj);
        printf("%s\n",s.c_str());
    }


    void setCmdID(unsigned int cmdid)
    {
        write(mCommandKey,cmdid);
    }

    unsigned int getCmdID(void)
    {
        return getUInt(mCommandKey);
    }

    void clear(void)
    {
       mReadRoot.clear();
       mWriteRoot.clear();
       mReadValid=false;
       mWriteValid=false;
    }

    void write(char const* name, int value)
    {
        mWriteValid=true;
        mWriteRoot[name]=(Json::Value::Int) value;
        printf("Write int %s %d\n",name,value);
    }

    int getInt(char const* name)
    {
        Json::Value  value;
        value=mReadRoot.get(name,0);
        return value.asInt();
    }

    void write(char const* name, unsigned int value)
    {
        mWriteValid=true;
        mWriteRoot[name]=(Json::Value::UInt) value;
    }

    unsigned int getUInt(char const* name)
    {
        Json::Value  value;
        value=mReadRoot.get(name,0);
        return value.asUInt();
    }

    void write(char const* name, unsigned long long int value)
    {
        mWriteValid=true;
        mWriteRoot[name]=(Json::Value::UInt64) value;
    }

    unsigned long long int getUInt64(char const* name)
    {
        Json::Value  value;
        value=mReadRoot.get(name,0);
        return value.asUInt64();
    }


    void write(char const* name, std::string str)
    {
        mWriteValid=true;
        mWriteRoot[name]= str;
    }

    std::string getString(char const* name)
    {
        Json::Value  value;
        value=mReadRoot.get(name,"");
        return value.asString();
    }


    void write(char const* name, char *str)
    {
        mWriteValid=true;
        std::string s(str);
        write(name,s);
    }

    void write(char const* name, float value)
    {
        mWriteValid=true;
        mWriteRoot[name]=(float) value ;
    }

    float getFloat(char const* name)
    {
        Json::Value  value;
        value=mReadRoot.get(name,0.0);
        return value.asFloat();
    }


    void write(char const* name, double value)
    {
        mWriteRoot[name]=(double) value ;
    }

    void write(char const* name, bool value)
    {
        mWriteRoot[name]=(bool) value ;
    }


    double getDouble(char const* name)
    {
        Json::Value  value;
        value=mReadRoot.get(name,0.0);
        return value.asDouble();
    }

    double getBool(char const* name)
    {
        Json::Value  value;
        value=mReadRoot.get(name,false);
        return value.asBool();
    }



    Json::Value getObject(char const* name)
    {
        return mReadRoot.get(name,false);
    }

//***********************************************************************************
//getArray functions for each type, can't use templates because of separate as<type> function

    std::vector<int> getArray(char const* name, std::vector<int> arr)
    {
        Json::Value value=mReadRoot[name];
        if (value.isArray())
        {

             Json::Value::iterator itr = value.begin();
//             int i=0;
             while (itr != value.end())
             {
                Json::Value single = (*itr);
                arr.push_back(single.asInt());
                itr++;
             }
        }
        return arr;
    }

    std::vector<unsigned int> getArray(char const* name, std::vector<unsigned int> arr)
    {
        Json::Value value=mReadRoot[name];
        if (value.isArray())
        {

             Json::Value::iterator itr = value.begin();
//             int i=0;
             while (itr != value.end())
             {
                Json::Value single = (*itr);
                arr.push_back(single.asUInt());
                itr++;
             }
        }
        return arr;
    }

    std::vector<short unsigned int> getArray(char const* name, std::vector<short unsigned int> arr)
    {
        Json::Value value=mReadRoot[name];
        if (value.isArray())
        {

             Json::Value::iterator itr = value.begin();
//             int i=0;
             while (itr != value.end())
             {
                Json::Value single = (*itr);
                arr.push_back(single.asUInt());
                itr++;
             }
        }
        return arr;
    }

    std::vector<short int> getArray(char const* name, std::vector<short int> arr)
    {
        Json::Value value=mReadRoot[name];
        if (value.isArray())
        {

             Json::Value::iterator itr = value.begin();
//             int i=0;
             while (itr != value.end())
             {
                Json::Value single = (*itr);
                arr.push_back(single.asInt());
                itr++;
             }
        }
        return arr;
    }

    std::vector<long long int> getArray(char const* name, std::vector<long long int> arr)
    {
        Json::Value value=mReadRoot[name];
        if (value.isArray())
        {

             Json::Value::iterator itr = value.begin();
//             int i=0;
             while (itr != value.end())
             {
                Json::Value single = (*itr);
                arr.push_back(single.asInt64());
                itr++;
             }
        }
        return arr;
    }
    std::vector<float> getArray(char const* name, std::vector<float> arr)
    {
        Json::Value value=mReadRoot[name];
        if (value.isArray())
        {

             Json::Value::iterator itr = value.begin();
//             int i=0;
             while (itr != value.end())
             {
                Json::Value single = (*itr);
                arr.push_back(single.asFloat());
                itr++;
             }
        }
        return arr;
    }
    std::vector<double> getArray(char const* name, std::vector<double> arr)
    {
        Json::Value value=mReadRoot[name];
        if (value.isArray())
        {

             Json::Value::iterator itr = value.begin();
//             int i=0;
             while (itr != value.end())
             {
                Json::Value single = (*itr);
                arr.push_back(single.asDouble());
                itr++;
             }
        }
        return arr;
    }
    std::vector<std::string> getArray(char const* name, std::vector<std::string> arr)
    {
        Json::Value value=mReadRoot[name];
        if (value.isArray())
        {

             Json::Value::iterator itr = value.begin();
//             int i=0;
             while (itr != value.end())
             {
                Json::Value single = (*itr);
                arr.push_back(single.asString());
                itr++;
             }
        }
        return arr;
    }
    std::vector<bool> getArray(char const* name, std::vector<bool> arr)
    {
        Json::Value value=mReadRoot[name];
        if (value.isArray())
        {

             Json::Value::iterator itr = value.begin();
//             int i=0;
             while (itr != value.end())
             {
                Json::Value single = (*itr);
                arr.push_back(single.asBool());
                itr++;
             }
        }
        return arr;
    }


//**************************************************************************
//write functions and templates for each type
    template <typename ArrayType>
    void write(char const* name,std::vector<ArrayType>& arr)
    {

        mWriteRoot[name]=Json::arrayValue;

        //Need "typename" before "std::vector<arrayType>" because the compiler says it is needed
        for(typename std::vector<ArrayType>::iterator it = arr.begin(); it != arr.end(); ++it)
        {
            mWriteRoot[name].append(Json::Value(*it));
        }
    }
    template <bool> std::vector<bool> write(const char*, std::vector<bool>& arr);
    template <int> std::vector<int> write(const char*, std::vector<int>& arr);
    template <short int> std::vector<int> write(const char*, std::vector<int>& arr);
    template <unsigned int> std::vector<unsigned int> write(const char*, std::vector<unsigned int>& arr);
    template <short unsigned int> std::vector<unsigned int> write(const char*, std::vector<unsigned int>& arr);
    template <long long int> std::vector<long long> write(const char*, std::vector<long long int>& arr);
    template <float&> std::vector<float> write(const char*, std::vector<float>& arr);
    template <double&> std::vector<double> write(const char*, std::vector<double>& arr);
    template <std::string&> std::vector<std::string> write(const char*, std::vector<std::string>& arr);




#if 0
    void write(char const* name,std::vector<bool>& arr)
    {

        mWriteRoot[name]=Json::arrayValue;

        for(std::vector<bool>::iterator it = arr.begin(); it != arr.end(); ++it)
        {
            mWriteRoot[name].append(Json::Value(*it));
        }
    }
#endif

    std::string getMessage(void)
    {
        return mWriter.write(mWriteRoot);
    }

    Json::Value get(void)
    {
        return mWriteRoot;
    }

    void setMessage(std::string str)
    {
        if(mReader.parse(str,mReadRoot,false))
        {
            mReadValid=true;
        }
        else
        {
            mReadValid=false;
        }

    }

    void set(Json::Value obj)
    {
        mReadRoot=obj;
    }

    bool isValid(std::string name)
    {
        return mReadRoot.isMember(name);
    }


};

#endif

