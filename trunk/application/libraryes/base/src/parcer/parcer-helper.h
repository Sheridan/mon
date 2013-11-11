#ifndef PARCERHELPER_H
#define PARCERHELPER_H
#include "st.h"
#include "signals-helper.h"
#include "infinity-cycle-helper.h"
#include "logger-helper.h"

// -----------------------------------------------  debug
//#define MON_PARCER_PRINT_CURRENT_CHAR_ENABLED
//#define MON_PARCER_PRINT_LOOP_STATUS_ENABLED
//#define MON_PARCER_PRINT_VARIABLES_ENABLED

#ifdef MON_PARCER_PRINT_LOOP_STATUS_ENABLED
  #define MON_PARCER_PRINT_LOOP_STATUS(_name,_status) MON_LOG_DBG("Loop " #_name " " #_status);
  #define MON_PARCER_PRINT_LOOP_STATUS_STARTED(_name) MON_PARCER_PRINT_LOOP_STATUS(_name, started); bool breaked##_name = false;
  #define MON_PARCER_PRINT_LOOP_STATUS_STOPPED(_name) if(!breaked##_name) { MON_PARCER_PRINT_LOOP_STATUS(_name, stopped) }
  #define MON_PARCER_PRINT_LOOP_STATUS_BREAKED(_name) MON_PARCER_PRINT_LOOP_STATUS(_name, breaked); breaked##_name = true;
#else
  #define MON_PARCER_PRINT_LOOP_STATUS_STARTED(_name)
  #define MON_PARCER_PRINT_LOOP_STATUS_STOPPED(_name)
  #define MON_PARCER_PRINT_LOOP_STATUS_BREAKED(_name)
#endif

#ifdef MON_PARCER_PRINT_CURRENT_CHAR_ENABLED
  #define MON_PARCER_PRINT_CURRENT_CHAR(_name) MON_LOG_DBG("Parcer (loop `" #_name "`) current character: " << MON_PARCER_CURRENT_CHARACTER(_name));
#else
  #define MON_PARCER_PRINT_CURRENT_CHAR(_name)
#endif

#define MON_PARCER_BUFFER_ERROR_PART(_name) " (Buffer contains `" + MON_PARCER_BUFFER(_name) + "`)"
// -----------------------------------------------  debug

// -----------------------------------------------  names
#define MON_PARCER_CURRENT_CHARACTER(_name)     current_character___##_name
#define MON_PARCER_BUFFER(_name)                buffer___##_name
#define MON_PARCER_LOOP_BREAK_LABEL_NAME(_name) MON_INFINITY_LOOP_END_LABEL_NAME(_name)
#define MON_PARCER_LOOP_BEGIN_LABEL_NAME(_name) MON_INFINITY_LOOP_BEGIN_LABEL_NAME(_name)
// -----------------------------------------------  names

// -----------------------------------------------  buffer
#define MON_PARCER_BUFFER_APPEND(_name) MON_PARCER_BUFFER(_name) += MON_PARCER_CURRENT_CHARACTER(_name);
#define MON_PARCER_BUFFER_RESET(_name)  MON_PARCER_BUFFER(_name) = "";
// -----------------------------------------------  buffer

// -----------------------------------------------  error
#define MON_PARCER_ERROR(_name, _err_message) parcerError(_err_message  MON_PARCER_BUFFER_ERROR_PART(_name), MON_PARCER_CURRENT_CHARACTER(_name));
// -----------------------------------------------  error

// -----------------------------------------------  buffer checks
#define MON_PARCER_CHECK_BUFFER(_name,_no,_err_message)          if( _no MON_PARCER_BUFFER(_name).empty()) { MON_PARCER_ERROR(_name, _err_message) }
#define MON_PARCER_ERROR_IF_BUFFER_EMPTY(_name, _err_message)    MON_PARCER_CHECK_BUFFER(_name, ,_err_message)
#define MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(_name, _err_message) MON_PARCER_CHECK_BUFFER(_name,!,_err_message)
// -----------------------------------------------  buffer checks

// -----------------------------------------------  loop control
#define MON_PARCER_LOOP_BREAK(_name)   MON_INFINITY_LOOP_BREAK(_name)
#define MON_PARCER_LOOP_RESTART(_name) MON_INFINITY_LOOP_RESTART(_name);
#define MON_PARCER_LOOP_BEGIN(_name) \
{ \
  MON_PARCER_PRINT_LOOP_STATUS_STARTED(_name); \
  mon::lib::base::TStdStringCharacter MON_PARCER_CURRENT_CHARACTER(_name) = 0; \
  std::string MON_PARCER_BUFFER(_name) = std::string(); \
  MON_INFINITY_LOOP_BEGIN(_name) \
  { \
    MON_PARCER_CURRENT_CHARACTER(_name) = readCharacter(); \
    if(m_error || m_eof) { MON_PARCER_LOOP_BREAK(_name) } \
    MON_PARCER_PRINT_CURRENT_CHAR(_name)

#define MON_PARCER_LOOP_END(_name) \
  } \
  MON_INFINITY_LOOP_END(_name) \
  MON_PARCER_PRINT_LOOP_STATUS_BREAKED(_name); \
  MON_PARCER_PRINT_LOOP_STATUS_STOPPED(_name); \
}
// -----------------------------------------------  loop control

