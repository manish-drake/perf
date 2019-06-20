#include "columns.h"

int Columns::getInt(const char *key, const int &def)
{
    int ret(def);
    get(ret, key);
    return ret;
}
unsigned int Columns::getUInt(const char *key, const unsigned int &def)
{
    return getInt(key, (int)def);
}

double Columns::getDouble(const char *key, const double &def)
{
    double ret(def);
    get(ret, key);
    return ret;
}

float Columns::getFloat(const char *key, const float &def)
{
    return (float)getDouble(key, (double)def);
}

std::string Columns::getString(const char *key, const std::string &def)
{
    std::string ret(def);
    get(ret, key);
    return ret;
}

char *Columns::getChar(const char *key, const char *def)
{
    std::string str = getString(key, std::string(def));
    return strdup(str.c_str());
}
int Columns::getBool(const char *key, const int &def)
{
    bool ret(def);
    get(ret, key);
    return ret;
}

Datetime Columns::getDt(const char *key, const int &def)
{
    Datetime ret((time_t)def);
    get(ret, key);
    return ret;
}

bool Columns::get(int &refVar, const char *key)
{
    return get(refVar, key, m_intColumns);
}

bool Columns::get(double &refVar, const char *key)
{
    return get(refVar, key, m_dblColumns);
}

bool Columns::get(std::string &refVar, const char *key)
{
    return get(refVar, key, m_strColumns);
}

bool Columns::get(bool &refVar, const char *key)
{
    return get(refVar, key, m_boolColumns);
}

bool Columns::get(Datetime &refVar, const char *key)
{
    return get(refVar, key, m_dtColumns);
}
bool Columns::get(unsigned int &refVar, const char *key)
{
    int intVar;
    if (get(intVar, key))
    {
        refVar = intVar;
        return true;
    }
    else
        return false;
}

bool Columns::get(float &refVar, const char *key)
{
    double dblVar;
    if (get(dblVar, key))
    {
        refVar = dblVar;
        return true;
    }
    else
        return false;
}
bool Columns::get(const char *refVar, const char *key)
{
    std::ignore = refVar;   //unused parameter 'refVar'
    std::string str;
    bool ret = get(str, key);    
    refVar = strdup(str.c_str());
    return ret;

}

void Columns::set(const char *key, const int &value)
{
    set(key, value, m_intColumns);
}
void Columns::set(const char *key, const unsigned int &value)
{                                 //TODO:...
    set(key, (const int &)value); //if uint is a practical requirement
} //then we can handle it separately

void Columns::set(const char *key, const double &value)
{
    set(key, value, m_dblColumns);
}
void Columns::set(const char *key, const float &value)
{
    set(key, (const double &)value);
}

void Columns::set(const char *key, const std::string &value)
{
    set(key, value, m_strColumns);
}
void Columns::set(const char *key, const char *value)
{
    set(key, std::string(strdup(value)));
}

void Columns::set(const char *key, const bool &value)
{
    set(key, value, m_boolColumns);
}

void Columns::set(const char *key, const Datetime &value)
{
    set(key, value, m_dtColumns);
}

void Columns::swap(const Columns &cols)
{
    swap(cols.m_intColumns, m_intColumns);
    swap(cols.m_strColumns, m_strColumns);
    swap(cols.m_boolColumns, m_boolColumns);
    swap(cols.m_dtColumns, m_dtColumns);
    swap(cols.m_dblColumns, m_dblColumns);
}
