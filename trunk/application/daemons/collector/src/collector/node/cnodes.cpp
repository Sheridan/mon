/* %Id% */
#include "collector_st.h"
#include "collector/node/cnodes.h"

namespace mon
{
namespace daemons
{
namespace collector
{

CNodes::CNodes() : mon::lib::base::CSingletonMember(MON_NODES_MANAGER_ST_MEMBER_ID)
{}

CNodes::~CNodes()
{
  unload();
}

void CNodes::load()
{
  MON_LOG_DBG("Load nodes");
  MON_OPTION_FOREACH_FOLDER(folder, MON_ST_CONFIG->folder("nodes"))
  {
    m_nodes.push_back(new CNode(folder->name()));
  }
  for(CNode *node : m_nodes)
  {
    node->connect();
  }
}

void CNodes::unload()
{
  for(CNode *node : m_nodes)
  {
    delete node;
  }
  m_nodes.clear();
}

}
}
}
