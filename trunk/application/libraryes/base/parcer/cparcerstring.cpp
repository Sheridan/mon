#include "libraryes/base/parcer/cparcerstring.h"
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

TStdStringCharacter CParcerString::goOneCharacterForward()
{
  if(m_textIndex+1 == m_textLength)
  {
    m_eof = true;
    return 0;
  }
  return m_text[m_textIndex++];
}

TStdStringCharacter CParcerString::goOneCharacterBack()
{
  if(m_textIndex == 0)
  {
    m_error = true;
    return 0;
  }
  return m_text[m_textIndex--];
}

}
}
}
