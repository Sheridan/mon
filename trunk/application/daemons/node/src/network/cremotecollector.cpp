#include "node_st.h"
#include "cremotecollector.h"
namespace mon
{
namespace daemons
{
namespace node
{

CRemoteCollector::CRemoteCollector(int socketDescriptor, const std::string &addr_from, const int &port_from)
  : mon::lib::network::CSocketClient(socketDescriptor, addr_from, port_from),
    CNodeProtocol(this)
{
  connected(addrRemote(), portRemote());
}

CRemoteCollector::~CRemoteCollector()
{}

void CRemoteCollector::incommingMessage(const std::string &message)
{
  MON_LOG_DBG(message)
}

void CRemoteCollector::connected(const std::string &to_addr, const unsigned short &to_port)
{
  MON_LOG_DBG("CRemoteCollector " << to_addr << ":" << to_port)
}

}
}
}
