#ifndef LIB_SINGLETON_H
#define LIB_SINGLETON_H
#include "config.h"
#include "logger.h"
#include "csingletonmember.h"
#include <assert.h>

#define MON_ST_ATOMIC_VNAME(_name) m_##_name
#define MON_ST_ATOMIC(_interface,_name) \
  private: _interface * MON_ST_ATOMIC_VNAME(_name); \
  public : _interface * _name() { assert(MON_ST_ATOMIC_VNAME(_name) != NULL); return MON_ST_ATOMIC_VNAME(_name); };


namespace mon
{
namespace lib
{
namespace base
{

class CSingleton
{
  MON_ST_ATOMIC(mon::lib::config::CConfig, config);
  MON_ST_ATOMIC(mon::lib::logger::CLogger, logger);
private:
  CSingleton();
  ~CSingleton();

  TSingletonMembers m_members;

public:

  void appendMember(CSingletonMember *member);
  CSingletonMember *member(const TSingletonMemberID &id);
  static CSingleton *instance();
  static void destroy();
};

}
}
}

#endif // LIB_SINGLETON_H
