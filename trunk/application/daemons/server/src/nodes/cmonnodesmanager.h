#ifndef CMONNODESMANAGER_H
#define CMONNODESMANAGER_H
#include "csingletonmember.h"
#include "cmonnode.h"

namespace mon
{
namespace daemons
{
namespace server
{

class CMonNodesManager : public mon::lib::base::CSingletonMember
{
public:
  CMonNodesManager();
  virtual ~CMonNodesManager();
  void load();
private:
  TMonNodes m_nodes;
};

}
}
}
#endif // CMONNODESMANAGER_H
