/* %Id% */
#ifndef CREMOTEMONNODE_H
#define CREMOTEMONNODE_H
#include "cclientsocket.h"
#include "threads-helper.h"
#include "class-helper.h"
#include "daemons/collector/protocol/ccollectorprotocol.h"
#include "ctimer.h"
#include "daemons/collector/node/csensor.h"
#include <list>
#include <string>
#include "mutex-helper.h"

namespace mon
{
namespace daemons
{
namespace collector
{

//! Удаленная нода
class CNode : public mon::lib::network::CSocketClient,
                    public CCollectorProtocol,
                    public mon::lib::base::CTimer
{
  MON_THREADED_FUNCTION_DECLARE(connect)
  MON_READONLY_PROPERTY(std::string, name)
  MON_MUTEX_DECLARE(node_sensors)
public:
  CNode(const std::string &name);
  virtual ~CNode();
private:
  TSensors m_nodeSensors;

  void onTimer() final;

  //! Вызывается при успешном коннекте сокета к ноде, инициализирует обмен данными по протоколу
  void connected(const std::string &to_addr, const unsigned short &to_port) final;
  //! Заглушка из за архитектурного недостатка
  void incommingMessage(const std::string &message) final;

  //! Вызывается при ответе на запрос подключения
  void incomingAnswerOnConnect(lib::protocol::CNetworkMessage *msg) final;
  //! Вызывается при ответе на запрос списка сенсоров
  void incomingAnswerOnRequestSensorList(lib::protocol::CNetworkMessage *msg) final;
  //! Вызывается при ответе на запрос описания сенсора
  void incomingAnswerOnRequestSensorDefinition(mon::lib::protocol::CNetworkMessage *msg) final;
  //! Вызывается при ответе на запрос статистики фрейма сенсора
  void incomingAnswerOnRequestSensorFrameStatistic(lib::protocol::CNetworkMessage *msg) final;
};

typedef std::list<CNode *> TNodes;

}
}
}

#endif // CREMOTEMONNODE_H
