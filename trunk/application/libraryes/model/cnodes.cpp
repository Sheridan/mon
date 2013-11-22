#include "libraryes/model/cnodes.h"

namespace mon
{
namespace lib
{
namespace model
{

CNodes::CNodes()
{
  MON_MUTEX_INITIALIZE(nodes)
}

CNodes::~CNodes()
{
  MON_MUTEX_LOCK(nodes);
  for(CNode *n : m_nodes)
  {
    delete n;
  }
  MON_MUTEX_UNLOCK(nodes);
  MON_MUTEX_DESTROY(nodes)
}

CNode *CNodes::node(const std::string &name)
{
  CNode *result = nullptr;
  MON_MUTEX_LOCK(nodes);
  for(CNode *n : m_nodes)
  {
    if(name.compare(n->name()) == 0)
    {
      result = n;
      break;
    }
  }
  MON_MUTEX_UNLOCK(nodes);
  return result;
}

void CNodes::addNode(CNode *node)
{
  MON_MUTEX_LOCK(nodes);
  m_nodes.push_back(node);
  MON_MUTEX_UNLOCK(nodes);
}

}
}
}
