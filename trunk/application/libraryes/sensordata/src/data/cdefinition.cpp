/* %Id% */
#include "cdefinition.h"
#include "st.h"
#include "signals-helper.h"

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
  MON_LOG_ERR("Requested sensor ("<< name <<") not exists");
  MON_ABORT;
  return nullptr;
}

TFramesNames &CDefinition::frames()
{
  return m_names;
}

}
}
}
