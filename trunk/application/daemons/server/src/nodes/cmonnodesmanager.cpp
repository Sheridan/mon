#include "../server_st.h"
#include "cmonnodesmanager.h"

#define MON_FOREACH_NODE(_name) \
   for(mon::daemons::server::TMonNodes::iterator _name = m_nodes.begin(); \
    _name != m_nodes.end(); \
    ++_name)

namespace mon
{
namespace daemons
{
namespace server
{

CMonNodesManager::CMonNodesManager() : mon::lib::base::CSingletonMember(MON_SERVER_NODES_MANAGER_ST_MEMBER_ID)
{}

CMonNodesManager::~CMonNodesManager()
{}

void CMonNodesManager::load()
{
  MON_LOG_DBG("load");
  TMonNodeID currentNodeID = 0;
  MON_OPTION_FOREACH_FOLDER(fit, MON_ST_CONFIG->folder(MON_MODULE_NAME)->folder("nodes"))
  {
    MON_LOG_DBG(*fit);
    m_nodes[currentNodeID] = new CMonNode(*fit, currentNodeID);
    currentNodeID++;
  }
  MON_FOREACH_NODE(node)
  {
    node->second->connect();
  }
}

}
}
}
