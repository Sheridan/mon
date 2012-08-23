#include "cparcer.h"
#include "st.h"
#include "signals-helper.h"
#include <ctype.h>
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
}

CParcer::~CParcer()
{}

SExtractedCharacter CParcer::readCharacter()
{
  SExtractedCharacter t_character = goOneCharacterForward();
  if (t_character.valid)
  {
    switch(t_character.character)
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

SExtractedCharacter CParcer::stepBack()
{
  SExtractedCharacter t_character = goOneCharacterBack();
  if(t_character.valid)
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

void CParcer::parcerError(const std::string &object, const std::string& message)
{
  MON_LOG_ERR("Can not parce "<< object <<", line " << m_linesCount+1 << ", symbol " << m_currentLineCharactersCount-1 << ": " << message);
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
  if(!slash) { MON_PARCER_CURRENT_CHARACTER_IS_EQUAL(read_string, stringOpenChar.character) { return MON_PARCER_BUFFER(read_string); } }

std::string CParcer::readString(const SExtractedCharacter &stringOpenChar)
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

bool CParcer::isAlpha(const SExtractedCharacter &character)
{
  if (isalpha(character.character) != EOF) { return true; }
  if (        character.character  == '_') { return true; }
  return false;
}

bool CParcer::isNumeric(const SExtractedCharacter &character)
{
  return isdigit(character.character) != EOF;
}

bool CParcer::isWhiteSpace(const SExtractedCharacter &character)
{
  return isspace(character.character) != EOF;
}

}
}
}
