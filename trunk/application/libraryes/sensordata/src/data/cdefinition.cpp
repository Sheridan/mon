/* %Id% */
#include "cdefinition.h"
namespace mon
{
namespace lib
{
namespace sensordata
{

CDefinition::CDefinition()
{
}

CDefinition::~CDefinition()
{
}

void CDefinition::addFrame(const std::string &name, CFrame *frame)
{
  m_frames[name] = frame;
}

CFrame *CDefinition::frame(const std::string &name)
{
  if (m_frames.count(name) > 0)
  {
    return m_frames[name];
  }
  return NULL;
}

}
}
}
