#ifndef CCOLLECTOR_H_LIB
#define CCOLLECTOR_H_LIB
#include <string>
#include "defines/class-helper.h"
#include "libraryes/model/cnode.h"
#include "libraryes/model/citems.h"

namespace mon
{
namespace lib
{
namespace model
{

//! Модель коллектора
class CCollector : public CItems<CNode>
{
    MON_READONLY_PROPERTY(std::string, name)
  public:
    CCollector(const std::string &name);
    virtual ~CCollector();
};

}
}
}
#endif // CCOLLECTOR_H_LIB
