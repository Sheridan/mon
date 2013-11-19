/* %Id% */
#include "collector_st.h"
#include "ccollectornodesmanager.h"

namespace mon
{
namespace daemons
{
namespace collector
{

CCollectorNodesManager::CCollectorNodesManager() : mon::lib::base::CSingletonMember(MON_NODES_MANAGER_ST_MEMBER_ID)
{}

CCollectorNodesManager::~CCollectorNodesManager()
{
  unload();
}

void CCollectorNodesManager::load()
{
  MON_LOG_DBG("Load nodes");
  MON_OPTION_FOREACH_FOLDER(folder, MON_ST_CONFIG->folder("nodes"))
  {
    m_nodes.push_back(new CCollectorRemoteNode(folder->name()));
  }
  for(CCollectorRemoteNode *node : m_nodes)
  {
    node->connect();
  }
}

void CCollectorNodesManager::unload()
{
  for(CCollectorRemoteNode *node : m_nodes)
  {
    delete node;
  }
  m_nodes.clear();
}

}
}
}
