/* %Id% */
#include "node_st.h"
#include "cnodecollectorsmanager.h"

namespace mon
{
namespace daemons
{
namespace node
{

CNodeCollectorsManager::CNodeCollectorsManager()
  : mon::lib::network::CSocketServer(),
    mon::lib::base::CSingletonMember(MON_COLLECTORS_MANAGER_ST_MEMBER_ID)
{}

CNodeCollectorsManager::~CNodeCollectorsManager()
{
  unlisten();
}

void CNodeCollectorsManager::listen()
{
  mon::lib::network::CSocketServer::listen(MON_ST_CONFIG->folder("network")->folder("listen")->file("port")->get(MON_DEFAULT_COLLECTOR_LISTEN_PORT));
}

void CNodeCollectorsManager::unlisten()
{
  close();
  for(CNodeRemoteCollector *collector : m_collectors)
  {
    delete collector;
  }
  m_collectors.clear();
}

mon::lib::network::CSocketClient * CNodeCollectorsManager::incommingConnection(const int &clientDescriptor, const std::string &addr_from, const int & port_from)
{
  CNodeRemoteCollector *collector = new CNodeRemoteCollector(clientDescriptor, addr_from, port_from);
  m_collectors.push_back(collector);
  return collector;
}

}
}
}
