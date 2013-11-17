/* %Id% */
#include "collector_st.h"
#include "cremotenode.h"
#include "global.h"
#include "stringhelper.h"
#include "infinity-cycle-helper.h"
#include "cfrequency.h"

namespace mon
{
namespace daemons
{
namespace collector
{

CRemoteNode::CRemoteNode(const std::string &name)
  : mon::lib::network::CSocketClient(),
    CCollectorProtocol(this),
    mon::lib::base::CTimer(),
    m_name(name)
{
  MON_MUTEX_INITIALIZE(node_sensors)
  MON_LOG_DBG("Node " << m_name << " ");
  mon::lib::config::CFolder *selfCfg  = MON_ST_CONFIG->folder("nodes")->folder(m_name);
  setTimeout   (selfCfg->folder("connection")->file("timeout")->get(MON_DEFAULT_CONNECT_TIMEOUT));
  setAddrRemote(selfCfg->folder("connection")->file("host")   ->get(std::string("localhost")));
  setPortRemote(selfCfg->folder("connection")->file("port")   ->get(MON_DEFAULT_LISTEN_PORT));
  MON_THREADED_FUNCTION_INIT(connect);
  float timerTimeout = MON_DEFAULT_REMOTE_NODE_DATA_REQUEST_TIMEOUT;
  if(selfCfg->folder("request")->folder("frequency")->containsFile("hz"))
  {
    timerTimeout = selfCfg->folder("request")->folder("frequency")->file("hz")->get(mon::lib::sensordata::SPP2Hz(MON_DEFAULT_REMOTE_NODE_DATA_REQUEST_TIMEOUT));
  }
  else if(selfCfg->folder("request")->folder("frequency")->containsFile("spp"))
  {
    timerTimeout = selfCfg->folder("request")->folder("frequency")->file("spp")->get(MON_DEFAULT_REMOTE_NODE_DATA_REQUEST_TIMEOUT);
  }
  else
  {
    selfCfg->folder("request")->folder("frequency")->file("hz")->set(mon::lib::sensordata::SPP2Hz(timerTimeout));
  }
  settimeout(timerTimeout);
}

CRemoteNode::~CRemoteNode()
{
  timerStop();
  MON_THREADED_FUNCTION_ABORT(connect)
  MON_MUTEX_LOCK(node_sensors)
  for(auto &sensor : m_nodeSensors)
  {
    delete sensor;
  }
  m_nodeSensors.clear();
  MON_MUTEX_UNLOCK(node_sensors)
  MON_MUTEX_DESTROY(node_sensors)
}

void CRemoteNode::onTimer()
{
  if(isConnected())
  {
    MON_MUTEX_LOCK(node_sensors)
    for(CRemoteNodeSensor *sensor : m_nodeSensors)
    {
      for(std::string &frameName : sensor->frames())
      {
        requestSensorFrameStatistic(sensor->name(), frameName);
      }
    }
    MON_MUTEX_UNLOCK(node_sensors)
  }
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
    usleep(500000);
  MON_INFINITY_LOOP_END(reconnect_loop)
}

void CRemoteNode::connected(const std::string &to_addr, const unsigned short &to_port)
{
  MON_LOG_DBG("Collector connected to " << to_addr << ":" << to_port);
  CCollectorProtocol::connect(MON_ST_CONFIG->folder("nodes")->folder(m_name)->file("password")->get(MON_DEFAULT_PASSWORD));
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
    timerStart();
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
  for(std::string &sensor_name : sensorsNames)
  {
    requestSensorDefinition(sensor_name);
  }
}

void CRemoteNode::incomingAnswerOnRequestSensorDefinition(lib::protocol::CNetworkMessage *msg)
{
  int index   = msg->string().find(MON_PROTOCOL_DELIMITER(sensorname ,definition));
//  MON_LOG_DBG("Sensor name: " << msg->string().substr(0, index)
//              << ", definition: " << msg->string().substr(index, msg->string().length()-1))
  CRemoteNodeSensor *rnSensor = new CRemoteNodeSensor(msg->string().substr(0, index),
                                                      msg->string().substr(index+1, msg->string().length()-1),
                                                      this);
  MON_MUTEX_LOCK(node_sensors)
  m_nodeSensors.push_back(rnSensor);
  MON_MUTEX_UNLOCK(node_sensors)
}

void CRemoteNode::incomingAnswerOnRequestSensorFrameStatistic(lib::protocol::CNetworkMessage *msg)
{
  MON_LOG_DBG(msg->string());
}


}
}
}
