/* %Id% */
#include "cobject.h"
namespace mon
{
namespace lib
{
namespace sensor
{

#define MON_FOREACH_FREQUENCES(_name) \
   for(TFrequences::iterator _name = m_frequences.begin(); \
    _name != m_frequences.end(); \
    ++_name)

CObject::CObject()
{}

CObject::~CObject()
{
  MON_FOREACH_FREQUENCES(freq)
  {
    delete freq->second;
  }
  m_frequences.clear();
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

void CObject::addInformationField(const std::string &name, const std::string &label, const EDataType &type, const std::string &description)
{
  m_informationFields.push_front(SField(name, label, type, description));
}

void CObject::addStatisticalField(const std::string &name, const std::string &label, const EDataType &type, const std::string &description)
{
  m_statisticalFields.push_front(SField(name, label, type, description));
}

void CObject::setFrequences(const EFrequencyClasses &ftype, const EFrequenceType &typeMax, const float &frequencyMax, const EFrequenceType &typeDefault, const float &frequencyDefault)
{
  m_frequences[ftype] = new CFrequences(typeMax, frequencyMax, typeDefault, frequencyDefault);
}

std::string CObject::generateText()
{
  return "";
}

}
}
}
