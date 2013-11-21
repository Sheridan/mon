#ifndef ClibNODE_H
#define ClibNODE_H
#include <list>
#include <string>
#include "defines/class-helper.h"
#include "defines/mutex-helper.h"
#include "libraryes/node/csensor.h"

namespace mon
{
namespace lib
{
namespace node
{

class CNode
{
    MON_READONLY_PROPERTY(std::string, name)
    MON_MUTEX_DECLARE(sensors)
  public:
    CNode();
    virtual ~CNode();
    CSensor *sensor(const std::string &name);

  protected:
    void addSensor(const std::string &name, const std::string &definition);

  private:
    TSensors m_sensors;
};

typedef std::list<CNode *> TNodes;

}
}
}
#endif // ClibNODE_H
