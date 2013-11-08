/* %Id% */
#ifndef CVALUE_H
#define CVALUE_H
#include "cnode.h"
#include "cvariant.h"

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

  bool        get(const bool        &def);
  int         get(const int         &def);
  double      get(const double      &def);
  std::string get(const std::string &def);
};

}
}
}
#endif // CVALUE_H
