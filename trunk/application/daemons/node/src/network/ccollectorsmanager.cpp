/* %Id% */
#include "node_st.h"
#include "ccollectorsmanager.h"

namespace mon
{
namespace daemons
{
namespace node
{

CCollectorsManager::CCollectorsManager()
  : mon::lib::network::CSocketServer(), mon::lib::base::CSingletonMember(MON_COLLECTORS_MANAGER_ST_MEMBER_ID)
{}

CCollectorsManager::~CCollectorsManager()
{
  unlisten();
}

void CCollectorsManager::listen()
{
  mon::lib::network::CSocketServer::listen(MON_ST_CONFIG->folder("network")->folder("listen")->file("port")->get(MON_DEFAULT_LISTEN_PORT));
}

void CCollectorsManager::unlisten()
{
  close();
  MON_STL_LIST_FOREACH(collector, TRemoteCollectors, m_collectors)
  {
    delete MON_STL_LIST_VALUE(collector);
  }
  m_collectors.clear();
}

mon::lib::network::CSocketClient * CCollectorsManager::incommingConnection(const int &clientDescriptor, const std::string &addr_from, const int & port_from)
{
  CRemoteCollector *collector = new CRemoteCollector(clientDescriptor, addr_from, port_from);
  m_collectors.push_back(collector);
  return collector;
}

}
}
}
