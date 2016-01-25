/* %Id% */
#ifndef CVALUE_H
#define CVALUE_H
#include "libraryes/config/model/cnode.h"
#include "libraryes/base/string/cvariant.h"

namespace mon
{
namespace lib
{
namespace config
{
//! Переменная конфига, тут хранятся значения
class CFile : public CNode, public mon::lib::base::CVariant
{
public:
  CFile(const std::string &nodeName, CNode *parentNode);
  ~CFile();
  CFolder *parent();

  bool               get(const bool               &def);
  char               get(const char               &def);
  int                get(const int                &def);
  unsigned int       get(const unsigned int       &def);
  short              get(const short              &def);
  unsigned short     get(const unsigned short     &def);
  long               get(const long               &def);
  unsigned long      get(const unsigned long      &def);
  long long          get(const long long          &def);
  unsigned long long get(const unsigned long long &def);
  float              get(const float              &def);
  double             get(const double             &def);
  std::string        get(const std::string        &def);
};

}
}
}
#endif // CVALUE_H
