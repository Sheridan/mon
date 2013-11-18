#ifndef SYSTEMRIGHTS_H
#define SYSTEMRIGHTS_H
#include <string>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

namespace mon
{
namespace lib
{
namespace base
{

class CSystemRights
{
  public:
    CSystemRights();
    ~CSystemRights();
    static bool setUser (const std::string &name);
    static bool setGroup(const std::string &name);
    bool resetUser();
    bool resetGroup();
    static uid_t currentUID();
    static gid_t currentGID();
    static std::string currentUserName();
    static std::string currentGroupName();
  private:
    uid_t m_currentUID;
    gid_t m_currentGID;
    static std::string getUName(const uid_t &id);
    static std::string getGName(const gid_t &id);
    static uid_t getUID(const std::string &name);
    static gid_t getGID(const std::string &name);
};





}
}
}
#endif // SYSTEMRIGHTS_H
