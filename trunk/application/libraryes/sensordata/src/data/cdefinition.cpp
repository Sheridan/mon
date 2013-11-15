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
  frame->setname(name);
  m_frames[name] = frame;
  m_names.push_back(name);
}

CFrame *CDefinition::frame(const std::string &name)
{
  if (m_frames.count(name) > 0)
  {
    return m_frames[name];
  }
  return nullptr;
}

TFramesNames &CDefinition::frames()
{
  return m_names;
}

}
}
}
