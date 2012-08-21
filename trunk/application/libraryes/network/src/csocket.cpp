/* %Id% */
#include <stdlib.h>
#include "infinity-cycle-helper.h"
#include "csocket.h"
#include "st.h"

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
  MON_THREADED_FUNCTION_INIT(waitRecv);
}

CSocket::~CSocket()
{
  MON_THREADED_FUNCTION_ABORT(waitRecv);
  close();
}
#define MON_SOCKET_RECV_BUFFER_LENGTH 512
MON_THREADED_FUNCTION_IMPLEMENT(CSocket, waitRecv)
{
  std::string t_message = "";
  INFINITY_CYCLE_BEGIN(read_or_wait)
    if(m_isConnected || m_isListen)
    {
      char t_recv_buffer[MON_SOCKET_RECV_BUFFER_LENGTH]; // = static_cast<char*>(malloc(sizeof(char)*MON_SOCKET_RECV_BUFFER_LENGTH));
      int  t_recv_bytes = 0;
      INFINITY_CYCLE_BEGIN(read_all)
        ::memset(t_recv_buffer, 0, sizeof(t_recv_buffer));
        t_recv_bytes = ::recv(m_socketDescriptor, t_recv_buffer, sizeof(t_recv_buffer), 0);
        if (t_recv_bytes > 0)
        {
          MON_LOG_DBG("Socket bytes received: " << t_recv_bytes)
          t_message += std::string(t_recv_buffer, t_recv_bytes);
          INFINITY_CYCLE_RESTART(read_all)
        }
        if (t_recv_bytes == 0)
        {
          if(!t_message.empty())
          {
            MON_LOG_DBG(t_message)
            incommingMessage(t_message);
          }
          INFINITY_CYCLE_RESTART(read_all)
        }
        if (t_recv_bytes < 0)
        {
          MON_PRINT_ERRNO("Socket recieve error")
          INFINITY_CYCLE_BREAK(read_all)
        }
      INFINITY_CYCLE_END(read_all)
    }
    else
    {
      sleep(1);
    }
  INFINITY_CYCLE_END(read_or_wait)
}

void CSocket::write(const std::string &data)
{
  if(m_isConnected || m_isListen)
  {
    int t_msg_length = data.length();
    int t_sent_bytes = 0;
    int t_total_sent_bytes = 0;

    while(t_total_sent_bytes < t_msg_length)
    {
       t_sent_bytes = ::send(m_socketDescriptor, data.c_str()+t_total_sent_bytes, t_msg_length-t_total_sent_bytes, 0);
       if (t_sent_bytes == -1) { MON_PRINT_ERRNO("Error writing to socket"); break; }
       t_total_sent_bytes += t_sent_bytes;
    }

    MON_LOG_DBG("Socket bytes send: " << t_total_sent_bytes)
  }
  else { MON_LOG_ERR("Write on offline socket") }
}

void CSocket::close()
{
  if(m_isListen || m_isConnected)
  {
    if(::shutdown(m_socketDescriptor, SHUT_RDWR) == -1)
    {
      MON_PRINT_ERRNO("Socket shutdown error")
    }
    if(::close(m_socketDescriptor) == -1)
    {
      MON_PRINT_ERRNO("Socket close error")
    }
    m_isListen    = false;
    m_isConnected = false;
  }
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
