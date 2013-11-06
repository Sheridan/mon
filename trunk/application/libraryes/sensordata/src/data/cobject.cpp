/* %Id% */
#include "cobject.h"
namespace mon
{
namespace lib
{
namespace sensordata
{


CObject::CObject()
{
  m_frequences[fpMax]     = NULL;
  m_frequences[fpDefault] = NULL;
  m_frequences[fpCurrent] = NULL;
}

CObject::~CObject()
{
  delete m_frequences[fpMax]    ;
  delete m_frequences[fpDefault];
  delete m_frequences[fpCurrent];
}

void CObject::addFlag(const EFlags &flag)
{
  m_flags.insert(flag);
}

bool CObject::hasFlag(const EFlags &flag)
{
  return m_flags.count(flag) > 0;
}

void CObject::addTag (const std::string &tag)
{
  m_tags.insert(tag);
}

bool CObject::hasTag (const std::string &tag)
{
  return m_tags.count(tag) > 0;
}

void CObject::addField(const std::string &name, const std::string &label, const EDataType &type, const std::string &description)
{
  m_fields.push_front(SField(name, label, type, description));
}

void CObject::setFrequency(const EFrequencyPurpose &purpose, const EFrequencyMeasurment &measurment, const float &value)
{
  delete m_frequences[purpose];
  m_frequences[purpose] = new CFrequency(measurment, value);
}

std::string CObject::generateText()
{
  return "";
}

}
}
}
