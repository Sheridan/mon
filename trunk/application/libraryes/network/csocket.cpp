/* %Id% */
#include <stdlib.h>
#include "defines/infinity-cycle-helper.h"
#include "libraryes/network/csocket.h"
#include "defines/st.h"

namespace mon
{
namespace lib
{
namespace network
{

CSocket::CSocket()
{
  m_isListen      = false;
  m_isConnected = false;
  m_portLocal   = 0;
  m_portRemote  = 0;
  m_socketDescriptor = 0;
  m_timeout    = MON_DEFAULT_CONNECT_TIMEOUT;
  m_addrLocal  = "";
  m_addrRemote = "";
  MON_MUTEX_INITIALIZE(write)
  MON_THREADED_FUNCTION_INIT(waitRecv);
}

CSocket::~CSocket()
{
  close();
  MON_MUTEX_DESTROY(write)
}

MON_THREADED_FUNCTION_IMPLEMENT(CSocket, waitRecv)
{
  std::string t_message = "";
  char t_current_char = '\0';
  MON_INFINITY_LOOP_BEGIN(read_or_wait)
    MON_THREADED_ABORT_IF_NEED(waitRecv);
    if(m_isConnected || m_isListen)
    {

      int  t_recv_bytes = 0;
      MON_INFINITY_LOOP_BEGIN(read_all)
        MON_THREADED_ABORT_IF_NEED(waitRecv);
        t_recv_bytes = ::recv(m_socketDescriptor, &t_current_char, sizeof(char), 0);
        if (t_recv_bytes > 0)
        {
          switch(t_current_char)
          {
            case '\n':
            {
              MON_LOG_DBG("Incoming message (endl): '" << t_message << "'");
              incommingMessage(t_message);
              t_message = "";
              break;
            }
            default: t_message += t_current_char;
          }
          MON_INFINITY_LOOP_RESTART(read_all)
        }
        if (t_recv_bytes == 0)
        {
          if(!t_message.empty())
          {
            MON_LOG_DBG("Incoming message (eof): '" << t_message << "'");
            incommingMessage(t_message);
            t_message = "";
          }
          MON_INFINITY_LOOP_RESTART(read_all)
        }
        if (t_recv_bytes < 0)
        {
          MON_PRINT_ERRNO("Socket recieve error")
          MON_INFINITY_LOOP_BREAK(read_all)
        }
      MON_INFINITY_LOOP_END(read_all)

    }
    else
    {
      sleep(1);
    }
  MON_INFINITY_LOOP_END(read_or_wait)
}

void CSocket::write(const std::string &data)
{
  if(m_isConnected || m_isListen)
  {
    MON_LOG_DBG("Message to send: '" << data.substr(0, data.length()-1) << "'");

    int t_msg_length = data.length();
    int t_sent_bytes = 0;
    int t_total_sent_bytes = 0;

    MON_MUTEX_LOCK(write)
    while(t_total_sent_bytes < t_msg_length)
    {
       t_sent_bytes = ::send(m_socketDescriptor, data.c_str()+t_total_sent_bytes, t_msg_length-t_total_sent_bytes, 0);
       if (t_sent_bytes == -1) { MON_PRINT_ERRNO("Error writing to socket"); break; }
       t_total_sent_bytes += t_sent_bytes;
    }
    MON_MUTEX_UNLOCK(write)

    //MON_LOG_DBG("Socket bytes send: " << t_total_sent_bytes);
  }
  else { MON_LOG_ERR("Write on offline socket") }
}

void CSocket::close()
{
  if(m_isListen || m_isConnected)
  {
    MON_MUTEX_LOCK(write)
    if(::shutdown(m_socketDescriptor, SHUT_RDWR) == -1)
    {
      MON_PRINT_ERRNO("Socket shutdown error")
    }
    if(::close(m_socketDescriptor) == -1)
    {
      MON_PRINT_ERRNO("Socket close error")
    }
    MON_MUTEX_UNLOCK(write)
    m_isListen    = false;
    m_isConnected = false;
  }
  MON_THREADED_FUNCTION_ABORT(waitRecv);
}

#define MON_SOCKET_OPTION_SET(_to,_from) \
    if(!(m_isListen || m_isConnected)) { _to = _from; } \
    else { MON_LOG_WRN("Set option (" #_to ") on online socket (from `" << _to << "` to `" << _from <<"`)") }

void                   CSocket::setPortLocal  (const unsigned short &port) { MON_SOCKET_OPTION_SET(m_portLocal,  port); }
void                   CSocket::setPortRemote (const unsigned short &port) { MON_SOCKET_OPTION_SET(m_portRemote, port); }
void                   CSocket::setAddrLocal  (const std::string    &addr) { MON_SOCKET_OPTION_SET(m_addrLocal , addr); }
void                   CSocket::setAddrRemote (const std::string    &addr) { MON_SOCKET_OPTION_SET(m_addrRemote, addr); }
void                   CSocket::setTimeout    (const int            &val ) { m_timeout = val ; }
const unsigned short & CSocket::portLocal  () const { return m_portLocal       ; }
const unsigned short & CSocket::portRemote () const { return m_portRemote      ; }
const std::string    & CSocket::addrLocal  () const { return m_addrLocal       ; }
const std::string    & CSocket::addrRemote () const { return m_addrRemote      ; }
const int            & CSocket::descriptor () const { return m_socketDescriptor; }
const int            & CSocket::timeout    () const { return m_timeout         ; }
const bool           & CSocket::isConnected() const { return m_isConnected     ; }
const bool           & CSocket::isListen   () const { return m_isListen        ; }
}
}
}