// -----------------------------------------------  characters check
#define MON_PARCER_CURRENT_CHARACTER_ALPHA_CHECK(_name)            isAlpha     (MON_PARCER_CURRENT_CHARACTER(_name))
#define MON_PARCER_CURRENT_CHARACTER_NUMERIC_CHECK(_name)          isNumeric   (MON_PARCER_CURRENT_CHARACTER(_name))
#define MON_PARCER_CURRENT_CHARACTER_NUMERIC_DOT_CHECK(_name)      isNumericDot(MON_PARCER_CURRENT_CHARACTER(_name))
#define MON_PARCER_CURRENT_CHARACTER_WHITESPACE_CHECK(_name)       isWhiteSpace(MON_PARCER_CURRENT_CHARACTER(_name))
#define MON_PARCER_CURRENT_CHARACTER_QUOTATION_CHECK(_name)        isQuotation (MON_PARCER_CURRENT_CHARACTER(_name))
#define MON_PARCER_CURRENT_CHARACTER_MARKER_CHECK(_name)           isMArker    (MON_PARCER_CURRENT_CHARACTER(_name))
#define MON_PARCER_CURRENT_CHARACTER_EQUAL_CHECK(_name,_character) MON_PARCER_CURRENT_CHARACTER(_name) == _character

#define MON_PARCER_CURRENT_CHARACTER_IS_ALPHA(_name)            if (MON_PARCER_CURRENT_CHARACTER_ALPHA_CHECK(_name))
#define MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC(_name)          if (MON_PARCER_CURRENT_CHARACTER_NUMERIC_CHECK(_name))
#define MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC_DOT(_name)      if (MON_PARCER_CURRENT_CHARACTER_NUMERIC_DOT_CHECK(_name))
#define MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(_name)       if (MON_PARCER_CURRENT_CHARACTER_WHITESPACE_CHECK(_name))
#define MON_PARCER_CURRENT_CHARACTER_IS_QUOTATION(_name)        if (MON_PARCER_CURRENT_CHARACTER_QUOTATION_CHECK(_name))
#define MON_PARCER_CURRENT_CHARACTER_IS_MARKER(_name)           if (MON_PARCER_CURRENT_CHARACTER_MARKER_CHECK(_name))
#define MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(_name,_character) if (MON_PARCER_CURRENT_CHARACTER_EQUAL_CHECK(_name,_character))
// -----------------------------------------------  characters check

// -----------------------------------------------  keywords check
#define MON_PARCER_KEYWORD_CHECK(_name,_kw) (MON_PARCER_BUFFER(_name).compare(_kw) == 0)
#define MON_PARCER_IS_KEYWORD(_name,_kw) if(MON_PARCER_KEYWORD_CHECK(_name,_kw))
// -----------------------------------------------  keywords check

// -----------------------------------------------  characters
#define MON_PARCER_CASES_ALPHA       case 'a': case 'A': case 'b': case 'B': case 'c': case 'C': case 'd': case 'D': case 'e': case 'E': \
                                     case 'f': case 'F': case 'g': case 'G': case 'h': case 'H': case 'i': case 'I': case 'j': case 'J': \
                                     case 'k': case 'K': case 'l': case 'L': case 'm': case 'M': case 'n': case 'N': case 'o': case 'O': \
                                     case 'p': case 'P': case 'q': case 'Q': case 'r': case 'R': case 's': case 'S': case 't': case 'T': \
                                     case 'u': case 'U': case 'v': case 'V': case 'w': case 'W': case 'x': case 'X': case 'y': case 'Y': \
                                     case 'z': case 'Z': case '_'
#define MON_PARCER_CASES_NUMERIC_DOT case '.': case ','
#define MON_PARCER_CASES_NUMERIC     case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9'
#define MON_PARCER_CASES_WHITE       case ' ': case '\t':case '\r':case '\n':case '\v':case '\f'
#define MON_PARCER_CASES_QUOTATION   case '"': case '\'':case '`'
#define MON_PARCER_CASES_MARKERS     case '{': case '}': case '=': case ';': case ':': case '.': case '#'
// -----------------------------------------------  characters

#endif // PARCERHELPER_H
