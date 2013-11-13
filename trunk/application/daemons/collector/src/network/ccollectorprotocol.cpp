/* %Id% */
#include "ccollectorprotocol.h"
#include "collector_st.h"
namespace mon
{
namespace daemons
{
namespace collector
{

CCollectorProtocol::CCollectorProtocol(mon::lib::network::CSocket *socket) : mon::lib::protocol::CProtocol(socket)
{
}

CCollectorProtocol::~CCollectorProtocol()
{}

void CCollectorProtocol::connect(const std::string &password)
{
  sendMessage(static_cast<mon::lib::protocol::TMessageCallback>(&mon::daemons::collector::CCollectorProtocol::incomingAnswerOnConnect),
              mon::lib::protocol::mtConnect, password);
}

void CCollectorProtocol::requestSensorsList()
{
  sendMessage(static_cast<mon::lib::protocol::TMessageCallback>(&mon::daemons::collector::CCollectorProtocol::incomingAnswerOnRequestSensorList),
              mon::lib::protocol::mtRequestSensorsList);
}

void CCollectorProtocol::requestSensorDefinition(const std::string &sensor)
{
    sendMessage(static_cast<mon::lib::protocol::TMessageCallback>(&mon::daemons::collector::CCollectorProtocol::incomingAnswerOnrequestSensorDefinition),
                mon::lib::protocol::mtRequestSensorDefinition);
}

}
}
}
