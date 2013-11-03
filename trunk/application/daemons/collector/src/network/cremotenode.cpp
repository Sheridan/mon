/* %Id% */
#include "collector_st.h"
#include "cremotenode.h"
#include "global.h"
#include "stringhelper.h"
#include "infinity-cycle-helper.h"

namespace mon
{
namespace daemons
{
namespace collector
{

CRemoteNode::CRemoteNode(const std::string &confLeaf)
  : mon::lib::network::CSocketClient(),
    CCollectorProtocol(this)
{
  MON_LOG_DBG("Node " << confLeaf << " ");
  m_selfConfig = MON_ST_CONFIG->folder("nodes")->folder(confLeaf);
  setTimeout                               (m_selfConfig->folder("connection")->file("timeout")->get(MON_DEFAULT_CONNECT_TIMEOUT));
  setAddrRemote                            (m_selfConfig->folder("connection")->file("host")   ->get(std::string("localhost")));
  setPortRemote(static_cast<unsigned short>(m_selfConfig->folder("connection")->file("port")   ->get(MON_DEFAULT_LISTEN_PORT)));
  MON_THREADED_FUNCTION_INIT(connect);
}

CRemoteNode::~CRemoteNode()
{
  MON_THREADED_FUNCTION_ABORT(connect)
}

MON_THREADED_FUNCTION_IMPLEMENT(CRemoteNode, connect)
{
  MON_INFINITY_LOOP_BEGIN(reconnect_loop)
    MON_THREADED_ABORT_IF_NEED(connect);
    if(!isConnected())
    {
      MON_THREADED_FUNCTION_DISABLE_CANCEL
      mon::lib::network::CSocketClient::connect();
      MON_THREADED_FUNCTION_ENABLE_CANCEL
    }
    sleep(1);
  MON_INFINITY_LOOP_END(reconnect_loop)
}

void CRemoteNode::incommingMessage(const std::string &message)
{
  MON_LOG_DBG("Incoming message from node: " << message);
  mon::lib::protocol::CMessage t_incomming_message(message);
  switch(t_incomming_message.type())
  {
    case MON_PROTO_ID_CONNECT_ANSWER:
    {
      if(t_incomming_message.msg().compare("t") == 0)
      {
        MON_LOG_NFO("Connection allowed")
        requestSensorsList();
      }
      else if(t_incomming_message.msg().compare("f") == 0)
      {
        MON_LOG_ERR("Connection denyed")
      }
      else
      {
        MON_LOG_DBG("Strange answer" << message)
      }
      break;
    }
    case MON_PROTO_ID_ANSWER_NODE_SENSORS_LIST:
    {
      std::vector<std::string> sensorsNames;
      mon::lib::base::split(t_incomming_message.msg(), ':', sensorsNames);
      for(std::vector<std::string>::iterator sensorName = sensorsNames.begin(); sensorName != sensorsNames.end(); ++sensorName)
      {
        CRemoteNodeSensor *rnSensor = new CRemoteNodeSensor(*(sensorName), this);
        m_nodeSensors.push_back(rnSensor);
      }
    }
    default: CCollectorProtocol::incommingMessage(message);
  }
}

void CRemoteNode::connected(const std::string &to_addr, const unsigned short &to_port)
{
  MON_LOG_DBG("Collector connected to " << to_addr << ":" << to_port);
  CCollectorProtocol::connect(m_selfConfig->file("password")->get(MON_DEFAULT_PASSWORD));
}

}
}
}
