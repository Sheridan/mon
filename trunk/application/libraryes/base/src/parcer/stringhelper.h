#ifndef STRINGHELPER_H
#define STRINGHELPER_H
#include <string>
#include <list>

namespace mon
{
namespace lib
{
namespace base
{

void                     split(const std::string &s, const char &delim, std::list<std::string> &elems);
std::list<std::string> split(const std::string &s, const char &delim);
//std::list<std::string> split(const std::string &input, const std::string &regex);

}
}
}

#endif // STRINGHELPER_H
