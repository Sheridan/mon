/* %Id% */
#ifndef CDEFINITION_H
#define CDEFINITION_H
#include "cobject.h"
namespace mon
{
namespace lib
{
namespace sensor
{

class CDefinition
{
  public:
    CDefinition();
    virtual ~CDefinition();
    void addObject(const std::string &name, CObject *obj);
    CObject * object(const std::string &name);
  private:
    TObjects m_objects;
};

}
}
}
#endif // CDEFINITION_H
