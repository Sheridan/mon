/* %Id% */
#include "libraryes/config/model/cnode.h"
namespace mon
{
namespace lib
{
namespace config
{

CNode::CNode(const std::string &nodeName, CNode *parentNode) : m_name(nodeName), m_parent(parentNode)
{}

CNode::~CNode()
{}

const std::string &CNode::name()
{
  return m_name;
}

CNode *CNode::parent()
{
  return m_parent;
}

int CNode::level()
{
  if(m_parent) { return m_parent->level() + 1; }
  return -1;
}

}
}
}
