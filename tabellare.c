#include <stdio.h>
#include "../klib.h"

void abc(unsigned int);

int main(int argc, char *argv[])
{
  if(argc>2)
    {
      int var= unint(argv[1]);
      char minterm[argc-2][var];

      abc(var);

      for(int x=2; x < argc; x++)
	{
	  int num= unint(argv[x]);
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

inline void abc(unsigned int n)
{
  for(char lettera= 'A'; lettera-64 <= n; lettera++)
    printf("%c", lettera);
  puts("");
}
