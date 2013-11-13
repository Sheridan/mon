#ifndef STLHELPER_H
#define STLHELPER_H

// ------------------------------- map ------------------------------
#define MON_STL_MAP_NAME(_name) it##_name
#define MON_STL_MAP_KEY(_name) (MON_STL_MAP_NAME(_name)->first)
#define MON_STL_MAP_VALUE(_name) (MON_STL_MAP_NAME(_name)->second)
#define MON_STL_MAP_FOREACH(_name,_map) \
  for(auto MON_STL_MAP_NAME(_name) = _map.begin(); \
      MON_STL_MAP_NAME(_name) != _map.end(); \
      ++MON_STL_MAP_NAME(_name))
// ------------------------------- map ------------------------------

// ------------------------------- list ------------------------------
#define MON_STL_LIST_NAME(_name) it##_name
#define MON_STL_LIST_VALUE(_name) (*MON_STL_LIST_NAME(_name))
#define MON_STL_LIST_FOREACH(_name,_list) \
  for(auto MON_STL_LIST_NAME(_name) = _list.begin(); \
      MON_STL_LIST_NAME(_name) != _list.end(); \
      MON_STL_LIST_NAME(_name)++)
// ------------------------------- list ------------------------------

// ------------------------------- set ------------------------------
#define MON_STL_SET_NAME(_name) it##_name
#define MON_STL_SET_VALUE(_name) (*MON_STL_SET_NAME(_name))
#define MON_STL_SET_FOREACH(_name,_list) \
  for(auto MON_STL_SET_NAME(_name) = _list.begin(); \
      MON_STL_SET_NAME(_name) != _list.end(); \
      MON_STL_SET_NAME(_name)++)
// ------------------------------- set ------------------------------
#endif // STLHELPER_H
