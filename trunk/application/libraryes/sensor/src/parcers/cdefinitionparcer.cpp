/* %Id% */
#include "cdefinitionparcer.h"
#include "infinity-cycle-helper.h"

// MON_DEFINITION_PARCER
//#define MON_DEFINITION_PARCER_PRINT_CURRENT_CHAR_ENABLED
//#define MON_DEFINITION_PARCER_PRINT_LOOP_STATUS_ENABLED
//#define MON_DEFINITION_PARCER_PRINT_VARIABLES_ENABLED

#ifdef MON_DEFINITION_PARCER_PRINT_LOOP_STATUS_ENABLED
  #define MON_DEFINITION_PARCER_PRINT_LOOP_STATUS(_name,_status) MON_LOG_DBG("Loop " #_name " " #_status);
  #define MON_DEFINITION_PARCER_PRINT_LOOP_STATUS_STARTED(_name) MON_DEFINITION_PARCER_PRINT_LOOP_STATUS(_name, started); bool breaked##_name = false;
  #define MON_DEFINITION_PARCER_PRINT_LOOP_STATUS_STOPPED(_name) if(!breaked##_name) { MON_DEFINITION_PARCER_PRINT_LOOP_STATUS(_name, stopped) }
  #define MON_DEFINITION_PARCER_PRINT_LOOP_STATUS_BREAKED(_name) MON_DEFINITION_PARCER_PRINT_LOOP_STATUS(_name, breaked); breaked##_name = true;
#else
  #define MON_DEFINITION_PARCER_PRINT_LOOP_STATUS_STARTED(_name)
  #define MON_DEFINITION_PARCER_PRINT_LOOP_STATUS_STOPPED(_name)
  #define MON_DEFINITION_PARCER_PRINT_LOOP_STATUS_BREAKED(_name)
#endif

#ifdef MON_DEFINITION_PARCER_PRINT_CURRENT_CHAR_ENABLED
  #define MON_DEFINITION_PARCER_PRINT_CURRENT_CHAR(_name) MON_LOG_DBG("Parcer (loop `" #_name "`) current character: " << MON_DEFINITION_PARCER_CURRENT_CHARACTER(_name));
#else
  #define MON_DEFINITION_PARCER_PRINT_CURRENT_CHAR(_name)
#endif

#define MON_DEFINITION_PARCER_CURRENT_CHARACTER(_name) current_character___##_name
#define MON_DEFINITION_PARCER_BUFFER_NAME(_name) buffer___##_name
#define MON_DEFINITION_PARCER_BUFFER_APPEND(_name) MON_DEFINITION_PARCER_BUFFER_NAME(_name) += MON_DEFINITION_PARCER_CURRENT_CHARACTER(_name);
#define MON_DEFINITION_PARCER_BUFFER_RESET(_name) MON_DEFINITION_PARCER_BUFFER_NAME(_name) = "";
#define MON_DEFINITION_PARCER_CHECK_BUFFER(_name,_no,_err_message) if( _no MON_DEFINITION_PARCER_BUFFER_NAME(_name).empty()) { MON_DEFINITION_PARCER_ERROR(_err_message << MON_DEFINITION_PARCER_BUFFER_ERROR_PART(_name)); }
#define MON_DEFINITION_PARCER_ERROR_IF_BUFFER_EMPTY(_name, _err_message)   MON_DEFINITION_PARCER_CHECK_BUFFER(_name, ,_err_message)
#define MON_DEFINITION_PARCER_ERROR_IF_BUFFER_NO_EMPTY(_name, _err_message) MON_DEFINITION_PARCER_CHECK_BUFFER(_name,!,_err_message)
#define MON_DEFINITION_PARCER_LOOP_BREAK_LABEL_NAME(_name) label_end___##_name
#define MON_DEFINITION_PARCER_LOOP_BEGIN_LABEL_NAME(_name) label_begin___##_name
#define MON_DEFINITION_PARCER_BREAK_LOOP(_name)   goto MON_DEFINITION_PARCER_LOOP_BREAK_LABEL_NAME(_name);
#define MON_DEFINITION_PARCER_RESTART_LOOP(_name) goto MON_DEFINITION_PARCER_LOOP_BEGIN_LABEL_NAME(_name);
#define MON_DEFINITION_PARCER_LOOP_BEGIN(_name) \
{ \
  MON_DEFINITION_PARCER_PRINT_LOOP_STATUS_STARTED(_name); \
  TCFChar MON_DEFINITION_PARCER_CURRENT_CHARACTER(_name); \
  std::string MON_DEFINITION_PARCER_BUFFER_NAME(_name) = ""; \
  MON_DEFINITION_PARCER_RESTART_LOOP(_name) \
  MON_DEFINITION_PARCER_LOOP_BEGIN_LABEL_NAME(_name): ; \
  for(;;) \
  { \
    MON_DEFINITION_PARCER_CURRENT_CHARACTER(_name) = readChar(); \
    if(m_eof || m_error) { MON_DEFINITION_PARCER_BREAK_LOOP(_name); } \
    MON_DEFINITION_PARCER_PRINT_CURRENT_CHAR(_name) \
    switch(MON_DEFINITION_PARCER_CURRENT_CHARACTER(_name)) \
    {
#define MON_DEFINITION_PARCER_LOOP_END(_name) \
    } \
  } \
  MON_DEFINITION_PARCER_LOOP_BREAK_LABEL_NAME(_name): MON_DEFINITION_PARCER_PRINT_LOOP_STATUS_BREAKED(_name); \
  MON_DEFINITION_PARCER_PRINT_LOOP_STATUS_STOPPED(_name); \
}

