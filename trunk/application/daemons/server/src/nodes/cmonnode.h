#ifndef CMONNODE_H
#define CMONNODE_H
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

class CMonNode
{
  MON_THREADED_FUNCTION_DECLARE(connect)
public:
  CMonNode(const std::string &confLeaf, const TMonNodeID &nodeID);
  virtual ~CMonNode();
  const TMonNodeID &id() const;
private:
  TMonNodeID m_id;
  std::string m_configLeaf;
  mon::lib::network::CSocketClient *m_socket;
};

typedef std::map<TMonNodeID, CMonNode *> TMonNodes;

}
}
}

#endif // CMONNODE_H
