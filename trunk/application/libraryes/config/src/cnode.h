#ifndef CNODE_H
#define CNODE_H
#include <string>

namespace mon
{
namespace lib
{
namespace config
{

class CNode
{
public:
  CNode(const std::string &nodeName, CNode *parentNode);
  virtual ~CNode();

  const std::string &name();
  CNode *parent();
private:
  std::string m_name;
  CNode *m_parent;
};

}
}
}
#endif // CNODE_H
