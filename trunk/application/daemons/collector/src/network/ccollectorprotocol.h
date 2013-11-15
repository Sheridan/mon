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

//! Реализация сетевого протокола для коллектора
class CCollectorProtocol : public mon::lib::protocol::CProtocol
{
  public:
    CCollectorProtocol(mon::lib::network::CSocket *socket);
    ~CCollectorProtocol();
    //! Запрос подключения
    void connect (const std::string &password);
    //! Запрос списка сенсоров ноды
    void requestSensorsList();
    //! Запрос описания сенсора
    void requestSensorDefinition(const std::string &sensor);
    //! Запрос статистики фрейма сенсора
    void requestSensorFrameStatistic(const std::string &sensor, const std::string &frame);

  protected:
    //! Вызывается при ответе на подключение
    virtual void incomingAnswerOnConnect(mon::lib::protocol::CNetworkMessage *msg) = 0;
    //! Вызывается при ответе на запрос списка сенсоров ноды
    virtual void incomingAnswerOnRequestSensorList(mon::lib::protocol::CNetworkMessage *msg) = 0;
    //! Вызывается при ответе на запрос описания сенсора
    virtual void incomingAnswerOnRequestSensorDefinition(mon::lib::protocol::CNetworkMessage *msg) = 0;
    //! Вызывается при ответе на запрос статистики фрейма сенсора
    virtual void incomingAnswerOnRequestSensorFrameStatistic(mon::lib::protocol::CNetworkMessage *msg) = 0;
};

}
}
}
#endif // CCOLLECTORPROTOCOL_H
