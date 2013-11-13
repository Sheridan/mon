/* %Id% */
#ifndef CREMOTEMONNODE_H
#define CREMOTEMONNODE_H
#include "cclientsocket.h"
#include "threads-helper.h"
#include "class-helper.h"
#include "ccollectorprotocol.h"
#include "cfolder.h"
#include "cremotenodesensor.h"
#include "cdefinition.h"
#include <list>
#include <string>

namespace mon
{
namespace daemons
{
namespace collector
{

//! Удаленная нода
class CRemoteNode : public mon::lib::network::CSocketClient, public CCollectorProtocol
{
  MON_THREADED_FUNCTION_DECLARE(connect)
public:
  CRemoteNode(const std::string &confLeaf);
  virtual ~CRemoteNode();
private:
  mon::lib::config::CFolder *m_selfConfig;
  mon::lib::sensordata::CDefinition *m_definition;

  TRemoteNodeSensors m_nodeSensors;

  //! Вызывается при успешном коннекте сокета к ноде, инициализирует обмен данными по протоколу
  void connected(const std::string &to_addr, const unsigned short &to_port);
  //! Заглушка из за архитектурного недостатка
  void incommingMessage(const std::string &message);

  //! Вызывается при ответе на запрос подключения
  void incomingAnswerOnConnect(lib::protocol::CNetworkMessage *msg);
  //! Вызывается при ответе на запрос списка сенсоров
  void incomingAnswerOnRequestSensorList(lib::protocol::CNetworkMessage *msg);
  //! Вызывается при ответе на запрос описания сенсора
  void incomingAnswerOnrequestSensorDefinition(mon::lib::protocol::CNetworkMessage *msg);
};

typedef std::list<CRemoteNode *> TRemoteNodes;

}
}
}

#endif // CREMOTEMONNODE_H
