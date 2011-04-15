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

std::string CSocket::readAll()
{
  return "";
}

void CSocket::write(const std::string &data)
{
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
    m_isOpen      = false;
  }
}

void                   CSocket::setPortLocal  (const unsigned short &port) { m_portLocal  = port; }
void                   CSocket::setPortRemote (const unsigned short &port) { m_portRemote = port; }
void                   CSocket::setAddrLocal  (const std::string    &addr) { m_addrLocal  = addr; }
void                   CSocket::setAddrRemote (const std::string    &addr) { m_addrRemote = addr; }
void                   CSocket::setTimeout    (const int            &val ) { m_timeout    = val ; }
const unsigned short & CSocket::portLocal  () const { return m_portLocal       ; }
const unsigned short & CSocket::portRemote () const { return m_portRemote      ; }
const std::string    & CSocket::addrLocal  () const { return m_addrLocal       ; }
const std::string    & CSocket::addrRemote () const { return m_addrRemote      ; }
const int            & CSocket::descriptor () const { return m_socketDescriptor; }
const int            & CSocket::timeout    () const { return m_timeout         ; }
const bool           & CSocket::isConnected() const { return m_isConnected     ; }
}
}
}
