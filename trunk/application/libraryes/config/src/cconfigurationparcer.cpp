/* %Id% */
#include "cconfigurationparcer.h"
#include "st.h"
#include "signals-helper.h"
#include "infinity-cycle-helper.h"
#include <stdlib.h>
#include <string.h>

// MON_CONF_PARCER
//#define MON_CONF_PARCER_PRINT_CURRENT_CHAR_ENABLED
//#define MON_CONF_PARCER_PRINT_LOOP_STATUS_ENABLED
//#define MON_CONF_PARCER_PRINT_VARIABLES_ENABLED

#ifdef MON_CONF_PARCER_PRINT_LOOP_STATUS_ENABLED
  #define MON_CONF_PARCER_PRINT_LOOP_STATUS(_name,_status) MON_LOG_DBG("Loop " #_name " " #_status);
  #define MON_CONF_PARCER_PRINT_LOOP_STATUS_STARTED(_name) MON_CONF_PARCER_PRINT_LOOP_STATUS(_name, started); bool breaked##_name = false;
  #define MON_CONF_PARCER_PRINT_LOOP_STATUS_STOPPED(_name) if(!breaked##_name) { MON_CONF_PARCER_PRINT_LOOP_STATUS(_name, stopped) }
  #define MON_CONF_PARCER_PRINT_LOOP_STATUS_BREAKED(_name) MON_CONF_PARCER_PRINT_LOOP_STATUS(_name, breaked); breaked##_name = true;
#else
  #define MON_CONF_PARCER_PRINT_LOOP_STATUS_STARTED(_name)
  #define MON_CONF_PARCER_PRINT_LOOP_STATUS_STOPPED(_name)
  #define MON_CONF_PARCER_PRINT_LOOP_STATUS_BREAKED(_name)
#endif

#ifdef MON_CONF_PARCER_PRINT_CURRENT_CHAR_ENABLED
  #define MON_CONF_PARCER_PRINT_CURRENT_CHAR(_name) MON_LOG_DBG("Parcer (loop `" #_name "`) current character: " << MON_CONF_PARCER_CURRENT_CHARACTER(_name));
#else
  #define MON_CONF_PARCER_PRINT_CURRENT_CHAR(_name)
#endif

#define MON_CONF_PARCER_CURRENT_CHARACTER(_name) current_character___##_name
#define MON_CONF_PARCER_BUFFER_NAME(_name) buffer___##_name
#define MON_CONF_PARCER_BUFFER_APPEND(_name) MON_CONF_PARCER_BUFFER_NAME(_name) += MON_CONF_PARCER_CURRENT_CHARACTER(_name);
#define MON_CONF_PARCER_BUFFER_RESET(_name) MON_CONF_PARCER_BUFFER_NAME(_name) = "";
#define MON_CONF_PARCER_CHECK_BUFFER(_name,_no,_err_message) if( _no MON_CONF_PARCER_BUFFER_NAME(_name).empty()) { MON_CONF_PARCER_ERROR(_err_message << MON_CONF_PARCER_BUFFER_ERROR_PART(_name)); }
#define MON_CONF_PARCER_ERROR_IF_BUFFER_EMPTY(_name, _err_message)   MON_CONF_PARCER_CHECK_BUFFER(_name, ,_err_message)
#define MON_CONF_PARCER_ERROR_IF_BUFFER_NO_EMPTY(_name, _err_message) MON_CONF_PARCER_CHECK_BUFFER(_name,!,_err_message)
#define MON_CONF_PARCER_LOOP_BREAK_LABEL_NAME(_name) label_end___##_name
#define MON_CONF_PARCER_LOOP_BEGIN_LABEL_NAME(_name) label_begin___##_name
#define MON_CONF_PARCER_BREAK_LOOP(_name)   goto MON_CONF_PARCER_LOOP_BREAK_LABEL_NAME(_name);
#define MON_CONF_PARCER_RESTART_LOOP(_name) goto MON_CONF_PARCER_LOOP_BEGIN_LABEL_NAME(_name);
#define MON_CONF_PARCER_LOOP_BEGIN(_name) \
{ \
  MON_CONF_PARCER_PRINT_LOOP_STATUS_STARTED(_name); \
  TCFChar MON_CONF_PARCER_CURRENT_CHARACTER(_name); \
  std::string MON_CONF_PARCER_BUFFER_NAME(_name) = ""; \
  MON_CONF_PARCER_RESTART_LOOP(_name) \
  MON_CONF_PARCER_LOOP_BEGIN_LABEL_NAME(_name): ; \
  for(;;) \
  { \
    MON_CONF_PARCER_CURRENT_CHARACTER(_name) = readChar(); \
    if(m_eof || m_error) { MON_CONF_PARCER_BREAK_LOOP(_name); } \
    MON_CONF_PARCER_PRINT_CURRENT_CHAR(_name) \
    switch(MON_CONF_PARCER_CURRENT_CHARACTER(_name)) \
    {
#define MON_CONF_PARCER_LOOP_END(_name) \
    } \
  } \
  MON_CONF_PARCER_LOOP_BREAK_LABEL_NAME(_name): MON_CONF_PARCER_PRINT_LOOP_STATUS_BREAKED(_name); \
  MON_CONF_PARCER_PRINT_LOOP_STATUS_STOPPED(_name); \
}

