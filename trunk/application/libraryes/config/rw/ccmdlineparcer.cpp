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
{
  for(auto &p : m_parametres)
  {
    delete p.second;
  }
  m_parametres.clear();
}

void CCmdLineParcer::parce ()
{
  for ( int i = 1; i < m_argc; i++ )
  {
    SCmdLineParameter *option = findOption(std::string(m_argv[i]));
    if(option->isFlag)
    {
      option->value = true;
    }
    else
    {
      i++;
      if(i>=m_argc)
      {
        MON_LOG_ERR( "Missing value for --" << option->longName << " (" << option->description << ")");
        MON_ABORT;
      }
      if(m_argv[i][0] == '-')
      {
        MON_LOG_ERR( "Missing value for --" << option->longName << " (" << option->description << ")");
        MON_ABORT;
      }
      option->value.set(m_argv[i]);
      MON_CMDLINE_LOG_DBG( option->longName << " = " << option->value.toString() << " (" << m_argv[i] << ")");
    }
  }
  if(getOption("h").toBool())
  {
    showHelp();
    MON_ABORT;
  }
}

#define MON_CMDLINE_IMPLEMENT_ADDPARAMETR \
  MON_CMDLINE_LOG_DBG("New cmd parameter -" << shortName << ":--" << longName << ":" << description << ", default: " << defaultValue); \
  m_parametres[shortName] = new SCmdLineParameter(shortName, longName, description, mon::lib::base::CVariant(defaultValue), false);

void CCmdLineParcer::addParametr (const std::string &shortName, const std::string &longName, const std::string &description, const std::string &defaultValue )
{
  MON_CMDLINE_IMPLEMENT_ADDPARAMETR;
}

void CCmdLineParcer::addParametr (const std::string &shortName, const std::string &longName, const std::string &description, const int &defaultValue )
{
  MON_CMDLINE_IMPLEMENT_ADDPARAMETR;
}

void CCmdLineParcer::addParametr (const std::string &shortName, const std::string &longName, const std::string &description, const float &defaultValue )
{
  MON_CMDLINE_IMPLEMENT_ADDPARAMETR;
}

void CCmdLineParcer::addParametr ( const std::string &shortName, const std::string &longName, const std::string &description )
{
  MON_CMDLINE_LOG_DBG("New cmd flag -" << shortName << ":--" << longName << ":" << description << ", default false");
  m_parametres[shortName] = new SCmdLineParameter(shortName, longName, description, mon::lib::base::CVariant(false), true);
}

SCmdLineParameter* CCmdLineParcer::findOption ( const std::string &argvOptionString )
{
  SCmdLineParameter *opt;
  for(auto &p : m_parametres)
  {
    opt = p.second;
    if(compareOptions(opt, argvOptionString))
    {
      MON_CMDLINE_LOG_DBG( "Found parametr '" << argvOptionString <<
                           "'. Interpret as [-" << opt->shortName << "][--" << opt->longName << "], with default '" << opt->value.toString() << "'");
      return opt;
    }
  }
  MON_LOG_ERR( "Unknown command line option: " << argvOptionString );
  MON_ABORT;
  return opt;
}

bool CCmdLineParcer::compareOptions ( const SCmdLineParameter *parametr, const std::string option )
{
  if(parametr->shortName.compare(option.substr(1, option.length())) == 0) { return true; }
  if(parametr->longName .compare(option.substr(2, option.length())) == 0) { return true; }
  return false;
}

mon::lib::base::CVariant CCmdLineParcer::getOption ( const std::string &shortName )
{
  return m_parametres[shortName]->value;
}

void CCmdLineParcer::showHelp ()
{
  SCmdLineParameter *opt;
  for(auto &p : m_parametres)
  {
    opt = p.second;
    std::cout << "\t-" << opt->shortName << ", "
              << "--" << opt->longName << " "
              << (opt->isFlag ? ": " :  "<value>: ")
              << opt->description << (opt->isFlag ? "" : " (current value: " + opt->value.toString() + ")")
              << std::endl;
  }
}


}
}
}
