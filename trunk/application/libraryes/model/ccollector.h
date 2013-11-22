#ifndef CCOLLECTOR_H_LIB
#define CCOLLECTOR_H_LIB
#include <list>
#include <string>
#include "defines/class-helper.h"
#include "libraryes/model/cnodes.h"

namespace mon
{
namespace lib
{
namespace model
{

//! Модель коллектора
class CCollector : public CNodes
{
    MON_READONLY_PROPERTY(std::string, name)
  public:
    CCollector(const std::string &name);
    virtual ~CCollector();
};

//! Список коллекторов
typedef std::list<CCollector *> TCollectors;

}
}
}
#endif // CCOLLECTOR_H_LIB
