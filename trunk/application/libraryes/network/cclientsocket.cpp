/* %Id% */
#include <arpa/inet.h>
#include <netdb.h>
#include "defines/st.h"
#include "defines/signals-helper.h"
#include "libraryes/network/cclientsocket.h"
#include "libraryes/base/string/cvariant.h"

namespace mon
{
namespace lib
{
namespace network
{

CSocketClient::CSocketClient() : CSocket()
{
}

CSocketClient::CSocketClient(const int &descriptor, const std::string &addr_from, const int &port_from) : CSocket()
{
  setAddrRemote(addr_from);
  setPortRemote(port_from);
  m_socketDescriptor = descriptor;
  m_isConnected      = true;
  waitRecv();
}

CSocketClient::~CSocketClient()
{}

void CSocketClient::connect(const std::string &addr, const unsigned short &port)
{
  setPortRemote(port);
  setAddrRemote(addr);
  connect();
}

void CSocketClient::connect()
{
  MON_LOG_NFO("Connecting to " << addrRemote() << ":" << portRemote());
  addrinfo t_connection_info, *t_ip_addresses, *t_ip_address;

  memset(&t_connection_info, 0, sizeof(struct addrinfo));
  t_connection_info.ai_family   = AF_UNSPEC;  /* Allow IPv4 or IPv6 */
  t_connection_info.ai_socktype = SOCK_STREAM; /* Datagram socket */
  t_connection_info.ai_flags    = 0;
  t_connection_info.ai_protocol = 0;          /* Any protocol */

  std::string strPort = mon::lib::base::toString(portRemote());

  int gai_err = getaddrinfo(addrRemote().c_str(), strPort.c_str(), &t_connection_info, &t_ip_addresses);
  if (gai_err != 0)
  {
    MON_LOG_ERR("Error get address info for " << addrRemote() << ":" << portRemote() << " - " << gai_strerror(gai_err));
    MON_ABORT;
  }

  for (t_ip_address = t_ip_addresses; t_ip_address != nullptr; t_ip_address = t_ip_address->ai_next)
  {
    m_socketDescriptor = socket(t_ip_address->ai_family, t_ip_address->ai_socktype, t_ip_address->ai_protocol);
    if (m_socketDescriptor == -1) { continue; }
    if (::connect(m_socketDescriptor, t_ip_address->ai_addr, t_ip_address->ai_addrlen) != -1) { break; } /* Success */
    ::close(m_socketDescriptor);
  }

  if (t_ip_address == nullptr) /* No address succeeded */
  {
    MON_LOG_ERR("Could not connect")
  }
  else
  {
    MON_LOG_NFO("Connected to " << addrRemote() << ":" << portRemote());
    m_isConnected = true;
    connected(addrRemote(), portRemote());
    waitRecv();
  }
  freeaddrinfo(t_ip_addresses);  /* No longer needed */
}

}
}
}
