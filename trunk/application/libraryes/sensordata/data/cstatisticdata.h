#ifndef CSTATISTICDATA_H
#define CSTATISTICDATA_H
#include <string>
#include <list>
#include <map>

namespace mon
{
namespace lib
{
namespace sensordata
{

typedef unsigned int TCacheID;
typedef std::list<std::string> TData;

class CStatisticData
{
  public:
    CStatisticData(const TCacheID &id, const TData &data);
    virtual ~CStatisticData();
    TData &data();
    TCacheID &id();
    TData &operator()();

  private:
    TData   m_data;
    TCacheID m_id;
};

}
}
}
#endif // CSTATISTICDATA_H
