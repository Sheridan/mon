/* %Id% */
#ifndef CSENSOR_H
#define CSENSOR_H
#include <string>
#include "class-helper.h"
#include <list>
namespace mon
{
namespace daemons
{
namespace node
{

class CSensor
{
    MON_READONLY_PROPERTY(std::string, name)
  public:
    CSensor(const std::string &i_name);
    ~CSensor();
    void load();

  private:
    void * m_handle;
};

typedef std::list<CSensor *> TSensors;

}
}
}
#endif // CSENSOR_H
