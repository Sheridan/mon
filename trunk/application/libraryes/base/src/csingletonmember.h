#ifndef CSINGLETONMEMBER_H
#define CSINGLETONMEMBER_H
#include <map>

namespace mon
{
namespace lib
{
namespace base
{

typedef unsigned short TSingletonMemberID;

class CSingletonMember
{
public:
  CSingletonMember(const TSingletonMemberID &memberID);
  virtual ~CSingletonMember();
  const TSingletonMemberID id() const;
private:
  TSingletonMemberID m_id;
};

typedef std::map<TSingletonMemberID, CSingletonMember *> TSingletonMembers;

}
}
}

#endif // CSINGLETONMEMBER_H