#define MON_CONF_PARCER_BUFFER_ERROR_PART(_name) " (Buffer contains `" << MON_CONF_PARCER_BUFFER_NAME(_name) << "`)"

#define MON_CONF_PARCER_ERROR(_message) \
{ MON_LOG_ERR("Error in configuration ("<< m_filename <<"), line " \
  << m_linesCount+1 << ", symbol " << m_currentLineCharactersCount-1 << ": " \
  << _message); MON_ABORT; }

#define MON_CONF_PARCER_CASES_WHITE \
  case  ' ':  case '\t':  case '\r': case '\n'

#define MON_CONF_PARCER_CASES_ALPHA \
  case 'a': case 'A':  case 'b': case 'B':  case 'c': case 'C':  case 'd': case 'D':  case 'e': case 'E': \
  case 'f': case 'F':  case 'g': case 'G':  case 'h': case 'H':  case 'i': case 'I':  case 'j': case 'J': \
  case 'k': case 'K':  case 'l': case 'L':  case 'm': case 'M':  case 'n': case 'N':  case 'o': case 'O': \
  case 'p': case 'P':  case 'q': case 'Q':  case 'r': case 'R':  case 's': case 'S':  case 't': case 'T': \
  case 'u': case 'U':  case 'v': case 'V':  case 'w': case 'W':  case 'x': case 'X':  case 'y': case 'Y': \
  case 'z': case 'Z':  case '_'

#define MON_CONF_PARCER_BOOL_COUNT 4
#define MON_CONF_PARCER_BOOL_TRUE(_var)  const char *_var[MON_CONF_PARCER_BOOL_COUNT] = {"on\0" , "true\0" , "yes\0", "1\0"};
#define MON_CONF_PARCER_BOOL_FALSE(_var) const char *_var[MON_CONF_PARCER_BOOL_COUNT] = {"off\0", "false\0", "no\0" , "0\0"};

#define MON_CONF_PARCER_CASES_NUMERIC_DOT case '.': case ','
#define MON_CONF_PARCER_CASES_NUMERIC     case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9'
#define MON_CONF_PARCER_CASES_DELIMITERS  case '{': case '}': case '=': case '.'

#define MON_CONF_PARCER_CASES_AVIALABLE \
  MON_CONF_PARCER_CASES_WHITE: MON_CONF_PARCER_CASES_ALPHA: MON_CONF_PARCER_CASES_NUMERIC: MON_CONF_PARCER_CASES_DELIMITERS

