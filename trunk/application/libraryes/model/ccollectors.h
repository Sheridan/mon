#ifndef CCOLLECTORS_H_LIB
#define CCOLLECTORS_H_LIB
#include "defines/mutex-helper.h"
#include "libraryes/model/ccollector.h"

namespace mon
{
namespace lib
{
namespace model
{

//! Модель коллекторов
class CCollectors
{
    MON_MUTEX_DECLARE(collectors)
  public:
    CCollectors();
    virtual ~CCollectors();

  protected:
    void addCollector(CCollector *c);

  private:
    TCollectors m_collectors;
};

}
}
}
#endif // CCOLLECTORS_H_LIB
