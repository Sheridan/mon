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

void CCmdLineParcer::parce ()
{
  for ( int i = 1; i < m_argc; i++ )
  {
    SCmdLineParameter option(findOption(m_argv[i]));
    if(option.isFlag)
    {
      option.value = true;
    }
    else
    {
      i++;
      if(i>=m_argc)
      {
        MON_LOG_ERR( "Missing value for --" << option.longName << " (" << option.description << ")");
        MON_ABORT;
      }
      if(m_argv[i][0] == '-')
      {
        MON_LOG_ERR( "Missing value for --" << option.longName << " (" << option.description << ")");
        MON_ABORT;
      }
      option.value.set(m_argv[i]);
      MON_CMDLINE_LOG_DBG( option.longName << " = " << option.value.toString() << " (" << m_argv[i] << ")");
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
  MON_CMDLINE_LOG_DBG("New cmd parameter -" << shortName << ":--" << longName << ":" << description << ", default: " << defaultValue.toString());
  m_parametres[shortName] = {shortName, longName, description, defaultValue, false};
}

void CCmdLineParcer::addParametr ( const std::string &shortName, const std::string &longName, const std::string &description )
{
  MON_CMDLINE_LOG_DBG("New cmd flag -" << shortName << ":--" << longName << ":" << description << ", default false");
  m_parametres[shortName] = {shortName, longName, description, false, true};
}

SCmdLineParameter CCmdLineParcer::findOption ( const std::string &argvOptionString )
{
  for(auto &p : m_parametres)
  {
    MON_LOG_DBG_CHECKPOINT;
    if(compareOptions(p.second, argvOptionString))
    {
      MON_LOG_DBG_CHECKPOINT;
      MON_CMDLINE_LOG_DBG( "Found parametr '" << argvOptionString << "'. Interpret as [-" << p.second.shortName << "][--" << p.second.longName << "], with default '" << p.second.value.toString() << "'");
      return p.second;
    }
  }
  MON_LOG_ERR( "Unknown command line option: " << argvOptionString );
  MON_ABORT;
}

bool CCmdLineParcer::compareOptions ( const SCmdLineParameter &parametr, const std::string option )
{
  MON_LOG_DBG_CHECKPOINT;
  if(parametr.shortName.compare(option.substr(1, option.length())) == 0) { return true; }
  if(parametr.longName .compare(option.substr(2, option.length())) == 0) { return true; }
  return false;
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
