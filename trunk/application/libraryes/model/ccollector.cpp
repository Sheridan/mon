#include "libraryes/model/ccollector.h"

namespace mon
{
namespace lib
{
namespace model
{

CCollector::CCollector(const std::string &name)
  : CItems<CNode>(),
    m_name(name)
{
}

CCollector::~CCollector()
{

}

}
}
}
