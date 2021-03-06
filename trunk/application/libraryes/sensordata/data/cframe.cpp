/* %Id% */
#include "libraryes/sensordata/data/cframe.h"

namespace mon
{
namespace lib
{
namespace sensordata
{


CFrame::CFrame()
{
  m_frequences[fpMax]     = nullptr;
  m_frequences[fpDefault] = nullptr;
}

CFrame::~CFrame()
{
  delete m_frequences[fpMax]    ;
  delete m_frequences[fpDefault];
  for(auto &field : m_fields)
  {
    delete field;
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
  m_fields.push_back(new CField(name, label, type, description));
}

void CFrame::setFrequency(const EFrequencyPurpose &purpose, const EFrequencyMeasurment &measurment, const float &value)
{
  delete m_frequences[purpose];
  m_frequences[purpose] = new CFrequency(measurment, value);
}

CFrequency *CFrame::frequency(const EFrequencyPurpose &purpose)
{
  return m_frequences[purpose];
}


}
}
}
