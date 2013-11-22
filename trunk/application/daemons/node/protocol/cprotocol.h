/* %Id% */
#ifndef CNODEPROTOCOL_H
#define CNODEPROTOCOL_H

#include "libraryes/protocol/cprotocol.h"

namespace mon
{
namespace daemons
{
namespace node
{

//! Реализация сетевого протокола для ноды
class CProtocol : public mon::lib::protocol::CProtocol
{
  public:
    CProtocol(mon::lib::network::CSocket *socket);
    ~CProtocol();
  protected:
    virtual void requestOfConnect(lib::protocol::CNetworkMessage *msg) = 0;
    virtual void requestOfSensorsList(lib::protocol::CNetworkMessage *msg) = 0;
    virtual void requestOfSensorDefinition(lib::protocol::CNetworkMessage *msg) = 0;
    virtual void requestSensorFrameStatistic(lib::protocol::CNetworkMessage *msg) = 0;
};

}
}
}
#endif // CNODEPROTOCOL_H
