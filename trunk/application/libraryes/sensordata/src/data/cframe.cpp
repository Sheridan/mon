/* %Id% */
#include "cframe.h"
#include "stl-helper.h"
namespace mon
{
namespace lib
{
namespace sensordata
{


CFrame::CFrame()
{
  m_frequences[fpMax]     = NULL;
  m_frequences[fpDefault] = NULL;
  m_frequences[fpCurrent] = NULL;
}

CFrame::~CFrame()
{
  delete m_frequences[fpMax]    ;
  delete m_frequences[fpDefault];
  delete m_frequences[fpCurrent];
  MON_STL_LIST_FOREACH(field, TFields, m_fields)
  {
    delete MON_STL_LIST_VALUE(field);
  }
}

void CFrame::addFlag(const EFrameFlags &flag)
{
  m_flags.insert(flag);
}

bool CFrame::hasFlag(const EFrameFlags &flag)
{
  return m_flags.count(flag) > 0;
}

void CFrame::addTag (const std::string &tag)
{
  m_tags.insert(tag);
}

bool CFrame::hasTag (const std::string &tag)
{
  return m_tags.count(tag) > 0;
}

void CFrame::addField(const std::string &name, const std::string &label, const EFieldDataType &type, const std::string &description)
{
  m_fields.push_front(new CField(name, label, type, description));
}

void CFrame::setFrequency(const EFrequencyPurpose &purpose, const EFrequencyMeasurment &measurment, const float &value)
{
  delete m_frequences[purpose];
  m_frequences[purpose] = new CFrequency(measurment, value);
}

std::string CFrame::generateText()
{
  return "";
}

}
}
}
