#include "cparcerstring.h"
namespace mon
{
namespace lib
{
namespace base
{

CParcerString::CParcerString(const std::string &i_text) : CParcer(), m_text(i_text)
{
  m_textLength = m_text.length();
  m_textIndex  = 0;
}

CParcerString::~CParcerString()
{}

SExtractedCharacter CParcerString::goOneCharacterForward()
{
  if(m_textIndex+1 == m_textLength)
  {
    return SExtractedCharacter();
  }
  return SExtractedCharacter(m_text[m_textIndex++]);
}

SExtractedCharacter CParcerString::goOneCharacterBack()
{
  if(m_textIndex-1 < 0)
  {
    return SExtractedCharacter();
  }
  return SExtractedCharacter(m_text[m_textIndex--]);
}

}
}
}
