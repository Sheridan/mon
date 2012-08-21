/* %Id% */
#include "collector_st.h"
#include "cremotenode.h"
#include "global.h"

namespace mon
{
namespace daemons
{
namespace collector
{

CRemoteNode::CRemoteNode(const std::string &confLeaf)
  : mon::lib::network::CSocketClient(),
    CCollectorProtocol(this),
    m_configLeaf(confLeaf)
{
  MON_LOG_DBG("Node " << confLeaf << " ");
  MON_CFOLDER *folder = MON_ST_CONFIG->folder("nodes")->folder(m_configLeaf)->folder("connection");
  setTimeout                               (folder->file("timeout")->get(MON_DEFAULT_CONNECT_TIMEOUT));
  setAddrRemote                            (folder->file("host")   ->get(std::string("localhost")));
  setPortRemote(static_cast<unsigned short>(folder->file("port")   ->get(MON_DEFAULT_LISTEN_PORT)));
  MON_THREADED_FUNCTION_INIT(connect);
}

CRemoteNode::~CRemoteNode()
{
  MON_THREADED_FUNCTION_ABORT(connect)
}

MON_THREADED_FUNCTION_IMPLEMENT(CRemoteNode, connect)
{
  for(;;)
  {
    if(!isConnected())
    {
      MON_THREADED_FUNCTION_DISABLE_CANCEL
      mon::lib::network::CSocketClient::connect();
      MON_THREADED_FUNCTION_ENABLE_CANCEL
    }
    sleep(1);
  }
}

void CRemoteNode::incommingMessage(const std::string &message)
{
  MON_LOG_DBG(message)
}

void CRemoteNode::connected(const std::string &to_addr, const unsigned short &to_port)
{
  MON_LOG_DBG("CRemoteMonNode " << to_addr << ":" << to_port)
  CCollectorProtocol::connect(MON_ST_CONFIG->folder("nodes")->folder(m_configLeaf)->file("password")->get(MON_DEFAULT_PASSWORD));
  CCollectorProtocol::connect(MON_ST_CONFIG->folder("nodes")->folder(m_configLeaf)->file("password")->get(MON_DEFAULT_PASSWORD));
  CCollectorProtocol::connect(MON_ST_CONFIG->folder("nodes")->folder(m_configLeaf)->file("password")->get(MON_DEFAULT_PASSWORD));
  CCollectorProtocol::connect(MON_ST_CONFIG->folder("nodes")->folder(m_configLeaf)->file("password")->get(MON_DEFAULT_PASSWORD));
}

}
}
}
