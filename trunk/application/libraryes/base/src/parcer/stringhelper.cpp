#include "stringhelper.h"
#include <sstream>

namespace mon
{
namespace lib
{
namespace base
{

void split(const std::string &s, const char &delim, std::vector<std::string> &elems)
{
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim))
  {
    elems.push_back(item);
  }
}

std::vector<std::string> split(const std::string &s, const char &delim)
{
  std::vector<std::string> elems;
  split(s, delim, elems);
  return elems;
}

}
}
}
