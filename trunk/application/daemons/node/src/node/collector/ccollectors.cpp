/* %Id% */
#include "node_st.h"
#include "node/collector/ccollectors.h"

namespace mon
{
namespace daemons
{
namespace node
{

CCollectors::CCollectors()
  : mon::lib::network::CSocketServer(),
    mon::lib::base::CSingletonMember(MON_COLLECTORS_MANAGER_ST_MEMBER_ID)
{}

CCollectors::~CCollectors()
{
  unlisten();
}

void CCollectors::listen()
{
  mon::lib::network::CSocketServer::listen(MON_ST_CONFIG->folder("network")->folder("listen")->file("port")->get(MON_DEFAULT_COLLECTOR_LISTEN_PORT));
}

void CCollectors::unlisten()
{
  close();
  for(CCollector *collector : m_collectors)
  {
    delete collector;
  }
  m_collectors.clear();
}

mon::lib::network::CSocketClient * CCollectors::incommingConnection(const int &clientDescriptor, const std::string &addr_from, const int & port_from)
{
  CCollector *collector = new CCollector(clientDescriptor, addr_from, port_from);
  m_collectors.push_back(collector);
  return collector;
}

}
}
}
