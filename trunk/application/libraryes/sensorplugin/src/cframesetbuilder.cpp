#include "cframesetbuilder.h"
#include "protocol-control.h"

namespace mon
{
namespace lib
{
namespace sensorplugin
{

CFramesetBuilder::CFramesetBuilder(const std::string &sensor, const std::string &frame, const int &totalFrames)
  :mon::lib::base::CStringBuilder(), m_totalFrames(totalFrames)
{
  mon::lib::base::CStringBuilder::append(sensor);
  mon::lib::base::CStringBuilder::append(MON_DATA_SENSORNAME_I_FRAMENAME_DELIMITER);
  mon::lib::base::CStringBuilder::append(frame);
  mon::lib::base::CStringBuilder::append(MON_DATA_SENSOR_HEADER_I_FRAMESETS_DELIMITER);
  m_framesCount = 0;
}

CFramesetBuilder::~CFramesetBuilder()
{}

const std::string &CFramesetBuilder::msg()
{
  removeLast();
  return mon::lib::base::CStringBuilder::msg();
}

CFramesetBuilder &CFramesetBuilder::newFrame(const int &number)
{
  if(m_framesCount)
  {
    removeLast();
    if(m_framesCount < m_totalFrames-1)
    {
      mon::lib::base::CStringBuilder::append(MON_DATA_SENSOR_FRAME_I_FRAME_DELIMITER);
    }
  }
  mon::lib::base::CStringBuilder::append(number);
  mon::lib::base::CStringBuilder::append(MON_DATA_SENSOR_FRAMENUMBER_I_FIELDS_DELIMITER);
  m_framesCount++;
  return *this;
}

#define MON_APPEND_DATA_FIELD mon::lib::base::CStringBuilder::append(val); mon::lib::base::CStringBuilder::append(MON_DATA_SENSOR_FIELD_I_FIELD_DELIMITER);

void CFramesetBuilder::append(const int           &val) { MON_APPEND_DATA_FIELD }
void CFramesetBuilder::append(const unsigned int  &val) { MON_APPEND_DATA_FIELD }
void CFramesetBuilder::append(const double        &val) { MON_APPEND_DATA_FIELD }
void CFramesetBuilder::append(const float         &val) { MON_APPEND_DATA_FIELD }
void CFramesetBuilder::append(const bool          &val) { MON_APPEND_DATA_FIELD }
void CFramesetBuilder::append(const std::string   &val) { MON_APPEND_DATA_FIELD }
void CFramesetBuilder::append(const char          *val) { MON_APPEND_DATA_FIELD }
void CFramesetBuilder::append(const char          &val) { MON_APPEND_DATA_FIELD }
void CFramesetBuilder::append(const unsigned char &val) { MON_APPEND_DATA_FIELD }

}
}
}
