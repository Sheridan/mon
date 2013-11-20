#include <sstream>
//#include <regex>
#include "stringhelper.h"

namespace mon
{
namespace lib
{
namespace base
{

void split(const std::string &s, const char &delim, std::list<std::string> &elems)
{
  std::stringstream ss(s);
  std::string item;
  while (std::getline(ss, item, delim))
  {
    elems.push_back(item);
  }
}

std::list<std::string> split(const std::string &s, const char &delim)
{
  std::list<std::string> elems;
  split(s, delim, elems);
  return elems;
}

//std::list<std::string> split(const std::string &input, const std::string &regex)
//{
//    // passing -1 as the submatch index parameter performs splitting
//    std::sregex_token_iterator
//        first{input.begin(), input.end(), regex, -1},
//        last;
//    return {first, last};
//}

}
}
}
