#include "cstatisticcache.h"
#include <climits>
#include "st.h"
#include "stl-helper.h"

namespace mon
{
namespace lib
{
namespace sensordata
{

CStatisticCache::CStatisticCache()
{
  MON_MUTEX_INITIALIZE(cache);
  m_lastID = 1;
}

CStatisticCache::~CStatisticCache()
{
  MON_MUTEX_LOCK(cache);
  MON_STL_MAP_FOREACH(cache, TCashedData, m_cachedData)
  {
    delete MON_STL_MAP_VALUE(cache);
  }
  m_cachedData.clear();
  MON_MUTEX_UNLOCK(cache);
  MON_MUTEX_DESTROY(cache);
}

void CStatisticCache::store(const std::string &value)
{
  MON_MUTEX_LOCK(cache);
  m_data.push_back(value);
  MON_LOG_DBG("Cashed " << static_cast<unsigned int>(m_data.size()) << " lines");
  MON_MUTEX_UNLOCK(cache);
}

CStatisticData *CStatisticCache::requestData()
{
  MON_MUTEX_LOCK(cache);
  TCacheID id = requestID();
  CStatisticData *data = new CStatisticData(id, m_data);
  m_data.clear();
  m_cachedData[id] = data;
  MON_MUTEX_UNLOCK(cache);
  return data;
}

void CStatisticCache::freeData(CStatisticData *data)
{
  MON_MUTEX_LOCK(cache);
  m_cachedData.erase(data->id());
  delete data;
  MON_MUTEX_UNLOCK(cache);
}

TCacheID CStatisticCache::requestID()
{
  if(m_lastID == UINT_MAX) { m_lastID = 1; }
  return m_lastID++;
}

}
}
}
