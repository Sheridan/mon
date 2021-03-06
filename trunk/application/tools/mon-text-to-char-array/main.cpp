/* %Id% */
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include "libraryes/sensordata/data/cdefinition.h"
#include "libraryes/sensordata/parcers/cdefinitionparcer.h"
#include "libraryes/sensordata/parcers/cdefinitiongenerator.h"

#define BREAK_AT 20
namespace mon
{
namespace applications
{
namespace tool
{
namespace text2char
{
std::string parceAndGenerate(const std::string &def)
{
  mon::lib::sensordata::CDefinition *definition = new mon::lib::sensordata::CDefinition();
  mon::lib::sensordata::CDefinitionParcer *parcer = new mon::lib::sensordata::CDefinitionParcer(definition, def);
  parcer->parce();
  mon::lib::sensordata::CDefinitionGenerator *generator = new mon::lib::sensordata::CDefinitionGenerator(definition);
  std::string result = generator->generate();
  delete generator;
  delete parcer;
  delete definition;
  return result;
}

int nsmain(int argc, char *argv[])
{
  if ( argc != 4 )
  {
    printf( "usage: %s <input filename> <output filename> <variable_name>", argv[0] );
    return 1;
  }

  std::ifstream ifs(argv[1]);
  std::ofstream ofs(argv[2]);
  std::string   source = { (std::istreambuf_iterator<char>(ifs) ),
                           (std::istreambuf_iterator<char>()    ) };
  source = parceAndGenerate(source);
  ofs << "const char " << argv[3] << "[] = {\n";
  char buff[5];
  int characters_count = 0;
  int unbreacked_count = 0;
  for ( auto x : source)
  {
    characters_count++;
    unbreacked_count++;
    sprintf(buff, "%#x", static_cast<char>(x));
    ofs << buff << ", ";
    if(unbreacked_count == BREAK_AT)
    {
      unbreacked_count = 0;
      ofs << "\n";
    }
  }
  ofs << "0\n};\n"
      << "const unsigned int " << argv[3] << "_length = " << characters_count+1 << ";\n";
  return 0;
}

}
}
}
}

int main(int argc, char *argv[]) { return mon::applications::tool::text2char::nsmain(argc, argv); }
