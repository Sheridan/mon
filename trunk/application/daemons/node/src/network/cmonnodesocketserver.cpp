/* %Id% */
#include "node_st.h"
#include "cmonnodesocketserver.h"

namespace mon
{
namespace daemons
{
namespace node
{

CMonNodeSocketServer::CMonNodeSocketServer()
  : mon::lib::network::CSocketServer(), mon::lib::base::CSingletonMember(MON_NODE_SOCKET_SERVER_ST_MEMBER_ID)
{}

CMonNodeSocketServer::~CMonNodeSocketServer()
{}

void CMonNodeSocketServer::listen()
{
  mon::lib::network::CSocketServer::listen(MON_ST_CONFIG->folder("network")->folder("listen")->file("port")->get(MON_DEFAULT_LISTEN_PORT));
}

bool CMonNodeSocketServer::incommingConnection(mon::lib::network::CSocketClient *client)
{
  return true;
}

bool CMonNodeSocketServer::checkConnection(mon::lib::network::CSocketClient *client)
{
  return true;
}

}
}
}
