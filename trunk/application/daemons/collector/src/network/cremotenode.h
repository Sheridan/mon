/* %Id% */
#ifndef CREMOTEMONNODE_H
#define CREMOTEMONNODE_H
#include "cclientsocket.h"
#include "threads-helper.h"
#include "class-helper.h"
#include "ccollectorprotocol.h"
#include "cfolder.h"
#include "cremotenodesensor.h"
#include <list>
#include <string>

namespace mon
{
namespace daemons
{
namespace collector
{

class CRemoteNode : public mon::lib::network::CSocketClient, public CCollectorProtocol
{
  MON_THREADED_FUNCTION_DECLARE(connect)
public:
  CRemoteNode(const std::string &confLeaf);
  virtual ~CRemoteNode();
private:
  mon::lib::config::CFolder *m_selfConfig;

  TRemoteNodeSensors m_nodeSensors;

  void incommingMessage(const std::string &message);
  void connected(const std::string &to_addr, const unsigned short &to_port);
};

typedef std::list<CRemoteNode *> TRemoteNodes;

}
}
}

#endif // CREMOTEMONNODE_H
