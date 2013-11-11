/* %Id% */
#include "cprotocol.h"
#include "cvariant.h"
#include "st.h"


namespace mon
{
namespace lib
{
namespace protocol
{

CProtocol::CProtocol(mon::lib::network::CSocket *socket) : m_socket(socket)
{
  m_currentID = 1;
}

CProtocol::~CProtocol()
{
  m_replyCallbackMap.clear();
  m_interceptCallbackMap.clear();
}

void CProtocol::incommingMessage(const std::string &i_incoming)
{
  CNetworkMessage *msg = new CNetworkMessage(i_incoming);
  if(msg->type() == mtAnswer)
  {
    if(m_replyCallbackMap.find(msg->id()) == m_replyCallbackMap.end())
    {
      MON_LOG_ERR("Reply on non-exists message id " << msg->id() << " (" << msg->string() << ")");
    }
    else
    {
      (*this.*m_replyCallbackMap[msg->id()])(msg);
      m_replyCallbackMap.erase(msg->id());
    }
  }
  else
  {
    if(m_interceptCallbackMap.find(msg->type()) == m_interceptCallbackMap.end())
    {
      MON_LOG_ERR("Unintercepted message type " << msg->type() << " (" << msg->string() << ")");
    }
    else
    {
      (*this.*m_interceptCallbackMap[msg->type()])(msg);
    }
  }
  delete msg;
}

void CProtocol::sendMessage(CNetworkMessage *msg)
{
  m_socket->write(msg->preparedText());
  delete msg;
}

void CProtocol::sendMessage(TMessageCallback callback, const EProtocolMessageType &i_type, const std::string &i_text)
{
  sendMessage(newMessage(callback, i_type, i_text));
}

void CProtocol::sendMessage(TMessageCallback callback, const EProtocolMessageType &i_type)
{
  sendMessage(newMessage(callback, i_type));
}

void CProtocol::sendReply(CNetworkMessage *requestMessage, const std::string &i_text)
{
  CNetworkMessage *msg = new CNetworkMessage(requestMessage->id(), mtAnswer, i_text);
  sendMessage(msg);
}

TProtocolMessageID CProtocol::getID()
{
  if(m_currentID == ULLONG_MAX) { m_currentID = 1; }
  return m_currentID++;
}

CNetworkMessage *CProtocol::newMessage(TMessageCallback callback, const EProtocolMessageType &i_type)
{
  CNetworkMessage *msg = new CNetworkMessage(getID(), i_type);
  m_replyCallbackMap[msg->id()] = callback;
  return msg;
}

CNetworkMessage *CProtocol::newMessage(TMessageCallback callback, const EProtocolMessageType &i_type, const std::string &i_text)
{
  CNetworkMessage *msg = new CNetworkMessage(getID(), i_type, i_text);
  m_replyCallbackMap[msg->id()] = callback;
  return msg;
}

void CProtocol::registerIntercept(const EProtocolMessageType &type, TMessageCallback callback)
{
  if(m_interceptCallbackMap.find(type) == m_interceptCallbackMap.end())
  {
    m_interceptCallbackMap[type] = callback;
  }
  else
  {
    MON_LOG_ERR("Intercept of network message type " << type << " currently exists");
    MON_ABORT;
  }
}


}
}
}
