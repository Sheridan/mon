/* %Id% */
#include "node_st.h"
#include "cremotecollector.h"
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

void CRemoteCollector::incommingMessage(const std::string &message)
{
  MON_LOG_DBG("Incoming message from collector: " << message);
  mon::lib::protocol::CNetworkMessage t_incomming_message(message);
  switch(t_incomming_message.type())
  {
    case MON_PROTO_ID_COLLECTOR_TO_NODE_CONNECT:
    {
      sendMessage(MON_PROTO_ID_CONNECT_ANSWER,
                  t_incomming_message.msg().compare(MON_ST_CONFIG->file("password")->get(MON_DEFAULT_PASSWORD)) == 0 ? "t" : "f" );
      break;
    }
    case MON_PROTO_ID_REQUEST_NODE_SENSORS_LIST:
    {
      sendMessage(MON_PROTO_ID_ANSWER_NODE_SENSORS_LIST, MON_ST_SENSORS_MANAGER->getGensorsNamesList());
      break;
    }
    case MON_PROTO_ID_REQUEST_SENSOR_DEFINITION:
    {
      sendMessage(MON_PROTO_ID_ANSWER_SENSOR_DEFINITION, MON_ST_SENSORS_MANAGER->sensor(t_incomming_message.msg())->getDefinition(NULL));
      break;
    }
    default: CNodeProtocol::incommingMessage(message);
  }
}

void CRemoteCollector::connected(const std::string &to_addr, const unsigned short &to_port)
{}

}
}
}
