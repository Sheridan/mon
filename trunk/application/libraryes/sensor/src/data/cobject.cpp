/* %Id% */
#include "cobject.h"
namespace mon
{
namespace lib
{
namespace sensor
{


CObject::CObject()
{
  m_frequences = NULL;
}

CObject::~CObject()
{
  delete m_frequences;
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

void CObject::setFrequences(const EFrequenceType &typeMax, const float &frequencyMax, const EFrequenceType &typeDefault, const float &frequencyDefault)
{
  delete m_frequences;
  m_frequences = new CFrequences(typeMax, frequencyMax, typeDefault, frequencyDefault);
}

std::string CObject::generateText()
{
  return "";
}

}
}
}
