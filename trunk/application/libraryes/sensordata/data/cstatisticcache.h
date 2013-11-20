#ifndef CSTATISTICCACHE_H
#define CSTATISTICCACHE_H
#include <map>
#include <list>
#include <string>
#include "defines/mutex-helper.h"
#include "libraryes/sensordata/data/cstatisticdata.h"

namespace mon
{
namespace lib
{
namespace sensordata
{

typedef std::map<TCacheID, CStatisticData *> TCashedData;

class CStatisticCache
{
    MON_MUTEX_DECLARE(cache)
  public:
    CStatisticCache();
    virtual ~CStatisticCache();
    void store(const std::string &value);
    CStatisticData *requestData();
    void freeData(CStatisticData *data);

  private:
    TCacheID requestID();
    TCacheID    m_lastID;
    TData       m_data;
    TCashedData m_cachedData;
};

}
}
}
#endif // CSTATISTICCACHE_H
