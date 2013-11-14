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

//! Удаленный коллектор
class CRemoteCollector : public mon::lib::network::CSocketClient, public CNodeProtocol
{
  public:
    CRemoteCollector(int socketDescriptor, const std::string &addr_from, const int & port_from);
    virtual ~CRemoteCollector();

  private:
    mon::lib::config::CFolder *m_selfConfig;
    void incommingMessage(const std::string &message) final;

    void connected(const std::string &to_addr, const unsigned short &to_port) final;
    void requestOfConnect(lib::protocol::CNetworkMessage *msg) final;
    void requestOfSensorsList(lib::protocol::CNetworkMessage *msg) final;
    void requestOfSensorDefinition(lib::protocol::CNetworkMessage *msg) final;
};

typedef std::list<CRemoteCollector *> TRemoteCollectors;

}
}
}
#endif // CREMOTECOLLECTOR_H
