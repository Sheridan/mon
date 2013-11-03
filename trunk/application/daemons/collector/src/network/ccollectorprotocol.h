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
};

}
}
}
#endif // CCOLLECTORPROTOCOL_H
