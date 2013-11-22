/* %Id% */
#include "daemons/collector/collector_st.h"
#include "daemons/collector/node/cnodes.h"

namespace mon
{
namespace daemons
{
namespace collector
{

CNodes::CNodes()
  : mon::lib::model::CNodes(),
    mon::lib::base::CSingletonMember(MON_NODES_MANAGER_ST_MEMBER_ID)
{}

CNodes::~CNodes()
{}

void CNodes::load()
{
  MON_LOG_DBG("Load nodes");
  CNode *n;
  MON_OPTION_FOREACH_FOLDER(folder, MON_ST_CONFIG->folder("nodes"))
  {
    n = new CNode(folder->name());
    addNode(n);
    n->connect();
  }
}


}
}
}
