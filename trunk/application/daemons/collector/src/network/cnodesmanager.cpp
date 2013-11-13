/* %Id% */
#include "collector_st.h"
#include "cnodesmanager.h"

namespace mon
{
namespace daemons
{
namespace collector
{

CNodesManager::CNodesManager() : mon::lib::base::CSingletonMember(MON_NODES_MANAGER_ST_MEMBER_ID)
{}

CNodesManager::~CNodesManager()
{
  unload();
}

void CNodesManager::load()
{
  MON_LOG_DBG("Load nodes");
  MON_OPTION_FOREACH_FOLDER(folder, MON_ST_CONFIG->folder("nodes"))
  {
    MON_LOG_DBG(folder->name());
    m_nodes.push_back(new CRemoteNode(folder->name()));
  }
  for(auto &node : m_nodes)
  {
    node->connect();
  }
}

void CNodesManager::unload()
{
  for(auto &node : m_nodes)
  {
    delete node;
  }
  m_nodes.clear();
}

}
}
}
