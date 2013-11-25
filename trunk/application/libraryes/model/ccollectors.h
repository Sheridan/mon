#ifndef CCOLLECTORS_H_LIB
#define CCOLLECTORS_H_LIB
#include "libraryes/model/citems.h"
#include "libraryes/model/ccollector.h"

namespace mon
{
namespace lib
{
namespace model
{

//! Модель коллекторов
class CCollectors : public CItems<CCollector>
{
  public:
    CCollectors();
    virtual ~CCollectors();
};

}
}
}
#endif // CCOLLECTORS_H_LIB
