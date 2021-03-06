#include <iostream>
#include <limits>

#define show_limit(_type) std::cout << #_type " -> " <<  std::endl <<\
                          "    size: " << sizeof(_type) << std::endl <<\
                          "    min : " << std::numeric_limits<_type>::min() << std::endl <<\
                          "    max : " << std::numeric_limits<_type>::max() << std::endl <<\
                          std::endl;


int main(void)
{
  show_limit(bool);
  show_limit(char);
  show_limit(unsigned char);
  show_limit(short);
  show_limit(unsigned short);
  show_limit(int);
  show_limit(unsigned int);
  show_limit(long int);
  show_limit(unsigned long int);
  show_limit(float);
  show_limit(double);
  return 0 ;
}
