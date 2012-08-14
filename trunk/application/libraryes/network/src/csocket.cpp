#include <stdlib.h>

#include "csocket.h"
#include "st.h"
//

//
//#include <arpa/inet.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
namespace mon
{
namespace lib
{
namespace network
{

CSocket::CSocket()
{
  m_isOpen      = false;
  m_isConnected = false;
  m_portLocal   = 0;
  m_portRemote  = 0;
  m_socketDescriptor = 0;
  m_timeout    = 30;
  m_addrLocal  = "";
  m_addrRemote = "";
}

CSocket::~CSocket()
{
  close();
}

#define MON_SOCKET_RECV_BUFFER_LENGTH 512
std::string CSocket::readAll()
{
  std::string data = "";
  char* t_recv_buffer = static_cast<char*>(malloc(sizeof(char)*MON_SOCKET_RECV_BUFFER_LENGTH));
  int t_recv_bytes = 0;
  while(true)
  {
    memset(t_recv_buffer, 0, MON_SOCKET_RECV_BUFFER_LENGTH * sizeof(char));
    t_recv_bytes = recv(m_socketDescriptor, t_recv_buffer, MON_SOCKET_RECV_BUFFER_LENGTH, MSG_WAITALL);

    MON_LOG_DBG("Socket bytes received: " << t_recv_bytes)

    if (t_recv_bytes > 0)
    {
      data += t_recv_buffer;
      continue;
    }
    if (t_recv_bytes == 0)
    {
      break;
    }
    if (t_recv_bytes < 0)
    {
      MON_PRINT_ERRNO("Socket recieve error")
      break;
    }
  }
  free(t_recv_buffer);
  return data;
}

void CSocket::write(const std::string &data)
{
  if(m_isConnected or m_isOpen)
  {
    int t_send_bytes = send(m_socketDescriptor, data.c_str(), data.length(), MSG_CONFIRM);
    MON_LOG_DBG("Socket bytes send: " << t_send_bytes)
    if (t_send_bytes >  0) { return; }
    if (t_send_bytes == 0) { MON_LOG_WRN("Socket sent zero bytes...")   }
    if (t_send_bytes <  0) { MON_PRINT_ERRNO("Error writing to socket") }
  }
  else { MON_LOG_ERR("Write on offline socket") }
}

void CSocket::close()
{
  if(m_isOpen)
  {
    if(m_isConnected)
    {
      if(::shutdown(m_socketDescriptor, SHUT_RDWR) == -1)
      {
        MON_PRINT_ERRNO("Socket shutdown error")
      }
      m_isConnected = false;
    }
    if(::close(m_socketDescriptor) == -1)
    {
      MON_PRINT_ERRNO("Socket close error")
    }
    m_isOpen = false;
  }
}

#define MON_SOCKET_OPTION_SET(_to,_from) \
    if(!m_isOpen) { _to = _from; } \
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
const bool           & CSocket::isOpen     () const { return m_isOpen          ; }
}
}
}
