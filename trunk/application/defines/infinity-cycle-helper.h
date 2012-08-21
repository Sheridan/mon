#ifndef INFINITYCYCLEHELPER_H
#define INFINITYCYCLEHELPER_H

#define INFINITY_CYCLE_RESTART(_name) goto label_##_name##_infinity_cycle_begin;
#define INFINITY_CYCLE_BREAK(_name)   goto label_##_name##_infinity_cycle_end;

#define INFINITY_CYCLE_BEGIN(_name) \
  INFINITY_CYCLE_RESTART(_name) \
  label_##_name##_infinity_cycle_begin: ; \
  for(;;) \
    {
#define INFINITY_CYCLE_END(_name) \
    } \
  INFINITY_CYCLE_BREAK(_name) \
  label_##_name##_infinity_cycle_end: ;

#endif // INFINITYCYCLEHELPER_H
