#include "csingleton.h"
#include "cconfig.h"
#include "clogger.h"
#include "signals-helper.h"

namespace mon
{
namespace lib
{
namespace base
{

CSingleton * sm_instance = NULL;

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
  for(TSingletonMembers::iterator it = m_members.begin(); it != m_members.end(); ++it)
  {
    delete it->second;
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
  sm_instance = NULL;
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
  MON_ABORT; return NULL;
}

}
}
}
