#ifndef CNODES_H_LIB
#define CNODES_H_LIB
#include <string>
#include "libraryes/model/cnode.h"
#include "libraryes/model/citems.h"

namespace mon
{
namespace lib
{
namespace model
{

//! Модель нод
class CNodes : public CItems<CNode>
{
  public:
    CNodes();
    virtual ~CNodes();
    CNode *node(const std::string &name);

  private:
    TNodes m_nodes;
};

}
}
}
#endif // CNODES_H_LIB
