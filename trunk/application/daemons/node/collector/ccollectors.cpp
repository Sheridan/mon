/* %Id% */
#include "daemons/node/node_st.h"
#include "daemons/node/collector/ccollectors.h"

namespace mon
{
namespace daemons
{
namespace node
{

CCollectors::CCollectors()
  : mon::lib::model::CCollectors(),
    mon::lib::network::CSocketServer(),
    mon::lib::base::CSingletonMember(MON_COLLECTORS_MANAGER_ST_MEMBER_ID)
{}

CCollectors::~CCollectors()
{
  close();
}

void CCollectors::listen()
{
  mon::lib::network::CSocketServer::listen(MON_ST_CONFIG->folder("network")->folder("listen")->file("port")->get(MON_DEFAULT_COLLECTOR_LISTEN_PORT));
}

mon::lib::network::CSocketClient * CCollectors::incommingConnection(const int &clientDescriptor, const std::string &addr_from, const int & port_from)
{
  CCollector *tmpCollector = new CCollector(clientDescriptor, addr_from, port_from);
  add(tmpCollector);
  return tmpCollector;
}

}
}
}
