#ifndef CITEMS_H_MODEL
#define CITEMS_H_MODEL
#include <list>
#include <string>
#include "defines/mutex-helper.h"

namespace mon
{
namespace lib
{
namespace model
{

template<typename T>
class CItems
{
    MON_MUTEX_DECLARE(items)
  public:
    typedef std::list<T *> TItems;
    typedef std::list<std::string> TNames;

    CItems()
    {
      MON_MUTEX_INITIALIZE(items)
    }

    virtual ~CItems()
    {
      MON_MUTEX_LOCK(items);
      for(T *i : m_items)
      {
        delete i;
      }
      m_items.clear();
      m_names.clear();
      MON_MUTEX_UNLOCK(items);
      MON_MUTEX_DESTROY(items)
    }

    T *item(const std::string &name)
    {
      T *result;
      MON_MUTEX_LOCK(items);
      for(T *i : m_items)
      {
        if(name.compare(i->name()))
        {
          result = i;
          break;
        }
      }
      MON_MUTEX_UNLOCK(items);
    }

    TNames names()
    {
      return m_names;
    }

  protected:
    void add(T *i)
    {
      MON_MUTEX_LOCK(items);
      m_items.push_back(i);
      m_names.push_back(i->name());
      MON_MUTEX_UNLOCK(items);
    }

  private:
    TItems m_items;
    TNames m_names;
};

}
}
}

#endif // CITEMS_H_MODEL
