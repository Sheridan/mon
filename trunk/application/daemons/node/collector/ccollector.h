/* %Id% */
#ifndef CNODEREMOTECOLLECTOR_H
#define CNODEREMOTECOLLECTOR_H
#include <list>
#include <string>
#include "defines/class-helper.h"
#include "libraryes/network/cclientsocket.h"
#include "libraryes/model/ccollector.h"
#include "daemons/node/protocol/cprotocol.h"

namespace mon
{
namespace daemons
{
namespace node
{

//! Удаленный коллектор
class CCollector :
    public mon::lib::model::CCollector,
    public mon::lib::network::CSocketClient,
    public CProtocol
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



}
}
}
#endif // CNODEREMOTECOLLECTOR_H
