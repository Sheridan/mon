/* %Id% */
#include "libraryes/config/rw/cconfigurationparcer.h"
#include "libraryes/base/parcer/parcer-helper.h"
#include <string.h>
#include <limits>

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
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(variable_name, ':')
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(variable_name, "Keyword name can't be empty");
      MON_PARCER_IS_KEYWORD(variable_name, "include")
      {
          includeFile(folder);
          MON_PARCER_BUFFER_RESET(variable_name);
          MON_PARCER_LOOP_RESTART(variable_name);
      }
      parcerError("Unknown keyword " MON_PARCER_BUFFER_ERROR_PART(variable_name), MON_PARCER_CURRENT_CHARACTER(variable_name));
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
      MON_PARCER_LOOP_BREAK(variable_name);
    }
    parcerError("Variable name must contain only alpha, numeric and '_' symbols" MON_PARCER_BUFFER_ERROR_PART(variable_name), MON_PARCER_CURRENT_CHARACTER(variable_name));
  }
  MON_PARCER_LOOP_END(variable_name);

  #ifdef MON_PARCER_PRINT_VARIABLES_ENABLED
    MON_LOG_DBG("Leave folder " << folder->name())
  #endif
}

void CConfigurationParcer::readValue(CFile *file)
{
  mon::lib::base::EContentType c_type = mon::lib::base::EContentType::Unknown;
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
      c_type = mon::lib::base::EContentType::String;
      MON_PARCER_LOOP_RESTART(variable_value);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(variable_value, ';')
    {
      switch(c_type)
      {
        case mon::lib::base::EContentType::Bool  : { file->set(convertBool(MON_PARCER_BUFFER(variable_value))); break; }
        case mon::lib::base::EContentType::String: { file->set(            MON_PARCER_BUFFER(variable_value)) ; break; }
        case mon::lib::base::EContentType::Int:
        {
          if(underZero)
          {
            long long val = mon::lib::base::toLLong(MON_PARCER_BUFFER(variable_value)) * -1;
                   if(val >= std::numeric_limits<short>    ::min()) { file->set(mon::lib::base::toShort (MON_PARCER_BUFFER(variable_value)) * -1); }
            else { if(val >= std::numeric_limits<int>      ::min()) { file->set(mon::lib::base::toInt   (MON_PARCER_BUFFER(variable_value)) * -1); }
            else { if(val >= std::numeric_limits<long>     ::min()) { file->set(mon::lib::base::toLong  (MON_PARCER_BUFFER(variable_value)) * -1); }
            else { if(val >= std::numeric_limits<long long>::min()) { file->set(mon::lib::base::toLLong (MON_PARCER_BUFFER(variable_value)) * -1); }
                                                                                                                                               } } }
          }
          else
          {
            unsigned long long val = mon::lib::base::toULLong(MON_PARCER_BUFFER(variable_value));
                   if(val <= std::numeric_limits<short>             ::max()) { file->set(mon::lib::base::toShort (MON_PARCER_BUFFER(variable_value))); }
            else { if(val <= std::numeric_limits<unsigned short>    ::max()) { file->set(mon::lib::base::toUShort(MON_PARCER_BUFFER(variable_value))); }
            else { if(val <= std::numeric_limits<int>               ::max()) { file->set(mon::lib::base::toInt   (MON_PARCER_BUFFER(variable_value))); }
            else { if(val <= std::numeric_limits<unsigned int>      ::max()) { file->set(mon::lib::base::toUInt  (MON_PARCER_BUFFER(variable_value))); }
            else { if(val <= std::numeric_limits<long>              ::max()) { file->set(mon::lib::base::toLong  (MON_PARCER_BUFFER(variable_value))); }
            else { if(val <= std::numeric_limits<unsigned long>     ::max()) { file->set(mon::lib::base::toULong (MON_PARCER_BUFFER(variable_value))); }
            else { if(val <= std::numeric_limits<long long>         ::max()) { file->set(mon::lib::base::toLLong (MON_PARCER_BUFFER(variable_value))); }
            else { if(val <= std::numeric_limits<unsigned long long>::max()) { file->set(mon::lib::base::toULLong(MON_PARCER_BUFFER(variable_value))); }
                                                                                                                                           } } } } } } }
          }
          break;
        }
        case mon::lib::base::EContentType::Float:
        {
          double val = mon::lib::base::toDouble(MON_PARCER_BUFFER(variable_value)) * (underZero?-1:1);
                 if(val >= std::numeric_limits<float> ::min() and val <= std::numeric_limits<float> ::max()) { file->set(mon::lib::base::toFloat (MON_PARCER_BUFFER(variable_value)) * (underZero?-1:1)); }
          else { if(val >= std::numeric_limits<double>::min() and val <= std::numeric_limits<double>::max()) { file->set(mon::lib::base::toDouble(MON_PARCER_BUFFER(variable_value)) * (underZero?-1:1)); }
                                                                                                                                                                                               }
          break;
        }
        default: { parcerError("Value '" + file->name() + "', Unknown value type" MON_PARCER_BUFFER_ERROR_PART(variable_value), MON_PARCER_CURRENT_CHARACTER(variable_value)); }
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
      if(c_type == mon::lib::base::EContentType::Unknown)  { c_type = mon::lib::base::EContentType::Int; }
      MON_PARCER_LOOP_RESTART(variable_value);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC_DOT(variable_value)
    {
      MON_PARCER_ERROR_IF_BUFFER_EMPTY(variable_value, "Missing numeric before dot");
      if(c_type == mon::lib::base::EContentType::Float) { parcerError("Double numeric dot?" MON_PARCER_BUFFER_ERROR_PART(variable_value), MON_PARCER_CURRENT_CHARACTER(variable_value)); }
      MON_PARCER_BUFFER_RESET(variable_value);
      c_type = mon::lib::base::EContentType::Float;
      MON_PARCER_LOOP_RESTART(variable_value);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_ALPHA(variable_value)
    {
      MON_PARCER_BUFFER_APPEND(variable_value);
      if(c_type == mon::lib::base::EContentType::Unknown)  { c_type = mon::lib::base::EContentType::Bool; }
      MON_PARCER_LOOP_RESTART(variable_value);
    }
    parcerError("Misplaced character" MON_PARCER_BUFFER_ERROR_PART(variable_value), MON_PARCER_CURRENT_CHARACTER(variable_value));
  }
  MON_PARCER_LOOP_END(variable_value);
}

void CConfigurationParcer::includeFile(CFolder *folder)
{
    CFile file("include", folder);
    readValue(&file);
    if (file.contentType() != mon::lib::base::EContentType::String)
    {
        parcerError("Include file path must be a string");
    }
    CConfigurationParcer includeParcer(file.toString(), folder);
    includeParcer.parce();
}

}
}
}
