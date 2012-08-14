#include "cfile.h"
#include "cfolder.h"

namespace mon
{
namespace lib
{
namespace config
{

CFile::CFile(const std::string &nodeName, CNode *parentNode) : CNode(nodeName, parentNode), CVariant()
{
}

CFile::~CFile()
{
}

CFolder * CFile::parent()
{
  return static_cast<CFolder *>(CNode::parent());
}

}
}
}

