#include <iostream>
#include "defines/signals-helper.h"
#include "ccmdlineparcer.h"
#include "defines/st.h"

namespace mon
{
namespace lib
{
namespace config
{

CCmdLineParcer::CCmdLineParcer ( int argc, char **argv )
  : m_argc(argc), m_argv(argv)
{
  addParametr("h", "help", "This help");
}

CCmdLineParcer::~CCmdLineParcer ()
{ }

void CCmdLineParcer::parce ( )
{
  for ( int i = 1; i < m_argc; i++ )
  {
//    MON_LOG_NFO(i << " -> " << m_argv[i]);
    SCmdLineParameter *opt = findOption(m_argv[i]);
    if(opt->isFlag)
    {
      opt->value = true;
    }
    else
    {
      i++;
      if(i>=m_argc)
      {
        MON_LOG_ERR("Missing value for --" << opt->longName << " (" << opt->description << ")");
        MON_ABORT;
      }
      std::string value = m_argv[i];
      if(value[0] == '-')
      {
        MON_LOG_ERR("Missing value for --" << opt->longName << " (" << opt->description << ")");
        MON_ABORT;
      }
      opt->value.set(value);
      MON_CMDLINE_LOG_DBG( opt->longName << " = " << opt->value.toString());
    }
  }
  if(getOption("h").toBool())
  {
    showHelp();
    MON_ABORT;
  }
}

void CCmdLineParcer::addParametr ( const std::string &shortName, const std::string &longName, const std::string &description,
                                   const mon::lib::base::CVariant &defaultValue )
{
  MON_CMDLINE_LOG_DBG("New cmd parameter -" << shortName << ":--" << longName << ":" << description);
  m_parametres[shortName] = {shortName, longName, description, defaultValue, false};
}

void CCmdLineParcer::addParametr ( const std::string &shortName, const std::string &longName, const std::string &description )
{
  MON_CMDLINE_LOG_DBG("New cmd flag -" << shortName << ":--" << longName << ":" << description);
  m_parametres[shortName] = {shortName, longName, description, false, true};
}

SCmdLineParameter *CCmdLineParcer::findOption ( const std::string &opt )
{
  for(auto &p : m_parametres)
  {
    MON_CMDLINE_LOG_DBG( std::string( "-" + p.second.longName));
    if( std::string("-" + p.second.shortName).compare(opt) == 0 ||
        std::string("--" + p.second.longName).compare(opt) == 0 )
    {
      MON_CMDLINE_LOG_DBG( "Found parametr " << opt << ": -" << p.second.shortName << " | --" << p.second.longName );
      return &(p.second);
    }
  }
  MON_LOG_ERR("Unknown command line option: " << opt);
  MON_ABORT;
  return nullptr;
}

mon::lib::base::CVariant CCmdLineParcer::getOption ( const std::string &shortName )
{
  return m_parametres[shortName].value;
}

void CCmdLineParcer::showHelp ()
{
  SCmdLineParameter opt;
  for(auto &p : m_parametres)
  {
    opt = p.second;
    std::cout << "\t-" << opt.shortName << ", "
              << "--" << opt.longName << " "
              << (opt.isFlag ? ": " :  "<value>: ")
              << opt.description << (opt.isFlag ? "" : " (current value: " + opt.value.toString() + ")")
              << std::endl;
  }
}
}
}
}
