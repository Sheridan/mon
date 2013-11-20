/* %Id% */
#include "defines/global.h"
#include "defines/protocol-control.h"
#include "daemons/node/node_st.h"
#include "daemons/node/collector/ccollector.h"

namespace mon
{
namespace daemons
{
namespace node
{

CCollector::CCollector(int socketDescriptor, const std::string &addr_from, const int &port_from)
  : mon::lib::network::CSocketClient(socketDescriptor, addr_from, port_from),
    CNodeProtocol(this)
{
  connected(addrRemote(), portRemote());
}

CCollector::~CCollector()
{}

void CCollector::connected(const std::string &to_addr, const unsigned short &to_port)
{}

void CCollector::incommingMessage(const std::string &message)
{
  mon::lib::protocol::CProtocol::incommingMessage(message);
}

void CCollector::requestOfConnect(lib::protocol::CNetworkMessage *msg)
{
  sendReply(msg, msg->string().compare(MON_ST_CONFIG->file("password")->get(MON_DEFAULT_PASSWORD)) == 0 ? "t" : "f" );
}

void CCollector::requestOfSensorsList(lib::protocol::CNetworkMessage *msg)
{
  sendReply(msg, MON_ST_SENSORS_MANAGER->getGensorsNamesList(MON_PROTOCOL_DELIMITER(sensorname ,sensorname)));
}

void CCollector::requestOfSensorDefinition(lib::protocol::CNetworkMessage *msg)
{
  sendReply(msg, msg->string() +
                 MON_PROTOCOL_DELIMITER(sensorname ,definition) +
                 MON_ST_SENSORS_MANAGER->sensor(msg->string())->getDefinition());
}

void CCollector::requestSensorFrameStatistic(lib::protocol::CNetworkMessage *msg)
{
  int sensorIndex = msg->string().find(MON_PROTOCOL_DELIMITER(sensorname ,framename));
  std::string sensor = msg->string().substr(0, sensorIndex);
  std::string frame  = msg->string().substr(sensorIndex+1, msg->string().length()-1);
  sendReply(msg, msg->string() +
            MON_PROTOCOL_DELIMITER(framename  ,statistic) +
            MON_ST_SENSORS_MANAGER->sensor(sensor)->frame(frame)->requestCachedData());
}

}
}
}
