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

class CNodeProtocol : public mon::lib::protocol::CProtocol
{
  public:
    CNodeProtocol(mon::lib::network::CSocket *socket);
    ~CNodeProtocol();
};

}
}
}
#endif // CNODEPROTOCOL_H
