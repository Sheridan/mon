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
}

CNodeProtocol::~CNodeProtocol()
{

}

}
}
}
