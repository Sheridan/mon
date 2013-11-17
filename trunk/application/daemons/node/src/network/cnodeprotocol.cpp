/* %Id% */
#include "cnodeprotocol.h"
namespace mon
{
namespace daemons
{
namespace node
{

CNodeProtocol::CNodeProtocol(mon::lib::network::CSocket *socket) : mon::lib::protocol::CProtocol(socket)
{
  registerIntercept(mon::lib::protocol::mtConnect,
                    static_cast<mon::lib::protocol::TMessageCallback>(&mon::daemons::node::CNodeProtocol::requestOfConnect));
  registerIntercept(mon::lib::protocol::mtRequestSensorsList,
                    static_cast<mon::lib::protocol::TMessageCallback>(&mon::daemons::node::CNodeProtocol::requestOfSensorsList));
  registerIntercept(mon::lib::protocol::mtRequestSensorDefinition,
                    static_cast<mon::lib::protocol::TMessageCallback>(&mon::daemons::node::CNodeProtocol::requestOfSensorDefinition));
  registerIntercept(mon::lib::protocol::mtRequestSensorFrameStatistic,
                    static_cast<mon::lib::protocol::TMessageCallback>(&mon::daemons::node::CNodeProtocol::requestSensorFrameStatistic));
}

CNodeProtocol::~CNodeProtocol()
{

}

}
}
}
