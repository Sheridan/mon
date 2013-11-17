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

bool               CFile::get(const bool               &def) { if(m_contentType != mon::lib::base::EContentType::Bool)   { set(def); } return m_value.m_bool  ; }
int                CFile::get(const int                &def) { if(m_contentType != mon::lib::base::EContentType::Int)    { set(def); } return m_value.m_int   ; }
unsigned int       CFile::get(const unsigned int       &def) { if(m_contentType != mon::lib::base::EContentType::UInt)   { set(def); } return m_value.m_uint  ; }
short              CFile::get(const short              &def) { if(m_contentType != mon::lib::base::EContentType::Short)  { set(def); } return m_value.m_short ; }
unsigned short     CFile::get(const unsigned short     &def) { if(m_contentType != mon::lib::base::EContentType::UShort) { set(def); } return m_value.m_ushort; }
long               CFile::get(const long               &def) { if(m_contentType != mon::lib::base::EContentType::Long)   { set(def); } return m_value.m_long  ; }
unsigned long      CFile::get(const unsigned long      &def) { if(m_contentType != mon::lib::base::EContentType::ULong)  { set(def); } return m_value.m_ulong ; }
long long          CFile::get(const long long          &def) { if(m_contentType != mon::lib::base::EContentType::LLong)  { set(def); } return m_value.m_llong ; }
unsigned long long CFile::get(const unsigned long long &def) { if(m_contentType != mon::lib::base::EContentType::ULLong) { set(def); } return m_value.m_ullong; }
float              CFile::get(const float              &def) { if(m_contentType != mon::lib::base::EContentType::Float)  { set(def); } return m_value.m_float ; }
double             CFile::get(const double             &def) { if(m_contentType != mon::lib::base::EContentType::Double) { set(def); } return m_value.m_double; }
std::string        CFile::get(const std::string        &def) { if(m_contentType != mon::lib::base::EContentType::String) { set(def); } return m_value.m_string; }

}
}
}

