#ifndef CVALUE_H
#define CVALUE_H
#include "cnode.h"
#include "cvariant.h"

namespace mon
{
namespace lib
{
namespace config
{

class CFile : public CNode, public CVariant
{
public:
  CFile(const std::string &nodeName, CNode *parentNode);
  ~CFile();
  CFolder *parent();
};

}
}
}
#endif // CVALUE_H
