/* %Id% */
#ifndef CREMOTEMONNODE_H
#define CREMOTEMONNODE_H
#include <list>
#include <string>
#include "defines/threads-helper.h"
#include "defines/class-helper.h"
#include "defines/mutex-helper.h"
#include "daemons/collector/protocol/cprotocol.h"
#include "daemons/collector/node/csensor.h"
#include "libraryes/base/timer/ctimer.h"
#include "libraryes/network/cclientsocket.h"
#include "libraryes/model/cnode.h"

namespace mon
{
namespace daemons
{
namespace collector
{

//! Удаленная нода
class CNode : public lib::model::CNode,
              public mon::lib::network::CSocketClient,
              public CProtocol,
              public mon::lib::base::CTimer
{
  MON_THREADED_FUNCTION_DECLARE(connect)
public:
  CNode(const std::string &nodeName);
  virtual ~CNode();
private:

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

}
}
}

#endif // CREMOTEMONNODE_H
