#include "cparcer.h"
#include "st.h"
#include "signals-helper.h"
#include "parcer-helper.h"

namespace mon
{
namespace lib
{
namespace base
{

const char *CParcer::keywordsTrue [CParcer::boolKeywordsCount] = {"on\0" , "true\0" , "yes\0", "1\0"};
const char *CParcer::keywordsFalse[CParcer::boolKeywordsCount] = {"off\0", "false\0", "no\0" , "0\0"};

CParcer::CParcer()
{
  m_linesCount                 = 0;
  m_currentLineCharactersCount = 0;
  m_charactersCount            = 0;
  m_error = false;
  m_eof   = false;
}

CParcer::~CParcer()
{}

TStdStringCharacter CParcer::readCharacter()
{
  TStdStringCharacter t_character = goOneCharacterForward();
  if (!m_error && !m_eof)
  {
    switch(t_character)
    {
      case '\n':
      {
        m_linesCount++;
        m_currentLineCharactersCount = 0;
      }
      default:
      {
        m_charactersCount++;
        m_currentLineCharactersCount++;
      }
    }
  }
  return t_character;
}

TStdStringCharacter CParcer::stepBack()
{
  TStdStringCharacter t_character = goOneCharacterBack();
  if(!m_error && !m_eof)
  {
    m_charactersCount--;
    m_currentLineCharactersCount--;
    if(m_currentLineCharactersCount < 0)
    {
      m_currentLineCharactersCount = 0;
      m_linesCount--;
    }
  }
  return t_character;
}

void CParcer::parcerError(const std::string& message, const TStdStringCharacter &character)
{
  MON_LOG_ERR("Can not parce, line " << m_linesCount+1 << ", symbol " << m_currentLineCharactersCount-1 << " (`" << character << "`): " << message);
  MON_ABORT;
}

void CParcer::skipComment()
{
  MON_PARCER_LOOP_BEGIN(read_comment);
  MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_comment,'\n')
  {
    MON_PARCER_LOOP_BREAK(read_comment);
  }
  MON_PARCER_LOOP_END(read_comment);
}

#define MON_STRING_LOOP_CHECK \
  if(!slash) { MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_string, stringOpenChar) { return MON_PARCER_BUFFER(read_string); } }

std::string CParcer::readString(const TStdStringCharacter &stringOpenChar)
{
  bool slash = false;
  MON_PARCER_LOOP_BEGIN(read_string);
  {
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_string, '\\') { if(slash) { MON_PARCER_BUFFER(read_string) += '\\'; } slash = !slash; MON_PARCER_LOOP_RESTART(read_string); }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_string,  'n') { if(slash) { MON_PARCER_BUFFER(read_string) += '\n';   slash =  false; MON_PARCER_LOOP_RESTART(read_string); } }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_string,  'r') { if(slash) { MON_PARCER_BUFFER(read_string) += '\r';   slash =  false; MON_PARCER_LOOP_RESTART(read_string); } }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_string,  'b') { if(slash) { MON_PARCER_BUFFER(read_string) += '\b';   slash =  false; MON_PARCER_LOOP_RESTART(read_string); } }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_string,  't') { if(slash) { MON_PARCER_BUFFER(read_string) += '\t';   slash =  false; MON_PARCER_LOOP_RESTART(read_string); } }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_string, '\'') { if(slash) { MON_PARCER_BUFFER(read_string) += '\'';   slash =  false; MON_PARCER_LOOP_RESTART(read_string); } MON_STRING_LOOP_CHECK; }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_string,  '"') { if(slash) { MON_PARCER_BUFFER(read_string) +=  '"';   slash =  false; MON_PARCER_LOOP_RESTART(read_string); } MON_STRING_LOOP_CHECK; }
    MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_string,  '`') { if(slash) { MON_PARCER_BUFFER(read_string) +=  '`';   slash =  false; MON_PARCER_LOOP_RESTART(read_string); } MON_STRING_LOOP_CHECK; }
    MON_PARCER_BUFFER_APPEND(read_string)
  }
  MON_PARCER_LOOP_END(read_string);
  return "";
}

TStdStringCharacter CParcer::findString()
{
  MON_PARCER_LOOP_BEGIN(find_string)
  {
    MON_PARCER_CURRENT_CHARACTER_IS_WHITESPACE(find_string)
    {
      MON_PARCER_LOOP_RESTART(find_string);
    }
    MON_PARCER_CURRENT_CHARACTER_IS_QUOTATION(find_string)
    {
      return MON_PARCER_CURRENT_CHARACTER(find_string);
    }
    MON_PARCER_ERROR_IF_BUFFER_NO_EMPTY(find_string, "Misplaced character");
  }
  MON_PARCER_LOOP_END(find_string);
  parcerError("Can not find string", ' ');
  return ' ';
}

bool CParcer::convertBool(const std::string &string)
{
  const char * buffer = string.c_str();
  for(int i = 0; i < boolKeywordsCount; i++)
  {
    if(strcasecmp(keywordsTrue [i], buffer) == 0) { return true ; }
    if(strcasecmp(keywordsFalse[i], buffer) == 0) { return false; }
  }
  parcerError("Unknown bool value: " + string, ' ');
  return false;
}

bool CParcer::isAlpha(const TStdStringCharacter &character)
{
  switch(character) { MON_PARCER_CASES_ALPHA: { return true; } }
  return false;
}

bool CParcer::isNumeric(const TStdStringCharacter &character)
{
  switch(character) { MON_PARCER_CASES_NUMERIC: { return true; } }
  return false;
}

bool CParcer::isNumericDot(const TStdStringCharacter &character)
{
  switch(character) { MON_PARCER_CASES_NUMERIC_DOT: { return true; } }
  return false;
}

bool CParcer::isWhiteSpace(const TStdStringCharacter &character)
{
  switch(character) { MON_PARCER_CASES_WHITE: { return true; } }
  return false;
}

bool CParcer::isQuotation (const TStdStringCharacter &character)
{
  switch(character) { MON_PARCER_CASES_QUOTATION: { return true; } }
  return false;
}

}
}
}
