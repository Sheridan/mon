/* %Id% */
#include "defines/signals-helper.h"
#include "libraryes/base/singleton/csingleton.h"
#include "libraryes/config/cconfig.h"
#include "libraryes/logger/clogger.h"

namespace mon
{
namespace lib
{
namespace base
{

CSingleton * sm_instance = nullptr;

// --------------------------------------------------------------------------------------------------------------------------------------
CSingleton::CSingleton()
{
  sm_instance = this;
  MON_ST_ATOMIC_VNAME(logger) = new mon::lib::logger::CLogger();
  MON_ST_ATOMIC_VNAME(config) = new mon::lib::config::CConfig();
}
// --------------------------------------------------------------------------------------------------------------------------------------
CSingleton::~CSingleton()
{
  for(auto &member : m_members)
  {
    delete member.second;
  }
  m_members.clear();
  delete MON_ST_ATOMIC_VNAME(config);
  delete MON_ST_ATOMIC_VNAME(logger);
}
// --------------------------------------------------------------------------------------------------------------------------------------
CSingleton *CSingleton::instance()
{
  if(sm_instance) return sm_instance;
  return new CSingleton();
}
// --------------------------------------------------------------------------------------------------------------------------------------
void CSingleton::destroy()
{
  delete sm_instance;
  sm_instance = nullptr;
}

void CSingleton::appendMember(CSingletonMember *member)
{
  if(m_members.count(member->id()))
  {
    logger()->log(mon::lib::logger::CLogMessage(mon::lib::logger::pError)
                  << "Append singleton member with id=" << member->id() << "failed. Currently this id is exists. Aborting...");
    MON_ABORT;
  }
  m_members[member->id()] = member;
}

CSingletonMember * CSingleton::member(const TSingletonMemberID &id)
{
  if(m_members.count(id)) { return m_members[id]; }
  logger()->log(mon::lib::logger::CLogMessage(mon::lib::logger::pError)
                << "Access to singleton member with id=" << id << " failed. Member not exists. Aborting...");
  MON_ABORT;
  return nullptr;
}

}
}
}
