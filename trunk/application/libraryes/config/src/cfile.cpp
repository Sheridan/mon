#include "cfile.h"

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

}
}
}

