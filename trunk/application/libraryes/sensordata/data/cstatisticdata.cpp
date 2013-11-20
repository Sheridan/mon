#include "libraryes/sensordata/data/cstatisticdata.h"
namespace mon
{
namespace lib
{
namespace sensordata
{

CStatisticData::CStatisticData(const TCacheID &id, const TData &data)
  : m_data(data), m_id(id)
{
}

CStatisticData::~CStatisticData()
{

}

TData &CStatisticData::data()
{
  return m_data;
}

TCacheID &CStatisticData::id()
{
  return m_id;
}

TData &CStatisticData::operator()()
{
  return m_data;
}

}
}
}
