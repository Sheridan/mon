/* %Id% */
#include "defines/st.h"
#include "defines/signals-helper.h"
#include "libraryes/sensordata/data/cdefinition.h"

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
//  MON_LOG_DBG("Frame ("<< name <<") added");
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
