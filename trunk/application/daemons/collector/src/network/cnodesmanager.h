/* %Id% */
#ifndef CMONNODESMANAGER_H
#define CMONNODESMANAGER_H
#include "csingletonmember.h"
#include "cremotenode.h"

namespace mon
{
namespace daemons
{
namespace collector
{

class CNodesManager : public mon::lib::base::CSingletonMember
{
public:
  CNodesManager();
  virtual ~CNodesManager();
  void load();
  void unload();
private:
  TRemoteNodes m_nodes;
};

}
}
}
#endif // CMONNODESMANAGER_H
