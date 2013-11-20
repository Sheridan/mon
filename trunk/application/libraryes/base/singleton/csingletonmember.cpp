/* %Id% */
#include "libraryes/base/singleton/csingletonmember.h"

namespace mon
{
namespace lib
{
namespace base
{

CSingletonMember::CSingletonMember(const TSingletonMemberID &memberID)
  : m_id(memberID)
{}

CSingletonMember::~CSingletonMember()
{}

const TSingletonMemberID CSingletonMember::id() const
{
  return m_id;
}

}
}
}
