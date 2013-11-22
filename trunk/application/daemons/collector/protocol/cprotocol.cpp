/* %Id% */
#include "daemons/collector/collector_st.h"
#include "daemons/collector/protocol/cprotocol.h"

namespace mon
{
namespace daemons
{
namespace collector
{

CProtocol::CProtocol(mon::lib::network::CSocket *socket) : mon::lib::protocol::CProtocol(socket)
{
}

CProtocol::~CProtocol()
{}

void CProtocol::connect(const std::string &password)
{
  sendMessage(static_cast<mon::lib::protocol::TMessageCallback>(&mon::daemons::collector::CProtocol::incomingAnswerOnConnect),
              mon::lib::protocol::mtConnect, password);
}

void CProtocol::requestSensorsList()
{
  sendMessage(static_cast<mon::lib::protocol::TMessageCallback>(&mon::daemons::collector::CProtocol::incomingAnswerOnRequestSensorList),
              mon::lib::protocol::mtRequestSensorsList);
}

void CProtocol::requestSensorDefinition(const std::string &sensor)
{
    sendMessage(static_cast<mon::lib::protocol::TMessageCallback>(&mon::daemons::collector::CProtocol::incomingAnswerOnRequestSensorDefinition),
                mon::lib::protocol::mtRequestSensorDefinition, sensor);
}

void CProtocol::requestSensorFrameStatistic(const std::string &sensor, const std::string &frame)
{
  sendMessage(static_cast<mon::lib::protocol::TMessageCallback>(&mon::daemons::collector::CProtocol::incomingAnswerOnRequestSensorFrameStatistic),
              mon::lib::protocol::mtRequestSensorFrameStatistic, sensor + MON_PROTOCOL_DELIMITER(sensorname ,framename) + frame);
}

}
}
}
