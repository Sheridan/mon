/* %Id% */
#include "node_st.h"
#include "cremotecollector.h"
#include "protocol-control.h"
#include "global.h"

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

void CRemoteCollector::connected(const std::string &to_addr, const unsigned short &to_port)
{}

void CRemoteCollector::incommingMessage(const std::string &message)
{
  mon::lib::protocol::CProtocol::incommingMessage(message);
}

void CRemoteCollector::requestOfConnect(lib::protocol::CNetworkMessage *msg)
{
  sendReply(msg, msg->string().compare(MON_ST_CONFIG->file("password")->get(MON_DEFAULT_PASSWORD)) == 0 ? "t" : "f" );
}

void CRemoteCollector::requestOfSensorsList(lib::protocol::CNetworkMessage *msg)
{
  sendReply(msg, MON_ST_SENSORS_MANAGER->getGensorsNamesList());
}

void CRemoteCollector::requestOfSensorDefinition(lib::protocol::CNetworkMessage *msg)
{
  MON_LOG_DBG(msg->string());
  sendReply(msg, msg->string() +
                 std::to_string(MON_PROTOCOL_DELIMITER(sensorname ,definition)) +
                 MON_ST_SENSORS_MANAGER->sensor(msg->string())->getDefinition());
}

}
}
}
