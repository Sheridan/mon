#ifndef CCMDLINEPARCER_H
#define CCMDLINEPARCER_H

#include "libraryes/config/model/cfolder.h"
#include "libraryes/base/string/cvariant.h"

namespace mon
{
namespace lib
{
namespace config
{

struct SCmdLineParameter
{
    char shortName;
    std::string longName;
    std::string description;
    mon::lib::base::CVariant defaultValue;
};

typedef std::map<char, SCmdLineParameter> TParametresMap;

class CCmdLineParcer
{
  public:
    CCmdLineParcer(CFolder *root, int argc, char *argv[]);
    virtual ~CCmdLineParcer();

    void addAvialableParameter();
    void parce();

  private:
    CFolder *m_root;
    TParametresMap m_avialableParametres;
    int m_argc;
    char** m_argv;
};

}
}
}
#endif // CCMDLINEPARCER_H