namespace mon
{
namespace lib
{
namespace config
{

CConfigurationParcer::CConfigurationParcer(const std::string &filename, CFolder *root) : m_filename(filename), m_root(root)
{
  m_eof        = false;
  m_error      = false;
  m_linesCount = 0;
  m_currentLineCharactersCount = 0;
  m_charactersCount            = 0;
  m_file = fopen(m_filename.c_str(), "r");
  if(m_file == NULL)
  {
    m_error = true;
    MON_PRINT_FILEOP_ERRNO(m_filename, "Open file error");
  }
}

CConfigurationParcer::~CConfigurationParcer()
{
  if(m_error) { return; }

  if(fclose(m_file) == EOF)
  {
    MON_PRINT_FILEOP_ERRNO(m_filename, "Close file error");
  }
}

void CConfigurationParcer::parce()
{
  if(m_error) { return; }

  MON_LOG_NFO("Loading config from " << m_filename);
  while(!m_error && !m_eof)
  {
    readFolder(m_root);
  }
  MON_LOG_DBG("Loading config from " << m_filename << " done. Lines: " << m_linesCount + 2 << ", symbols: " << m_charactersCount);
}

void CConfigurationParcer::readFolder(CFolder *folder, const TCFChar &lastFolderDelimiter)
{
  #ifdef MON_CONF_PARCER_PRINT_VARIABLES_ENABLED
    MON_LOG_DBG("Enter folder " << folder->name());
  #endif

  MON_CONF_PARCER_LOOP_BEGIN(variable_name)
  MON_CONF_PARCER_CASES_ALPHA:
  {
    MON_CONF_PARCER_BUFFER_APPEND(variable_name)
    break;
  }
  MON_CONF_PARCER_CASES_NUMERIC:
  {
    MON_CONF_PARCER_ERROR_IF_BUFFER_EMPTY(variable_name, "Variable name must begin only with alpha symbols")
    MON_CONF_PARCER_BUFFER_APPEND(variable_name)
    break;
  }
  MON_CONF_PARCER_CASES_WHITE: { break; }
  case  '=':
  {
    MON_CONF_PARCER_ERROR_IF_BUFFER_EMPTY(variable_name, "Variable name can't be empty")
    readValue(folder->file(MON_CONF_PARCER_BUFFER_NAME(variable_name)));
    MON_CONF_PARCER_BUFFER_RESET(variable_name)
    break;
  }
  case  '#': { skipComment(); break; }
  case  ';':
  {
    MON_CONF_PARCER_ERROR_IF_BUFFER_NO_EMPTY(variable_name, "Variable path name cannot be without value")
    if(lastFolderDelimiter == '.') { MON_CONF_PARCER_BREAK_LOOP(variable_name) }
    MON_CONF_PARCER_BUFFER_RESET(variable_name)
    break;
  }
  case  '{':
  {
    MON_CONF_PARCER_ERROR_IF_BUFFER_EMPTY(variable_name, "Variable path name can't be empty")
    readFolder(folder->folder(MON_CONF_PARCER_BUFFER_NAME(variable_name)), MON_CONF_PARCER_CURRENT_CHARACTER(variable_name));
    if(lastFolderDelimiter == '.') { MON_CONF_PARCER_BREAK_LOOP(variable_name) }
    MON_CONF_PARCER_BUFFER_RESET(variable_name)
    break;
  }
  case  '}':
  {
    MON_CONF_PARCER_ERROR_IF_BUFFER_NO_EMPTY(variable_name, "Variable path name cannot be without value")
    MON_CONF_PARCER_BREAK_LOOP(variable_name)
  }
  case  '.':
  {
    MON_CONF_PARCER_ERROR_IF_BUFFER_EMPTY(variable_name, "Variable path name can't be empty");
    readFolder(folder->folder(MON_CONF_PARCER_BUFFER_NAME(variable_name)), MON_CONF_PARCER_CURRENT_CHARACTER(variable_name));
    if(lastFolderDelimiter == '.') { MON_CONF_PARCER_BREAK_LOOP(variable_name) }
    MON_CONF_PARCER_BUFFER_RESET(variable_name)
    break;
  }
  default: { MON_CONF_PARCER_ERROR("Variable name must contain only alpha, numeric and '_' symbols" << MON_CONF_PARCER_BUFFER_ERROR_PART(variable_name)) }
  MON_CONF_PARCER_LOOP_END(variable_name)

  #ifdef MON_CONF_PARCER_PRINT_VARIABLES_ENABLED
    MON_LOG_DBG("Leave folder " << folder->name())
  #endif
}

void CConfigurationParcer::readValue(CFile *file)
{
  mon::lib::base::EContentType c_type = mon::lib::base::ctUnknown;
  bool underZero = false;
  MON_CONF_PARCER_LOOP_BEGIN(variable_value);
  MON_CONF_PARCER_CASES_WHITE:
  case '`':
  case '\'':
  case  '"':
  {
    MON_CONF_PARCER_ERROR_IF_BUFFER_NO_EMPTY(variable_value, "Junk before string");
    MON_CONF_PARCER_BUFFER_NAME(variable_value) = readString(MON_CONF_PARCER_CURRENT_CHARACTER(variable_value));
    c_type = mon::lib::base::ctString;
    break;
  }
  case ';':
  {
    #ifdef MON_CONF_PARCER_PRINT_VARIABLES_ENABLED
    switch(c_type)
    {
      case mon::lib::base::ctBool   : MON_LOG_DBG("Value '" << file->name() << "', bool: `"   << MON_CONF_PARCER_BUFFER_NAME(variable_value) << "`"); break;
      case mon::lib::base::ctString : MON_LOG_DBG("Value '" << file->name() << "', string: `" << MON_CONF_PARCER_BUFFER_NAME(variable_value) << "`"); break;
      case mon::lib::base::ctInt    : MON_LOG_DBG("Value '" << file->name() << "', int: `"    << MON_CONF_PARCER_BUFFER_NAME(variable_value) << "`"); break;
      case mon::lib::base::ctFloat  : MON_LOG_DBG("Value '" << file->name() << "', float: `"  << MON_CONF_PARCER_BUFFER_NAME(variable_value) << "`"); break;
      case mon::lib::base::ctUnknown: MON_CONF_PARCER_ERROR("Value '" << file->name() << "', Unknown value type" << MON_CONF_PARCER_BUFFER_ERROR_PART(variable_value));
    }
    #endif
    switch(c_type)
    {
      case mon::lib::base::ctBool   : file->set(convertBool(MON_CONF_PARCER_BUFFER_NAME(variable_value).c_str())); break;
      case mon::lib::base::ctString : file->set(MON_CONF_PARCER_BUFFER_NAME(variable_value)); break;
      case mon::lib::base::ctInt    : file->set(static_cast<int>(strtol(MON_CONF_PARCER_BUFFER_NAME(variable_value).c_str(), NULL, 10)) * (underZero?-1:1)); break;
      case mon::lib::base::ctFloat  : file->set(strtod(MON_CONF_PARCER_BUFFER_NAME(variable_value).c_str(), NULL) * (underZero?-1:1)); break;
      case mon::lib::base::ctUnknown: MON_CONF_PARCER_ERROR("Value '" << file->name() << "', Unknown value type" << MON_CONF_PARCER_BUFFER_ERROR_PART(variable_value));
    }
    stepBack();
    MON_CONF_PARCER_BREAK_LOOP(variable_value);
  }
  case '-':
  {
    MON_CONF_PARCER_ERROR_IF_BUFFER_NO_EMPTY(variable_value, "`-` must be before number");
    underZero = true;
    break;
  }
  MON_CONF_PARCER_CASES_NUMERIC:
  {
    MON_CONF_PARCER_BUFFER_APPEND(variable_value);
    if(c_type == mon::lib::base::ctUnknown)  { c_type = mon::lib::base::ctInt; }
    break;
  }
  MON_CONF_PARCER_CASES_NUMERIC_DOT:
  {
    MON_CONF_PARCER_ERROR_IF_BUFFER_EMPTY(variable_value, "Missing numeric before dot");
    if(c_type == mon::lib::base::ctFloat) { MON_CONF_PARCER_ERROR("Double numeric dot?" << MON_CONF_PARCER_BUFFER_ERROR_PART(variable_value)); }
    MON_CONF_PARCER_BUFFER_RESET(variable_value)
    c_type = mon::lib::base::ctFloat;
    break;
  }
  MON_CONF_PARCER_CASES_ALPHA:
  {
    MON_CONF_PARCER_BUFFER_APPEND(variable_value);
    if(c_type == mon::lib::base::ctUnknown)  { c_type = mon::lib::base::ctBool; }
    break;
  }
  default:
  {
    MON_CONF_PARCER_ERROR("Misplaced character" << MON_CONF_PARCER_BUFFER_ERROR_PART(variable_value));
  }
  MON_CONF_PARCER_LOOP_END(variable_value);
}

MON_CONF_PARCER_BOOL_TRUE (v_true )
MON_CONF_PARCER_BOOL_FALSE(v_false)
bool CConfigurationParcer::convertBool(const char *buffer)
{
  for(int i = 0; i < MON_CONF_PARCER_BOOL_COUNT; i++)
  {
    if(strcasecmp(v_true [i], buffer) == 0) { return true ; }
    if(strcasecmp(v_false[i], buffer) == 0) { return false; }
  }
  MON_CONF_PARCER_ERROR("Unknown bool value: " << buffer);
  return false;
}

#define MON_STRING_LOOP_CHECK \
  if(!slash && stringOpenChar == MON_CONF_PARCER_CURRENT_CHARACTER(read_string)) { MON_CONF_PARCER_BREAK_LOOP(read_string); }

std::string CConfigurationParcer::readString(const TCFChar &stringOpenChar)
{
  bool slash = false;
  std::string result = "";
  MON_CONF_PARCER_LOOP_BEGIN(read_string);
  case '\\': { if(slash) { result += '\\'; } slash = !slash; break; }
  case '\'': { if(slash) { result += '\'';   slash =  false; break; } MON_STRING_LOOP_CHECK; }
  case  '"': { if(slash) { result +=  '"';   slash =  false; break; } MON_STRING_LOOP_CHECK; }
  case  '`': { if(slash) { result +=  '`';   slash =  false; break; } MON_STRING_LOOP_CHECK; }
  case  'n': { if(slash) { result += '\n';   slash =  false; break; } }
  case  'r': { if(slash) { result += '\r';   slash =  false; break; } }
  case  'b': { if(slash) { result += '\b';   slash =  false; break; } }
  case  't': { if(slash) { result += '\t';   slash =  false; break; } }
  default: result += MON_CONF_PARCER_CURRENT_CHARACTER(read_string);
  MON_CONF_PARCER_LOOP_END(read_string);
  return result;
}

void CConfigurationParcer::skipComment()
{
  MON_CONF_PARCER_LOOP_BEGIN(read_comment);
  case '\n': MON_CONF_PARCER_BREAK_LOOP(read_comment);
  default: break;
  MON_CONF_PARCER_LOOP_END(read_comment);
}

TCFChar CConfigurationParcer::readChar()
{
  int result = fgetc(m_file);
  if(result == -1 && result != EOF)
  {
    m_error = true;
    MON_PRINT_FILEOP_ERRNO(m_filename, "Read file error");
    return 0;
  }

  m_eof = result == EOF;
  TCFChar character = static_cast<TCFChar>(result);
  // statistics
  switch(character)
  {
    case '\n':
    {
      m_linesCount++;
      m_currentLineCharactersCount = 0;
    }
    case '\r': break;
    default:
    {
      m_charactersCount++;
      m_currentLineCharactersCount++;
    }
  }
  return character;
}

void CConfigurationParcer::stepBack()
{
  if(fseek(m_file, -sizeof(TCFChar), SEEK_CUR) == -1)
  {
    m_error = true;
    MON_PRINT_FILEOP_ERRNO(m_filename, "Seek");
    return;
  }
  m_charactersCount--;
  m_currentLineCharactersCount--;
}

}
}
}
