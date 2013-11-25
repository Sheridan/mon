#include "libraryes/model/ccollectors.h"

namespace mon
{
namespace lib
{
namespace model
{

CCollectors::CCollectors()
  : CItems<CCollector>()
{
}

CCollectors::~CCollectors()
{
}

CCollector *CCollectors::collector(const std::string &name)
{
  return static_cast<CCollector *>(item(name));
}

}
}
}
