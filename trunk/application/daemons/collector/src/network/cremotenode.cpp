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
  for(auto &sensor : m_nodeSensors)
  {
    delete sensor;
  }
  m_nodeSensors.clear();
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

void CRemoteNode::connected(const std::string &to_addr, const unsigned short &to_port)
{
  MON_LOG_DBG("Collector connected to " << to_addr << ":" << to_port);
  CCollectorProtocol::connect(m_selfConfig->file("password")->get(MON_DEFAULT_PASSWORD));
}

void CRemoteNode::incommingMessage(const std::string &message)
{
  mon::lib::protocol::CProtocol::incommingMessage(message);
}

void CRemoteNode::incomingAnswerOnConnect(lib::protocol::CNetworkMessage *msg)
{
  if(msg->string().compare("t") == 0)
  {
    MON_LOG_NFO("Connection allowed");
    requestSensorsList();
  }
  else if(msg->string().compare("f") == 0)
  {
    MON_LOG_ERR("Connection denyed");
    MON_ABORT;
  }
}

void CRemoteNode::incomingAnswerOnRequestSensorList(lib::protocol::CNetworkMessage *msg)
{
  std::list<std::string> sensorsNames;
  mon::lib::base::split(msg->string(), ':', sensorsNames);
  for(auto &sensor_name : sensorsNames)
  {
    requestSensorDefinition(sensor_name);
  }
}

void CRemoteNode::incomingAnswerOnrequestSensorDefinition(lib::protocol::CNetworkMessage *msg)
{
  int index   = msg->string().find(MON_PROTOCOL_DELIMITER(sensorname ,definition));
  CRemoteNodeSensor *rnSensor = new CRemoteNodeSensor(msg->string().substr(0, index),
                                                      msg->string().substr(index, msg->string().length()-1),
                                                      this);
  m_nodeSensors.push_back(rnSensor);
}

}
}
}
