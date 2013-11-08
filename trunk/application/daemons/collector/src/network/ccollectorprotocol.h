/* %Id% */
#ifndef CCOLLECTORPROTOCOL_H
#define CCOLLECTORPROTOCOL_H

#include "cprotocol.h"

namespace mon
{
namespace daemons
{
namespace collector
{

class CCollectorProtocol : public mon::lib::protocol::CProtocol
{
  public:
    CCollectorProtocol(mon::lib::network::CSocket *socket);
    ~CCollectorProtocol();
    void connect (const std::string &password);
    void requestSensorsList();
    void requestSensorDefinition(const std::string &sensor);
  protected:
    virtual void incomingAnswerOnConnect(mon::lib::protocol::CNetworkMessage *msg) = 0;
    virtual void incomingAnswerOnRequestSensorList(mon::lib::protocol::CNetworkMessage *msg) = 0;
    virtual void incomingAnswerOnrequestSensorDefinition(mon::lib::protocol::CNetworkMessage *msg) = 0;
};

}
}
}
#endif // CCOLLECTORPROTOCOL_H
