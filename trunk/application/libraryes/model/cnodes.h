#ifndef CNODES_H_LIB
#define CNODES_H_LIB
#include <string>
#include "defines/class-helper.h"
#include "defines/mutex-helper.h"
#include "libraryes/model/cnode.h"

namespace mon
{
namespace lib
{
namespace model
{

class CNodes
{
    MON_MUTEX_DECLARE(nodes)
  public:
    CNodes();
    virtual ~CNodes();
    CNode *node(const std::string &name);

  protected:
    void addNode(CNode *node);

  private:
    TNodes m_nodes;
};

}
}
}
#endif // CNODES_H_LIB
