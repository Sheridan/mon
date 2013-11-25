#ifndef CNODE_H_LIB
#define CNODE_H_LIB
#include <list>
#include <string>
#include "defines/class-helper.h"
#include "defines/mutex-helper.h"
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
    MON_MUTEX_DECLARE(sensors)
  public:
    CNode(const std::string &name);
    virtual ~CNode();
    CSensor *sensor(const std::string &name);

  protected:
    void addSensor(const std::string &name, const std::string &definition);
};

}
}
}
#endif // CNODE_H_LIB
