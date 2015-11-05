#include <stdio.h>
#include "../klib.h"

int main(int argc, char *argv[])
{
  if(argc>2)
    {
      int var= deci(argv[1], strl(argv[1]));
      char minterm[argc-2][var];
      for(int x=2; x < argc; x++)
	{
	  int num= deci(argv[x], strl(argv[x]));
	  for(int v= var-1; v >= 0; v--)
	    {
	      minterm[x-2][v]= (char) nascii(num%2);
	      num/=2;
	    }
	  for(int y=0; y < var; y++)
	    printf("%c",minterm[x-2][y]);
	  puts("");
	}
      puts("-----------------");
    }
  return qualcosa(argc-2, "[numero_variabili] [mintermini_in_decimale]", argv[0]);
}
