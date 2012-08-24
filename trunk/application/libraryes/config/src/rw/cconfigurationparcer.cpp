/* %Id% */
#include "cconfigurationparcer.h"
#include "parcer-helper.h"
#include <string.h>

namespace mon
{
namespace lib
{
namespace config
{

CConfigurationParcer::CConfigurationParcer(const std::string &filename, CFolder *root)
  : mon::lib::base::CParcerFile(filename),
    m_root(root)
{}

CConfigurationParcer::~CConfigurationParcer()
{}

void CConfigurationParcer::parce()
{
  if(m_error) { return; }

  MON_LOG_NFO("Loading config from " << filename());
  while(!m_error && !m_eof)
  {
    readFolder(m_root);
  }
  MON_LOG_DBG("Loading config from " << filename() << " done. Lines: " << m_linesCount + 2 << ", symbols: " << m_charactersCount);
}

void CConfigurationParcer::readFolder(CFolder *folder, const mon::lib::base::TStdStringCharacter &lastFolderDelimiter)
{
  #ifdef MON_PARCER_PRINT_VARIABLES_ENABLED
    MON_LOG_DBG("Enter folder " << folder->name());
  #endif

  MON_PARCER_LOOP_BEGIN(variable_name)
  {
    MON_PARCER_CURRENT_CHARACTER_IS_ALPHA(variable_name)
    {
      MON_PARCER_BUFFER_APPEND(variable_name);
      MON_PARCER_LOOP_RESTART(variable_name);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC(variable_name)
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(variable_name, "Variable name must begin only with alpha symbols");
      MON_PARCER_BUFFER_APPEND(variable_name);
      MON_PARCER_LOOP_RESTART(variable_name);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(variable_name)
    {
      MON_PARCER_LOOP_RESTART(variable_name);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(variable_name, '=')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(variable_name, "Variable name can't be empty");
      readValue(folder->file(MON_PARCER_BUFFER(variable_name)));
      MON_PARCER_BUFFER_RESET(variable_name);
      MON_PARCER_LOOP_RESTART(variable_name);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(variable_name, '#')
    {
      skipComment();
      MON_PARCER_LOOP_RESTART(variable_name);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(variable_name, ';')
    {
      MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(variable_name, "Variable path name cannot be without value");
      if(lastFolderDelimiter == '.') { MON_PARCER_LOOP_BREAK(variable_name) }
      MON_PARCER_BUFFER_RESET(variable_name);
      MON_PARCER_LOOP_RESTART(variable_name);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(variable_name, '{')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(variable_name, "Variable path name can't be empty");
      readFolder(folder->folder(MON_PARCER_BUFFER(variable_name)), MON_PARCER_CURRENT_CHARACTER(variable_name));
      if(lastFolderDelimiter == '.') { MON_PARCER_LOOP_BREAK(variable_name) }
      MON_PARCER_BUFFER_RESET(variable_name);
      MON_PARCER_LOOP_RESTART(variable_name);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(variable_name, '}')
    {
      MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(variable_name, "Variable cannot be without value");
      MON_PARCER_LOOP_BREAK(variable_name);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(variable_name, '.')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(variable_name, "Variable path name can't be empty");
      readFolder(folder->folder(MON_PARCER_BUFFER(variable_name)), MON_PARCER_CURRENT_CHARACTER(variable_name));
      if(lastFolderDelimiter == '.') { MON_PARCER_LOOP_BREAK(variable_name) }
      MON_PARCER_BUFFER_RESET(variable_name);
      MON_PARCER_LOOP_RESTART(variable_name);
    }
    parcerError("Variable name must contain only alpha, numeric and '_' symbols" MON_PARCER_BUFFER_ERROR_PART(variable_name));
  }
  MON_PARCER_LOOP_END(variable_name);

  #ifdef MON_PARCER_PRINT_VARIABLES_ENABLED
    MON_LOG_DBG("Leave folder " << folder->name())
  #endif
}

void CConfigurationParcer::readValue(CFile *file)
{
  mon::lib::base::EContentType c_type = mon::lib::base::ctUnknown;
  bool underZero = false;
  MON_PARCER_LOOP_BEGIN(variable_value)
  {
    MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(variable_value)
    {
      MON_PARCER_LOOP_RESTART(variable_value);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_QUOTATION(variable_value)
    {
      MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(variable_value, "Junk before string");
      MON_PARCER_BUFFER(variable_value) = readString(MON_PARCER_CURRENT_CHARACTER(variable_value));
      c_type = mon::lib::base::ctString;
      MON_PARCER_LOOP_RESTART(variable_value);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(variable_value, ';')
    {
      #ifdef MON_PARCER_PRINT_VARIABLES_ENABLED
      switch(c_type)
      {
        case mon::lib::base::ctBool   : MON_LOG_DBG("Value '" << file->name() << "', bool: `"   << MON_PARCER_BUFFER(variable_value) << "`"); break;
        case mon::lib::base::ctString : MON_LOG_DBG("Value '" << file->name() << "', string: `" << MON_PARCER_BUFFER(variable_value) << "`"); break;
        case mon::lib::base::ctInt    : MON_LOG_DBG("Value '" << file->name() << "', int: `"    << MON_PARCER_BUFFER(variable_value) << "`"); break;
        case mon::lib::base::ctFloat  : MON_LOG_DBG("Value '" << file->name() << "', float: `"  << MON_PARCER_BUFFER(variable_value) << "`"); break;
        case mon::lib::base::ctUnknown: parcerError("Value '" + file->name() + "', Unknown value type" MON_PARCER_BUFFER_ERROR_PART(variable_value));
      }
      #endif
      switch(c_type)
      {
        case mon::lib::base::ctBool   :
        {
          file->set(convertBool(MON_PARCER_BUFFER(variable_value)));
          break;
        }
        case mon::lib::base::ctString :
        {
          file->set(MON_PARCER_BUFFER(variable_value));
          break;
        }
        case mon::lib::base::ctInt    :
        {
          file->set(mon::lib::base::toInt(MON_PARCER_BUFFER(variable_value)) * (underZero?-1:1));
          break;
        }
        case mon::lib::base::ctFloat  :
        {
          file->set(mon::lib::base::toFloat(MON_PARCER_BUFFER(variable_value)) * (underZero?-1:1));
          break;
        }
        case mon::lib::base::ctUnknown:
        {
          parcerError("Value '" + file->name() + "', Unknown value type" MON_PARCER_BUFFER_ERROR_PART(variable_value));
        }
      }
      stepBack();
      MON_PARCER_LOOP_BREAK(variable_value);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(variable_value, '-')
    {
      MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(variable_value, "`-` must be before number");
      underZero = true;
      MON_PARCER_LOOP_RESTART(variable_value);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC(variable_value)
    {
      MON_PARCER_BUFFER_APPEND(variable_value);
      if(c_type == mon::lib::base::ctUnknown)  { c_type = mon::lib::base::ctInt; }
      MON_PARCER_LOOP_RESTART(variable_value);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC_DOT(variable_value)
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(variable_value, "Missing numeric before dot");
      if(c_type == mon::lib::base::ctFloat) { parcerError("Double numeric dot?" MON_PARCER_BUFFER_ERROR_PART(variable_value)); }
      MON_PARCER_BUFFER_RESET(variable_value);
      c_type = mon::lib::base::ctFloat;
      MON_PARCER_LOOP_RESTART(variable_value);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_ALPHA(variable_value)
    {
      MON_PARCER_BUFFER_APPEND(variable_value);
      if(c_type == mon::lib::base::ctUnknown)  { c_type = mon::lib::base::ctBool; }
      MON_PARCER_LOOP_RESTART(variable_value);
    }
    parcerError("Misplaced character" MON_PARCER_BUFFER_ERROR_PART(variable_value));
  }
  MON_PARCER_LOOP_END(variable_value);

}

}
}
}
