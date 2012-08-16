/* %Id% */
#ifndef CMONNODESMANAGER_H
#define CMONNODESMANAGER_H
#include "csingletonmember.h"
#include "cremotemonnode.h"

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
  void unload();
private:
  TRemoteMonNodes m_nodes;
};

}
}
}
#endif // CMONNODESMANAGER_H
