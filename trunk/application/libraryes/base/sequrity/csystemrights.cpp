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
  return setUser(user) && setGroup(group);
}

std::string CSystemRights::getUName(const uid_t &uid)
{
  std::string userName;
  MON_GET_GID_UID_TEMPLATE(getUName,passwd,getpwuid_r,_SC_GETPW_R_SIZE_MAX,uid,userName,pw_name);
  MON_LOG_DBG("Name for UID " << uid << " is " << userName);
  return userName;
}

std::string CSystemRights::getGName(const gid_t &gid)
{
  std::string groupName;
  MON_GET_GID_UID_TEMPLATE(getGName,group,getgrgid_r,_SC_GETGR_R_SIZE_MAX,gid,groupName,gr_name);
  MON_LOG_DBG("Name for GID " << gid << " is " << groupName);
  return groupName;
}

uid_t CSystemRights::getUID(const std::string &name)
{
  uid_t uid;
  MON_LOG_DBG_CHECKPOINT;
  MON_GET_GID_UID_TEMPLATE(getUID,passwd,getpwnam_r,_SC_GETPW_R_SIZE_MAX,name.c_str(),uid,pw_uid);
  MON_LOG_DBG_CHECKPOINT;
  MON_LOG_DBG("UID for " << name << " is " << uid);
  return uid;
}

gid_t CSystemRights::getGID(const std::string &name)
{
  gid_t gid;
  MON_GET_GID_UID_TEMPLATE(getGID,group,getgrnam_r,_SC_GETGR_R_SIZE_MAX,name.c_str(),gid,gr_gid);
  MON_LOG_DBG("GID for " << name << " is " << gid);
  return gid;
}

bool CSystemRights::setUser (const std::string &name)
{
  MON_LOG_DBG("Try change user name to " << name);
  return(name.compare(currentUserName()) == 0) || setUID(getUID(name));
}

bool CSystemRights::setGroup(const std::string &name)
{
  MON_LOG_DBG("Try change group name to " << name);
  return (name.compare(currentGroupName()) == 0) || setGID(getGID(name));
}

bool CSystemRights::setUID(const uid_t &uid)
{
  MON_LOG_DBG("Try change user id to " << uid);
  if(seteuid(uid) != 0)
  {
    MON_PRINT_ERRNO("Can not set effective user to " << getUName(uid) << " [" << uid << "]");
    MON_ABORT;
    return false;
  }
  MON_LOG_NFO("Effective user changed to " << getUName(uid) << " [" << uid << "]");
  return true;
}

bool CSystemRights::setGID(const gid_t &gid)
{
  MON_LOG_DBG("Try change group id to " << gid);
  if(setegid(gid) != 0)
  {
    MON_PRINT_ERRNO("Can not set effective group to " << getGName(gid) << " [" << gid << "]");
    MON_ABORT;
    return false;
  }
  MON_LOG_NFO("Effective group changed to " << getGName(gid) << " [" << gid << "]");
  return true;
}

bool CSystemRights::resetUser()
{
  return (m_startupUID == currentUID()) || setUID(m_startupUID);
}

bool CSystemRights::resetGroup()
{
  return (m_startupGID == currentGID()) || setGID(m_startupGID);
}

bool CSystemRights::resetUserGroup()
{
  return resetUser() && resetGroup();
}



}
}
}
