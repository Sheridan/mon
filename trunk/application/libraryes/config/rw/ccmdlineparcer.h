#ifndef CCMDLINEPARCER_H
#define CCMDLINEPARCER_H

#include <map>
#include "libraryes/base/string/cvariant.h"

#define MON_CMDLINE_DEBUG
#ifdef MON_CMDLINE_DEBUG
  #define MON_CMDLINE_LOG_DBG(_message) MON_LOG_DBG(_message)
#else
  #define MON_CMDLINE_LOG_DBG(_message)
#endif

#define MON_CMD_LINE_VARNAME __cmd__line__parcer__
#define MON_CMD_LINE_INIT mon::lib::config::CCmdLineParcer *MON_CMD_LINE_VARNAME = new mon::lib::config::CCmdLineParcer( argc, argv )
#define MON_CMD_LINE_DESTROY delete MON_CMD_LINE_VARNAME
#define MON_CMD_LINE_ADD_OPTION(_shortName,_longName,_description,_default) \
    MON_CMD_LINE_VARNAME->addParametr(_shortName,_longName,_description,_default)
#define MON_CMD_LINE_ADD_FLAG(_shortName,_longName,_description) \
    MON_CMD_LINE_VARNAME.addParametr(_shortName, _longName, _description)
#define MON_CMD_LINE_PARCE MON_CMD_LINE_VARNAME->parce()
#define MON_CMD_LINE_OPTION_VALUE(_shortName) MON_CMD_LINE_VARNAME->getOption(_shortName)

namespace mon
{
namespace lib
{
namespace config
{

struct SCmdLineParameter
{
    std::string shortName;
    std::string longName;
    std::string description;
    mon::lib::base::CVariant value;
    bool isFlag;
};

typedef std::map<std::string, SCmdLineParameter> TCmdLineParametres;

class CCmdLineParcer
{
  public:
    CCmdLineParcer ( int argc, char **argv );
    virtual ~CCmdLineParcer ();

    void addParametr (const std::string &shortName,
                     const std::string &longName,
                     const std::string &description,
                     const mon::lib::base::CVariant &defaultValue );
    void addParametr(const std::string &shortName,
                     const std::string &longName,
                     const std::string &description);
    void parce ( );
    mon::lib::base::CVariant getOption(const std::string &shortName);

  private:
    SCmdLineParameter findOption (const std::string &argvOptionString );
    void showHelp();
    bool compareOptions(const SCmdLineParameter &parametr, const std::string option);

    TCmdLineParametres    m_parametres;
    int m_argc;
    char **m_argv;
};

}
}
}
#endif // CCMDLINEPARCER_H
