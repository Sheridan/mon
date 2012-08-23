#ifndef PARCERHELPER_H
#define PARCERHELPER_H
#include "st.h"
#include "signals-helper.h"
#include "infinity-cycle-helper.h"

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
  #define MON_PARCER_PRINT_CURRENT_CHAR(_name) MON_LOG_DBG("Parcer (loop `" #_name "`) current character: " << MON_PARCER_CURRENT_CHARACTER(_name);
#else
  #define MON_PARCER_PRINT_CURRENT_CHAR(_name)
#endif

#define MON_PARCER_BUFFER_ERROR_PART(_name) " (Buffer contains `" << MON_PARCER_BUFFER(_name) << "`)"
// -----------------------------------------------  debug

// -----------------------------------------------  names
#define MON_PARCER_CURRENT_EXTRACTED_CHARACTER(_name) current_character___##_name
#define MON_PARCER_CURRENT_CHARACTER(_name)           MON_PARCER_CURRENT_EXTRACTED_CHARACTER(_name).character
#define MON_PARCER_CURRENT_CHARACTER_VALID(_name)     MON_PARCER_CURRENT_EXTRACTED_CHARACTER(_name).valid
#define MON_PARCER_BUFFER(_name)                      buffer___##_name
#define MON_PARCER_LOOP_BREAK_LABEL_NAME(_name)       MON_INFINITY_LOOP_END_LABEL_NAME(_name)
#define MON_PARCER_LOOP_BEGIN_LABEL_NAME(_name)       MON_INFINITY_LOOP_BEGIN_LABEL_NAME(_name)
// -----------------------------------------------  names

// -----------------------------------------------  buffer
#define MON_PARCER_BUFFER_APPEND(_name) MON_PARCER_BUFFER(_name) += MON_PARCER_CURRENT_CHARACTER(_name);
#define MON_PARCER_BUFFER_RESET(_name)  MON_PARCER_BUFFER(_name) = "";
// -----------------------------------------------  buffer

// -----------------------------------------------  buffer checks
#define MON_PARCER_CHECK_BUFFER(_name,_no,_err_message)          if( _no MON_PARCER_BUFFER(_name).empty()) { MON_PARCER_ERROR(_err_message << MON_PARCER_BUFFER_ERROR_PART(_name)); }
#define MON_PARCER_ERROR_IF_BUFFER_EMPTY(_name, _err_message)    MON_PARCER_CHECK_BUFFER(_name, ,_err_message)
#define MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(_name, _err_message) MON_PARCER_CHECK_BUFFER(_name,!,_err_message)
// -----------------------------------------------  buffer checks

// -----------------------------------------------  loop control
#define MON_PARCER_LOOP_BREAK(_name)   MON_INFINITY_LOOP_BREAK(_name)
#define MON_PARCER_LOOP_RESTART(_name) MON_INFINITY_LOOP_RESTART(_name)
#define MON_PARCER_LOOP_BEGIN(_name) \
{ \
  MON_PARCER_PRINT_LOOP_STATUS_STARTED(_name); \
  mon::lib::base::SExtractedCharacter MON_PARCER_CURRENT_EXTRACTED_CHARACTER(_name); \
  std::string MON_PARCER_BUFFER(_name) = ""; \
  MON_INFINITY_LOOP_BEGIN(_name) \
  { \
    MON_PARCER_CURRENT_EXTRACTED_CHARACTER(_name) = readCharacter(); \
    MON_PARCER_PRINT_CURRENT_CHAR(_name)
#define MON_PARCER_LOOP_END(_name) \
  } \
  MON_INFINITY_LOOP_END(_name) \
  MON_PARCER_PRINT_LOOP_STATUS_BREAKED(_name); \
  MON_PARCER_PRINT_LOOP_STATUS_STOPPED(_name); \
}
// -----------------------------------------------  loop control

// -----------------------------------------------  characters check
#define MON_PARCER_CURRENT_CHARACTER_IS_ALPHA(_name)            if (isAlpha     (MON_PARCER_CURRENT_EXTRACTED_CHARACTER(_name)))
#define MON_PARCER_CURRENT_CHARACTER_IS_NUMERIC(_name)          if (isNumeric   (MON_PARCER_CURRENT_EXTRACTED_CHARACTER(_name)))
#define MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(_name)       if (isWhiteSpace(MON_PARCER_CURRENT_EXTRACTED_CHARACTER(_name)))
#define MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(_name,_character) if (MON_PARCER_CURRENT_CHARACTER(_name) == _character)
// -----------------------------------------------  characters check
#endif // PARCERHELPER_H
