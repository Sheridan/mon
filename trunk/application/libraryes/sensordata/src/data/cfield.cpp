#include "cfield.h"
namespace mon
{
namespace lib
{
namespace sensordata
{

CField::CField()
{
  m_name = "";
  m_label = "";
  m_description = "";
  m_type = dtInteger;
}

CField::CField(const std::string &name, const std::string &label, const EFieldDataType &type, const std::string &description)
  :m_name(name), m_label(label), m_type(type), m_description(description)
{}


CField::~CField()
{

}


}
}
}
