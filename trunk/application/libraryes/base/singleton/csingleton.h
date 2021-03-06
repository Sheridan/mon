/* %Id% */
#ifndef LIB_SINGLETON_H
#define LIB_SINGLETON_H
#include <assert.h>
#include "libraryes/config/config.h"
#include "libraryes/logger/logger.h"
#include "libraryes/base/singleton/csingletonmember.h"

#define MON_ST_ATOMIC_VNAME(_name) m_##_name
#define MON_ST_ATOMIC(_interface,_name) \
  private: _interface * MON_ST_ATOMIC_VNAME(_name); \
  public : _interface * _name() { assert(MON_ST_ATOMIC_VNAME(_name) != nullptr); return MON_ST_ATOMIC_VNAME(_name); };


namespace mon
{
namespace lib
{
namespace base
{

//! Реализация синглтона приложений
class CSingleton
{
    MON_ST_ATOMIC(mon::lib::config::CConfig, config)
    MON_ST_ATOMIC(mon::lib::logger::CLogger, logger)
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
