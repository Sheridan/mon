#include "ccollectorprotocol.h"
#include "collector_st.h"
namespace mon
{
namespace daemons
{
namespace collector
{

CCollectorProtocol::CCollectorProtocol(mon::lib::network::CSocket *socket) : mon::lib::protocol::CProtocol(socket)
{}

CCollectorProtocol::~CCollectorProtocol()
{}

void CCollectorProtocol::connect(const std::string &password)
{
  sendMessage(MON_PROTO_ID_COLLECTOR_TO_NODE_CONNECT, password);
}

}
}
}
