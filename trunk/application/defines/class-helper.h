/* %Id% */
#ifndef CLASSHELPER_H
#define CLASSHELPER_H

#define MON_READONLY_PROPERTY(_type, _name) \
  private: _type m_##_name; \
  public:  _type    _name() { return m_##_name ; }

#define MON_PROPERTY(_type,_name) \
  MON_READONLY_PROPERTY(_type, _name) \
  public: void set##_name(const _type & value) { m_##_name = value; }

#endif // CLASSHELPER_H
