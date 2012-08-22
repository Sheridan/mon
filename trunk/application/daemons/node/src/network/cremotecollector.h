/* %Id% */
#ifndef CREMOTECOLLECTOR_H
#define CREMOTECOLLECTOR_H
#include "cclientsocket.h"
#include "class-helper.h"
#include "cnodeprotocol.h"
#include <list>
#include <string>
namespace mon
{
namespace daemons
{
namespace node
{

class CRemoteCollector : public mon::lib::network::CSocketClient, public CNodeProtocol
{
  public:
    CRemoteCollector(int socketDescriptor, const std::string &addr_from, const int & port_from);
    virtual ~CRemoteCollector();

  private:
    mon::lib::config::CFolder *m_selfConfig;

    void incommingMessage(const std::string &message);
    void connected(const std::string &to_addr, const unsigned short &to_port);
};

typedef std::list<CRemoteCollector *> TRemoteCollectors;

}
}
}
#endif // CREMOTECOLLECTOR_H
