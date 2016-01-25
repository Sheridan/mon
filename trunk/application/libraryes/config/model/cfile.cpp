/* %Id% */
#include "libraryes/config/model/cfile.h"
#include "libraryes/config/model/cfolder.h"

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

bool               CFile::get(const bool               &def) { if(!tryConvert(def)) { set(def); } return toBool  (); }
char               CFile::get(const char               &def) { if(!tryConvert(def)) { set(def); } return toChar  (); }
int                CFile::get(const int                &def) { if(!tryConvert(def)) { set(def); } return toInt   (); }
unsigned int       CFile::get(const unsigned int       &def) { if(!tryConvert(def)) { set(def); } return toUInt  (); }
short              CFile::get(const short              &def) { if(!tryConvert(def)) { set(def); } return toShort (); }
unsigned short     CFile::get(const unsigned short     &def) { if(!tryConvert(def)) { set(def); } return toUShort(); }
long               CFile::get(const long               &def) { if(!tryConvert(def)) { set(def); } return toLong  (); }
unsigned long      CFile::get(const unsigned long      &def) { if(!tryConvert(def)) { set(def); } return toULong (); }
long long          CFile::get(const long long          &def) { if(!tryConvert(def)) { set(def); } return toLLong (); }
unsigned long long CFile::get(const unsigned long long &def) { if(!tryConvert(def)) { set(def); } return toULLong(); }
float              CFile::get(const float              &def) { if(!tryConvert(def)) { set(def); } return toFloat (); }
double             CFile::get(const double             &def) { if(!tryConvert(def)) { set(def); } return toDouble(); }
std::string        CFile::get(const std::string        &def) { if(!tryConvert(def)) { set(def); } return toString(); }

}
}
}

