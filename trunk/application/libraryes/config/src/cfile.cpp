/* %Id% */
#include "cfile.h"
#include "cfolder.h"

namespace mon
{
namespace lib
{
namespace config
{

CFile::CFile(const std::string &nodeName, CNode *parentNode) : CNode(nodeName, parentNode), mon::lib::base::CVariant()
{}

CFile::~CFile()
{}

CFolder * CFile::parent()
{
  return static_cast<CFolder *>(CNode::parent());
}

bool        CFile::get(const bool        &def) { if(m_contentType != mon::lib::base::ctBool)   { set(def); } return m_value.m_bool  ; }
int         CFile::get(const int         &def) { if(m_contentType != mon::lib::base::ctInt)    { set(def); } return m_value.m_int   ; }
double      CFile::get(const double      &def) { if(m_contentType != mon::lib::base::ctFloat)  { set(def); } return m_value.m_float ; }
std::string CFile::get(const std::string &def) { if(m_contentType != mon::lib::base::ctString) { set(def); } return m_value.m_string; }

}
}
}

