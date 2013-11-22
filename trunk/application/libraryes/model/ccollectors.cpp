#include "libraryes/model/ccollectors.h"

namespace mon
{
namespace lib
{
namespace model
{

CCollectors::CCollectors()
{
  MON_MUTEX_INITIALIZE(collectors)
}

CCollectors::~CCollectors()
{
  MON_MUTEX_LOCK(collectors);
  for(CCollector *c : m_collectors)
  {
    delete c;
  }
  MON_MUTEX_UNLOCK(collectors);
  MON_MUTEX_DESTROY(collectors)
}

void CCollectors::addCollector(CCollector *c)
{
  MON_MUTEX_LOCK(collectors);
  m_collectors.push_back(c);
  MON_MUTEX_UNLOCK(collectors);
}

}
}
}
