/* %Id% */
#include "collector_st.h"
#include "cnodesmanager.h"

#define MON_FOREACH_NODE(_name) \
   for(mon::daemons::collector::TRemoteNodes::iterator _name = m_nodes.begin(); \
    _name != m_nodes.end(); \
    ++_name)

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
  MON_LOG_DBG("load");
  MON_OPTION_FOREACH_FOLDER(folder, MON_ST_CONFIG->folder("nodes"))
  {
    MON_LOG_DBG((*folder)->name());
    m_nodes.push_back(new CRemoteNode((*folder)->name()));
  }
  MON_FOREACH_NODE(node)
  {
    (*node)->connect();
  }
}

void CNodesManager::unload()
{
    MON_FOREACH_NODE(node)
    {
      delete (*node);
    }
    m_nodes.clear();
}

}
}
}
