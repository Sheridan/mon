#include "defines/st.h"
#include "defines/logger-helper.h"
#include "defines/signals-helper.h"
#include "libraryes/base/sequrity/csystemrights.h"

#define _OPEN_SYS
#include <unistd.h>

#define MON_GET_GID_UID_TEMPLATE(_name,_pwgr_type,_function,_max_size_buf,_id_or_name,_result_var,_struct_member) \
  struct _pwgr_type _name##pwgr; \
  struct _pwgr_type *_name##tmppwgr; \
  char *_name##bufer; \
  size_t _name##bufferSize; \
  int _name##getpwResult; \
  _name##bufferSize = sysconf(_max_size_buf); \
  _name##bufer = static_cast<char *>(malloc(_name##bufferSize)); if (_name##bufer == NULL) { MON_PRINT_ERRNO("Can not get a bit of memory"); MON_ABORT; } \
  _name##getpwResult = _function(_id_or_name, &_name##pwgr, _name##bufer, _name##bufferSize, &_name##tmppwgr); \
  if (_name##tmppwgr == NULL) \
  { \
  if (_name##getpwResult == 0) { MON_LOG_ERR("Requested " #_pwgr_type " (" << _id_or_name << ") not found"); } \
    else { errno = _name##getpwResult; MON_PRINT_ERRNO("Can not get " #_pwgr_type " (" << _id_or_name << ")"); } \
    MON_ABORT; \
  } \
  _result_var = _name##pwgr._struct_member;\
  free(_name##bufer);

namespace mon
{
namespace lib
{
namespace base
{

CSystemRights::CSystemRights()
{
  m_startupUID = currentUID();
  m_startupGID = currentGID();
}

CSystemRights::~CSystemRights()
{}

uid_t CSystemRights::currentUID() { return geteuid(); }
gid_t CSystemRights::currentGID() { return getegid(); }
std::string CSystemRights::currentUserName()  { return getUName(currentUID()); }
std::string CSystemRights::currentGroupName() { return getGName(currentGID()); }

bool CSystemRights::setUserGroup(const std::string &user, const std::string &group)
{
  return setGroup(group) && setUser(user);
}

std::string CSystemRights::getUName(const uid_t &id)
{
  std::string userName;
  MON_GET_GID_UID_TEMPLATE(getUName,passwd,getpwuid_r,_SC_GETPW_R_SIZE_MAX,id,userName,pw_name);
  return userName;
}

std::string CSystemRights::getGName(const gid_t &id)
{
  std::string groupName;
  MON_GET_GID_UID_TEMPLATE(getGName,group,getgrgid_r,_SC_GETGR_R_SIZE_MAX,id,groupName,gr_name);

  return groupName;
}

uid_t CSystemRights::getUID(const std::string &name)
{
  uid_t uid;
  MON_GET_GID_UID_TEMPLATE(getUID,passwd,getpwnam_r,_SC_GETPW_R_SIZE_MAX,name.c_str(),uid,pw_uid);
  return uid;
}

gid_t CSystemRights::getGID(const std::string &name)
{
  gid_t gid;
  MON_GET_GID_UID_TEMPLATE(getGID,group,getgrnam_r,_SC_GETGR_R_SIZE_MAX,name.c_str(),gid,gr_gid);
  return gid;
}

bool CSystemRights::setUser (const std::string &name)
{
  if(name.compare(currentUserName()) != 0)
  {
    MON_LOG_DBG_CHECKPOINT;
    if(seteuid(getUID(name)) != 0)
    {
      MON_LOG_DBG_CHECKPOINT;
      MON_PRINT_ERRNO("Can not set effective user (" << name << ")");
      MON_ABORT;
      return false;
    }
    MON_LOG_NFO("Effective user changed to " << name);
  }
  return true;
}

bool CSystemRights::setGroup(const std::string &name)
{
  if(name.compare(currentGroupName()) != 0)
  {
    if(setegid(getGID(name)) != 0)
    {
      MON_PRINT_ERRNO("Can not set effective group (" << name << ")");
      MON_ABORT;
      return false;
    }
    MON_LOG_NFO("Effective group changed to " << name);
  }
  return true;
}

bool CSystemRights::resetUser()
{
  if(m_startupUID != currentUID())
  {
    if(seteuid(m_startupUID) != 0)
    {
      MON_PRINT_ERRNO("Can not set effective user (" << getUName(m_startupUID) << ")");
      MON_ABORT;
      return false;
    }
    MON_LOG_NFO("Effective user changed to " << getUName(m_startupUID));
  }
  return true;
}

bool CSystemRights::resetGroup()
{
  if(m_startupGID != currentGID())
  {
    if(setegid(m_startupGID) != 0)
    {
      MON_PRINT_ERRNO("Can not set effective group (" << getGName(m_startupGID) << ")");
      MON_ABORT;
      return false;
    }
    MON_LOG_NFO("Effective group changed to " << getUName(m_startupGID));
  }
  return true;
}

bool CSystemRights::resetUserGroup()
{
  return resetUser() && resetGroup();
}



}
}
}
