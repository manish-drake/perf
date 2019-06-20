#ifndef STRINGUTILS_H
#define STRINGUTILS_H


#include <string>

namespace StringUtils
{

inline std::string &operator<<(std::string &&str1, const std::string &str2)
{
    return str1.append(str2);
}
inline std::string &operator<<(std::string &str1, const std::string &str2)
{
    return str1.append(str2);
}
inline std::string &operator<<(std::string &str1, const char *cstr)
{
    str1 += cstr;
    return str1;
}
inline std::string &operator<<(std::string &str1, const int &num)
{
    str1 += std::to_string(num);
    return str1;
}
inline std::string &operator<<(std::string &str1, const double &dbl)
{
    str1 += std::to_string(dbl);
    return str1;
}
inline std::string &operator<<(std::string &str1, const float &flt)
{
    str1 += std::to_string(flt);
    return str1;
}
}

#endif //STRINGUTILS_H
