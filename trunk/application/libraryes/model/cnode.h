#ifndef CNODE_H_LIB
#define CNODE_H_LIB
#include <list>
#include <string>
#include "defines/class-helper.h"
#include "libraryes/model/csensor.h"
#include "libraryes/model/citems.h"

namespace mon
{
namespace lib
{
namespace model
{

//! Модель ноды
class CNode : public CItems<CSensor>
{
    MON_READONLY_PROPERTY(std::string, name)
  public:
    CNode(const std::string &name);
    virtual ~CNode();
    CSensor *sensor(const std::string &name);
};

}
}
}
#endif // CNODE_H_LIB
