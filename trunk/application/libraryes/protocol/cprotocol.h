/* %Id% */
#ifndef CPROTOCOL_H
#define CPROTOCOL_H
#include "libraryes/network/csocket.h"
#include "libraryes/protocol/cnetworkmessage.h"
#include "defines/protocol-control.h"
#include <map>

namespace mon
{
namespace lib
{
namespace protocol
{
class CProtocol;
typedef void (CProtocol::*TMessageCallback) (mon::lib::protocol::CNetworkMessage *);
typedef std::map<MON_PROTOCOL_MESSAGE_ID_TYPE,TMessageCallback> TReplyMap;
typedef std::map<EProtocolMessageType,TMessageCallback> TInterceptMap;

//! Базовый класс описания сетевого протокола
class CProtocol
{
  friend class CNetworkMessage;
public:
  CProtocol(mon::lib::network::CSocket *socket);
  virtual ~CProtocol();
  CNetworkMessage * newMessage(TMessageCallback callback, const EProtocolMessageType &i_type);
  CNetworkMessage * newMessage(TMessageCallback callback, const EProtocolMessageType &i_type, const std::string  &i_text);
  void sendMessage(TMessageCallback callback, const EProtocolMessageType &i_type, const std::string  &i_text);
  void sendMessage(TMessageCallback callback, const EProtocolMessageType &i_type);
  void sendReply(CNetworkMessage *requestMessage, const std::string  &i_text);

protected:
  void incommingMessage(const std::string &i_incoming);
  void registerIntercept(const EProtocolMessageType &type, TMessageCallback callback);
  void sendMessage(CNetworkMessage *msg);

private:
  mon::lib::network::CSocket *m_socket;
  MON_PROTOCOL_MESSAGE_ID_TYPE m_currentID;      //!< Текущий идентификатор сообщения. При достижении максимума - сбрасывается в ноль
  TReplyMap m_replyCallbackMap;        //!< Карта вызовов при ответе на сообщение
  TInterceptMap m_interceptCallbackMap;//!< Карта вызовов при входящих сообщениях

  MON_PROTOCOL_MESSAGE_ID_TYPE getID();          //!< Генерирование нового идентификатора сообщения
};

}
}
}
#endif // CPROTOCOL_H
