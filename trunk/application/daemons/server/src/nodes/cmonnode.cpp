/* %Id% */
#include "../server_st.h"
#include "cmonnode.h"

namespace mon
{
namespace daemons
{
namespace server
{

CMonNode::CMonNode(const std::string &confLeaf, const TMonNodeID &nodeID)
{
  m_configLeaf = confLeaf;
  m_id = nodeID;
  MON_LOG_DBG("Node " << confLeaf << " " << nodeID);
  m_socket = new mon::lib::network::CSocketClient();
  MON_CFOLDER *folder = MON_ST_CONFIG->folder("nodes")->folder(m_configLeaf)->folder("connection");
  m_socket->setTimeout                               (folder->file("timeout")->get(30));
  m_socket->setAddrRemote                            (folder->file("host")   ->get(std::string("localhost")));
  m_socket->setPortRemote(static_cast<unsigned short>(folder->file("port")   ->get(4848)));
  MON_THREADED_FUNCTION_INIT(connect);
}

CMonNode::~CMonNode()
{
  MON_THREADED_FUNCTION_ABORT(connect)
  delete m_socket;
}

MON_THREADED_FUNCTION_IMPLEMENT(CMonNode, connect)
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

const TMonNodeID &CMonNode::id() const
{
  return m_id;
}

}
}
}
