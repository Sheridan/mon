#ifndef CVALUE_H
#define CVALUE_H
#include <map>
#include <list>
#include <string>
#include "cnode.h"
#include "cvariant.h"

namespace mon
{
namespace lib
{
namespace config
{

typedef std::list<std::string> TStringList;

class CFile;
typedef std::pair<std::string, CFile   *> TFile;
typedef std::map <std::string, CFile   *> TFiles;

class CFile : public CNode, public CVariant
{
public:
  CFile(const std::string &nodeName, CNode *parentNode);
  ~CFile();
};

}
}
}
#endif // CVALUE_H
