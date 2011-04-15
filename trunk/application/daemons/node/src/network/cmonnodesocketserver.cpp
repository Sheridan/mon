#include "cmonnodesocketserver.h"
#include "../node_st.h"

namespace mon
{
namespace daemons
{
namespace node
{

CMonNodeSocketServer::CMonNodeSocketServer()
  : mon::lib::network::CSocketServer(), mon::lib::base::CSingletonMember(MON_NODE_SOCKET_SERVER_ST_MEMBER_ID)
{
  //ctor
}

CMonNodeSocketServer::~CMonNodeSocketServer()
{
  //dtor
}

void CMonNodeSocketServer::listen()
{
  mon::lib::network::CSocketServer::listen(MON_ST_CONFIG->folder("network")->folder("listen")->file("port")->get(4848));
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
