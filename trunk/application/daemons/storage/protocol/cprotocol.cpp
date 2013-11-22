/* %Id% */
#include "daemons/storage/protocol/cprotocol.h"

namespace mon
{
namespace daemons
{
namespace storage
{

CProtocol::CProtocol(mon::lib::network::CSocket *socket) : mon::lib::protocol::CProtocol(socket)
{
/*
  registerIntercept(mon::lib::protocol::mtConnect,
                    static_cast<mon::lib::protocol::TMessageCallback>(&mon::daemons::node::CProtocol::requestOfConnect));
  registerIntercept(mon::lib::protocol::mtRequestSensorsList,
                    static_cast<mon::lib::protocol::TMessageCallback>(&mon::daemons::node::CProtocol::requestOfSensorsList));
  registerIntercept(mon::lib::protocol::mtRequestSensorDefinition,
                    static_cast<mon::lib::protocol::TMessageCallback>(&mon::daemons::node::CProtocol::requestOfSensorDefinition));
  registerIntercept(mon::lib::protocol::mtRequestSensorFrameStatistic,
                    static_cast<mon::lib::protocol::TMessageCallback>(&mon::daemons::node::CProtocol::requestSensorFrameStatistic));
*/
}

CProtocol::~CProtocol()
{

}

}
}
}
