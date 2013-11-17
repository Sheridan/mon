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

typedef std::list<CRemoteCollector *> TRemoteCollectors;

}
}
}
#endif // CREMOTECOLLECTOR_H
