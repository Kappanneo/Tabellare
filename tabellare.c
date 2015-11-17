#include <stdio.h>
#include "../klib.h"

int main(int argc, char *argv[])
{
  VET("[numero variabili] [mintermini in decimale]");

  int var= unint(argv[1]); // numero variabili
  int mint= argc-2; // numero mintermini
  char minterm[mint][var+2]; // array bidimensionale
  // ogni riga: [numero di 1 nel minterm] [minterm] ['\0']

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

  for(int z= mint; z > 0; z--) // ordina i minterm
    for(int x= 1; x < z; x++)
      if(minterm[x-1][0] > minterm [x][0]) // in base al numero di 1
	scambia(minterm[x-1],minterm[x]);

  for(int x=0; x < mint; x++) // per ogni minterm
    {
      printf("%s", &minterm[x][1]); //stampa il minterm
      printf(" %c\n", minterm[x][0]); // stampa il numero di '1' 
    }
  puts("-----------------");

  return 0;
}
