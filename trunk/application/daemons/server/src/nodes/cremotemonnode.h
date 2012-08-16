/* %Id% */
#ifndef CREMOTEMONNODE_H
#define CREMOTEMONNODE_H
#include "cclientsocket.h"
#include "threads-helper.h"
#include <map>
#include <string>

namespace mon
{
namespace daemons
{
namespace server
{

typedef unsigned int TMonNodeID;

class CRemoteMonNode
{
  MON_THREADED_FUNCTION_DECLARE(connect)
public:
  CRemoteMonNode(const std::string &confLeaf, const TMonNodeID &nodeID);
  virtual ~CRemoteMonNode();
  const TMonNodeID &id() const;
private:
  TMonNodeID m_id;
  std::string m_configLeaf;
  mon::lib::network::CSocketClient *m_socket;
};

typedef std::map<TMonNodeID, CRemoteMonNode *> TRemoteMonNodes;

}
}
}

#endif // CREMOTEMONNODE_H
