/* %Id% */
#ifndef CNODEPROTOCOL_H
#define CNODEPROTOCOL_H

#include "cprotocol.h"

namespace mon
{
namespace daemons
{
namespace node
{

//! Реализация сетевого протокола для ноды
class CNodeProtocol : public mon::lib::protocol::CProtocol
{
  public:
    CNodeProtocol(mon::lib::network::CSocket *socket);
    ~CNodeProtocol();
  protected:
    virtual void requestOfConnect(lib::protocol::CNetworkMessage *msg) = 0;
    virtual void requestOfSensorsList(lib::protocol::CNetworkMessage *msg) = 0;
    virtual void requestOfSensorDefinition(lib::protocol::CNetworkMessage *msg) = 0;
};

}
}
}
#endif // CNODEPROTOCOL_H
