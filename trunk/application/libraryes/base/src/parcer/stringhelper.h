#ifndef STRINGHELPER_H
#define STRINGHELPER_H
#include <string>
#include <vector>

namespace mon
{
namespace lib
{
namespace base
{

void                     split(const std::string &s, const char &delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, const char &delim);

}
}
}

#endif // STRINGHELPER_H
