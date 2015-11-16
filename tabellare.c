#include <stdio.h>
#include "../klib.h"

int main(int argc, char *argv[])
{
  VET("[numero_variabili] [mintermini_in_decimale]");

  int var= unint(argv[1]); // numero variabili
  int mint= argc-2; // numero mintermini
  char minterm[mint][var+2]; // array bidimensionale: ogni riga è un minterm
  // [numero di 1 nelle variabili] [variabili] ['\0']

  ABC(var);

  for(int x=0; x < mint; x++) // per ogni minterm
    {
      int num= unint(argv[x+2]); // valore decimale
	  
      for(int v= var; v > 0; v--) // converte in binario
	{
	  minterm[x][v]= (char) nascii(num%2);
	  num/=2;
	}
      minterm[x][0]= nascii(match(minterm[x]+1,'1')); // conta gli '1' nel minterm
      minterm[x][var+1]= '\0';
    }

  for(int x=0; x < mint; x++) // per ogni minterm
    {
      printf("%s", &minterm[x][1]);
      printf(" %c\n", minterm[x][0]); // stampa il numero di '1' 
    }
  puts("-----------------");

  return 0;
}