#define MON_DEFINITION_PARCER_BUFFER_ERROR_PART(_name) " (Buffer contains `" << MON_DEFINITION_PARCER_BUFFER_NAME(_name) << "`)"

#define MON_DEFINITION_PARCER_ERROR(_message) \
{ MON_LOG_ERR("Error in DEFINITIONiguration ("<< m_filename <<"), line " \
  << m_linesCount+1 << ", symbol " << m_currentLineCharactersCount-1 << ": " \
  << _message); MON_ABORT; }

#define MON_DEFINITION_PARCER_CASES_WHITE \
  case  ' ':  case '\t':  case '\r': case '\n'

#define MON_DEFINITION_PARCER_CASES_ALPHA \
  case 'a': case 'A':  case 'b': case 'B':  case 'c': case 'C':  case 'd': case 'D':  case 'e': case 'E': \
  case 'f': case 'F':  case 'g': case 'G':  case 'h': case 'H':  case 'i': case 'I':  case 'j': case 'J': \
  case 'k': case 'K':  case 'l': case 'L':  case 'm': case 'M':  case 'n': case 'N':  case 'o': case 'O': \
  case 'p': case 'P':  case 'q': case 'Q':  case 'r': case 'R':  case 's': case 'S':  case 't': case 'T': \
  case 'u': case 'U':  case 'v': case 'V':  case 'w': case 'W':  case 'x': case 'X':  case 'y': case 'Y': \
  case 'z': case 'Z':  case '_'

#define MON_DEFINITION_PARCER_BOOL_COUNT 4
#define MON_DEFINITION_PARCER_BOOL_TRUE(_var)  const char *_var[MON_DEFINITION_PARCER_BOOL_COUNT] = {"on\0" , "true\0" , "yes\0", "1\0"};
#define MON_DEFINITION_PARCER_BOOL_FALSE(_var) const char *_var[MON_DEFINITION_PARCER_BOOL_COUNT] = {"off\0", "false\0", "no\0" , "0\0"};

#define MON_DEFINITION_PARCER_CASES_NUMERIC_DOT case '.': case ','
#define MON_DEFINITION_PARCER_CASES_NUMERIC     case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9'
#define MON_DEFINITION_PARCER_CASES_DELIMITERS  case '{': case '}': case '=': case '.'

#define MON_DEFINITION_PARCER_CASES_AVIALABLE \
  MON_DEFINITION_PARCER_CASES_WHITE: MON_DEFINITION_PARCER_CASES_ALPHA: MON_DEFINITION_PARCER_CASES_NUMERIC: MON_DEFINITION_PARCER_CASES_DELIMITERS



namespace mon
{
namespace lib
{
namespace sensor
{

CDefinitionParcer::CDefinitionParcer()
{
  m_currentIndex = 0;
  m_definitionText = "";
}

CDefinitionParcer::~CDefinitionParcer()
{
}

CDefinition * CDefinitionParcer::parce(const std::string &definition)
{
  m_definitionText = definition;
  CDefinition * result = new CDefinition();
  return result;
}

//TCFChar CDefinitionParcer::readChar()
//{

//}

//void CDefinitionParcer::stepBack()
//{

//}

//void CDefinitionParcer::skipComment()
//{

//}

//std::string CDefinitionParcer::readString(const TCFChar &stringOpenChar)
//{

//}

//void CDefinitionParcer::readValue()
//{

//}


}
}
}
