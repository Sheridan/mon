/* %Id% */
#include "cdefinition.h"
#include "stl-helper.h"
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
}

CFrame *CDefinition::frame(const std::string &name)
{
  if (m_frames.count(name) > 0)
  {
    return m_frames[name];
  }
  return NULL;
}

TFramesNames CDefinition::frames()
{
  TFramesNames result;
  MON_STL_MAP_FOREACH(frames, TFramesMap, m_frames)
  {
    result.push_back(MON_STL_MAP_KEY(frames));
  }
  return result;}

}
}
}
