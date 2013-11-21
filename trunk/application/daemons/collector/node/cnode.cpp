/* %Id% */
#include "defines/global.h"
#include "defines/infinity-cycle-helper.h"
#include "daemons/collector/collector_st.h"
#include "daemons/collector/node/cnode.h"
#include "libraryes/base/string/stringhelper.h"
#include "libraryes/sensordata/data/cfrequency.h"

namespace mon
{
namespace daemons
{
namespace collector
{

CNode::CNode(const std::string &nodeName)
  : mon::lib::node::CNode(nodeName),
    mon::lib::network::CSocketClient(),
    CCollectorProtocol(this),
    mon::lib::base::CTimer()
{
  mon::lib::config::CFolder *selfCfg  = MON_ST_CONFIG->folder("nodes")->folder(name());
  setTimeout   (selfCfg->folder("connection")->file("timeout")->get(MON_DEFAULT_CONNECT_TIMEOUT));
  setAddrRemote(selfCfg->folder("connection")->file("host")   ->get(std::string("localhost")));
  setPortRemote(selfCfg->folder("connection")->file("port")   ->get(MON_DEFAULT_COLLECTOR_LISTEN_PORT));
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

CNode::~CNode()
{
  timerStop();
  MON_THREADED_FUNCTION_ABORT(connect)
}

void CNode::onTimer()
{
  if(isConnected())
  {
    for(mon::lib::node::CSensor *sensor : sensors())
    {
      for(std::string &frameName : sensor->frames())
      {
        requestSensorFrameStatistic(sensor->name(), frameName);
      }
    }
  }
}

MON_THREADED_FUNCTION_IMPLEMENT(CNode, connect)
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

void CNode::connected(const std::string &to_addr, const unsigned short &to_port)
{
  MON_LOG_DBG("Collector connected to " << to_addr << ":" << to_port);
  CCollectorProtocol::connect(MON_ST_CONFIG->folder("nodes")->folder(name())->file("password")->get(MON_DEFAULT_PASSWORD));
}

void CNode::incommingMessage(const std::string &message)
{
  mon::lib::protocol::CProtocol::incommingMessage(message);
}

void CNode::incomingAnswerOnConnect(lib::protocol::CNetworkMessage *msg)
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

void CNode::incomingAnswerOnRequestSensorList(lib::protocol::CNetworkMessage *msg)
{
  std::list<std::string> sensorsNames;
  mon::lib::base::split(msg->string(), ':', sensorsNames);
  for(std::string &sensor_name : sensorsNames)
  {
    requestSensorDefinition(sensor_name);
  }
}

void CNode::incomingAnswerOnRequestSensorDefinition(lib::protocol::CNetworkMessage *msg)
{
  int index   = msg->string().find(MON_PROTOCOL_DELIMITER(sensorname ,definition));
  addSensor(msg->string().substr(0, index),
            msg->string().substr(index+1, msg->string().length()-1));
}

void CNode::incomingAnswerOnRequestSensorFrameStatistic(lib::protocol::CNetworkMessage *msg)
{
//  MON_LOG_DBG(msg->string());
  //TODO: Парсинг и хранение статданных
}


}
}
}
