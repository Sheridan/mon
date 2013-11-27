#include "defines/st.h"
#include "libraryes/model/cnode.h"

namespace mon
{
namespace lib
{
namespace model
{

CNode::CNode(const std::string &name)
  : CItems<CSensor>(),
    m_name(name)
{
}

CNode::~CNode()
{
}

CSensor *CNode::sensor(const std::string &name)
{
  return static_cast<CSensor *>(item(name));
}

}
}
}
