/* %Id% */
#ifndef CNODEREMOTECOLLECTOR_H
#define CNODEREMOTECOLLECTOR_H
#include "libraryes/network/cclientsocket.h"
#include "defines/class-helper.h"
#include "daemons/node/protocol/cnodeprotocol.h"
#include <list>
#include <string>
namespace mon
{
namespace daemons
{
namespace node
{

//! Удаленный коллектор
class CCollector : public mon::lib::network::CSocketClient, public CNodeProtocol
{
  public:
    CCollector(int socketDescriptor, const std::string &addr_from, const int & port_from);
    virtual ~CCollector();

  private:
    //! Заглушка из за архитектурного недостатка
    void incommingMessage(const std::string &message) final;
    //! Вызывается при успешном коннекте сокета к ноде
    void connected(const std::string &to_addr, const unsigned short &to_port) final;
    //! Вызывается при запросе коннекта с паролем
    void requestOfConnect(lib::protocol::CNetworkMessage *msg) final;
    //! Вызывается при запросе списка сенсоров
    void requestOfSensorsList(lib::protocol::CNetworkMessage *msg) final;
    //! Вызывается при запросе определения сенсора
    void requestOfSensorDefinition(lib::protocol::CNetworkMessage *msg) final;
    //! Вызывается при запросе статистики фрейма
    void requestSensorFrameStatistic(lib::protocol::CNetworkMessage *msg) final;
};

typedef std::list<CCollector *> TCollectors;

}
}
}
#endif // CNODEREMOTECOLLECTOR_H
