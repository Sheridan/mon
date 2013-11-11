/* %Id% */
#include "collector_st.h"
#include "cnodesmanager.h"
#include "stl-helper.h"

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
    MON_LOG_DBG(MON_STL_LIST_VALUE(folder)->name());
    m_nodes.push_back(new CRemoteNode(MON_STL_LIST_VALUE(folder)->name()));
  }
  MON_STL_LIST_FOREACH(node, TRemoteNodes, m_nodes)
  {
    MON_STL_LIST_VALUE(node)->connect();
  }
}

void CNodesManager::unload()
{
  MON_STL_LIST_FOREACH(node, TRemoteNodes, m_nodes)
  {
    delete MON_STL_LIST_VALUE(node);
  }
    m_nodes.clear();
}

}
}
}
