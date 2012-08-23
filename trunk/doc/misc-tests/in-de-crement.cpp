#include <iostream>
#include <limits>

#define crement(_type) \
  i = 10; \
  std::cout << #_type " = " << _type; \
  i = 10; \
  std::cout << "; foo("  #_type ") = " << foo(_type)  << "; i=" << i << std::endl;

int foo(int val) { return val; }

int main(void)
{
  int i;
  crement(i++);
  crement(++i);
  crement(i--);
  crement(--i);
//  crement(++i++);
// crement(++i--);
//  crement(--i--);
//  crement(--i++);
  return 0 ;
}
