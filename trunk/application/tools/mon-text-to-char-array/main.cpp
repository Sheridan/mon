/* %Id% */
#include <stdio.h>
#include <stdlib.h>

#define BREAK_AT 20

int main(int argc, char *argv[])
{
  if ( argc != 4 )
  {
    printf( "usage: %s <input filename> <output filename> <variable_name>", argv[0] );
  }
  else
  {
    FILE *i_file = fopen(argv[1], "r");
    FILE *h_file = fopen(argv[2], "w");

    if (i_file == 0 or h_file == 0)
    {
      printf( "Could not open file\n" );
      exit(1);
    }
    else
    {
      fprintf(h_file, "const unsigned char %s[] = {\n", argv[3]);
      int x;
      int characters_count = 0;
      int unbreacked_count = 0;
      while((x = fgetc(i_file)) != EOF)
      {
        characters_count++;
        unbreacked_count++;
        fprintf(h_file, "%#x, ", static_cast<unsigned char>(x));
        if(unbreacked_count == BREAK_AT)
        {
          unbreacked_count = 0;
          fprintf(h_file, "\n");
        }
      }
      fprintf(h_file, "0\n};\n");
      fprintf(h_file, "const unsigned int %s_length = %d;\n", argv[3], characters_count+1);
      fclose(i_file);
      fclose(h_file);
    }
  }
}
