/* %Id% */
#include "cdefinition.h"
namespace mon
{
namespace lib
{
namespace sensor
{

CDefinition::CDefinition()
{
}

CDefinition::~CDefinition()
{
}

void CDefinition::addObject(const std::string &name, CObject *obj)
{
  m_objects[name] = obj;
}

CObject *CDefinition::object(const std::string &name)
{
  if (m_objects.count(name) > 0)
  {
    return m_objects[name];
  }
  return NULL;
}

}
}
}
