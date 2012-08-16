#include "cdefinition.h"
namespace mon
{
namespace lib
{
namespace protocol
{

CDefinition::CDefinition()
{
}

void CDefinition::addFlag(const EFlags &flag)
{
  m_flags.insert(flag);
}

void CDefinition::addTag (const std::string &tag)
{
  m_tags.insert(tag);
}

void CDefinition::addInformationField(const std::string &name, const std::string &label, const EDataType &type, const std::string &description)
{
  m_informationFields.push_front(SField(name, label, type, description));
}

void CDefinition::addStatisticalField(const std::string &name, const std::string &label, const EDataType &type, const std::string &description)
{
  m_statisticalFields.push_front(SField(name, label, type, description));
}

}
}
}
