/* %Id% */
#include "cdefinition.h"
namespace mon
{
namespace lib
{
namespace sensor
{

CDefinition::CDefinition()
{
}

CDefinition::~CDefinition()
{
}


void CDefinition::addFlag(const EFlags &flag)
{
  m_flags.insert(flag);
}

bool CDefinition::hasFlag(const EFlags &flag)
{
  return m_flags.count(flag) > 0;
}

void CDefinition::addTag (const std::string &tag)
{
  m_tags.insert(tag);
}

bool CDefinition::hasTag (const std::string &tag)
{
  return m_tags.count(tag) > 0;
}

void CDefinition::addInformationField(const std::string &name, const std::string &label, const EDataType &type, const std::string &description)
{
  m_informationFields.push_front(SField(name, label, type, description));
}

void CDefinition::addStatisticalField(const std::string &name, const std::string &label, const EDataType &type, const std::string &description)
{
  m_statisticalFields.push_front(SField(name, label, type, description));
}

std::string CDefinition::generateText()
{
  return "";
}

}
}
}
