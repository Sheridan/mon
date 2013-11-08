/* %Id% */
#ifndef CPROTOCOL_H
#define CPROTOCOL_H
#include "csocket.h"
#include "cnetworkmessage.h"
#include "protocol-control.h"
#include <map>

namespace mon
{
namespace lib
{
namespace protocol
{
class CProtocol;
typedef void (CProtocol::*TMessageCallback) (mon::lib::protocol::CNetworkMessage *);
typedef std::map<TProtocolMessageID,TMessageCallback> TReplyMap;
typedef std::map<EProtocolMessageType,TMessageCallback> TInterceptMap;

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
  TProtocolMessageID m_currentID; //!< Текущий идентификатор сообщения. При достижении максимума - сбрасывается в ноль
  TReplyMap m_replyCallbackMap;
  TInterceptMap m_interceptCallbackMap;

  TProtocolMessageID getID();     //!< Генерирование нового идентификатора сообщения
};

}
}
}
#endif // CPROTOCOL_H
