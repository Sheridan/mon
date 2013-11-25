#include "libraryes/model/cnodes.h"

namespace mon
{
namespace lib
{
namespace model
{

CNodes::CNodes()
  : CItems<CNode>()
{
}

CNodes::~CNodes()
{}

CNode *CNodes::node(const std::string &name)
{
  return static_cast<CNode *>(item(name));
}

}
}
}
