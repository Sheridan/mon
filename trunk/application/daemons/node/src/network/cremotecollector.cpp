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
  MON_LOG_DBG("----- Incoming message: " << message);
  mon::lib::protocol::CMessage t_incomming_message(message);
  switch(t_incomming_message.type())
  {
    case MON_PROTO_ID_COLLECTOR_TO_NODE_CONNECT:
    {
      sendMessage(MON_PROTO_ID_CONNECT_ANSWER,
                  t_incomming_message.msg().compare(MON_ST_CONFIG->file("password")->get(MON_DEFAULT_PASSWORD)) == 0 ? "t" : "f" );
      break;
    }
  }
}

void CRemoteCollector::connected(const std::string &to_addr, const unsigned short &to_port)
{}

}
}
}
