/* %Id% */
#include "server_st.h"
#include "cremotemonnode.h"

namespace mon
{
namespace daemons
{
namespace server
{

CRemoteMonNode::CRemoteMonNode(const std::string &confLeaf, const TMonNodeID &nodeID)
{
  m_configLeaf = confLeaf;
  m_id = nodeID;
  MON_LOG_DBG("Node " << confLeaf << " " << nodeID);
  m_socket = new mon::lib::network::CSocketClient();
  MON_CFOLDER *folder = MON_ST_CONFIG->folder("nodes")->folder(m_configLeaf)->folder("connection");
  m_socket->setTimeout                               (folder->file("timeout")->get(MON_DEFAULT_CONNECT_TIMEOUT));
  m_socket->setAddrRemote                            (folder->file("host")   ->get(std::string("localhost")));
  m_socket->setPortRemote(static_cast<unsigned short>(folder->file("port")   ->get(MON_DEFAULT_LISTEN_PORT)));
  MON_THREADED_FUNCTION_INIT(connect);
}

CRemoteMonNode::~CRemoteMonNode()
{
  MON_THREADED_FUNCTION_ABORT(connect)
  delete m_socket;
}

MON_THREADED_FUNCTION_IMPLEMENT(CRemoteMonNode, connect)
{
  for(;;)
  {
    if(!m_socket->isConnected())
    {
      m_socket->connect();
    }
    else
    {
      sleep(m_socket->timeout());
    }
  }
}

const TMonNodeID &CRemoteMonNode::id() const
{
  return m_id;
}

}
}
}
