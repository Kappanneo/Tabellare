#include <stdio.h>
#include <stdlib.h>
#include "../klib.h"

void abc(unsigned int); // stampa le prime n lettere dell'alfabeto
void charbin(long, char*, unsigned int); //converte un numero a binario in n char
void ordinamint(char*, unsigned int, unsigned int); // ordina le stringhe in base al primo char
unsigned int impli(char* in, char* out, unsigned int mint, unsigned int var); // it's compli
void compose(char*, char*, char*); // compone i primi due array nel terzo

int main(int argc, char *argv[])
{
  VET("[numero variabili] [mintermini in decimale]");

  const unsigned int var= unint(argv[1]); // numero variabili
  const unsigned int mint= argc-2; // numero mintermini
  char (*minterm)[var+2]= malloc(mint*(var+2)*sizeof(char)); //puntatore ad array
  // ogni riga: [numero di 1 nel minterm] [minterm] ['\0']
  unsigned int implicanti= 0;
  char (*impl)[var+2]= malloc(1024); 

  abc(var);

  for(int x= 0; x < argc-2; x++)
    {
      charbin( unint(argv[2+x]), &(minterm[x])[0], var);
      minterm[x][0]= nascii( match( &(minterm[x])[1],'1') ); // conta gli '1' nel minterm
      minterm[x][var+1]='\0';
    }
  
  ordinamint(&(*minterm)[0], mint, var+2);

  implicanti += impli( &(*minterm)[0], &(*impl)[0], mint, var+2 );

  for(int x= 0; x < argc-2; x++)
      printf("%s %c\n", &(minterm[x])[1], minterm[x][0]);

  puts("");

  for(int x= 0; x < implicanti; x++)
    printf("%s\n", impl[x]);

  free(&(*minterm)[0]);
  free(&(*impl)[0]);
  return 0;
}

void abc(unsigned int n)
{
  for(char lettera='A';lettera-64 <= n; lettera++)
    printf("%c", lettera);
  puts("");
}

void charbin(long num, char* str, unsigned int len)
{
  for(int v= len; v > 0; v--)
    {
      str[v]= (char) nascii(num%2);
      num/=2;
    }
}

void ordinamint(char* minterm, unsigned int mint, unsigned int var)
{
  for(int z= mint; z > 0; z--)
    for(int x= 1; x < z; x++)
      if(minterm[(x-1)*var] > minterm[x*var])
	scambia( &minterm[(x-1)*var], &minterm[x*var]);
}

unsigned int impli(char* in, char* out, unsigned int mint, unsigned int var)
{
  int ret= 0; //numero di minterm nuovi (aggiung controllo doppioni)
  char m= '0'; // valore corrente di match
  int x= 0;
  while(in[x*var]==m) //da rivedere da qui in poi
    {
      for(int v=1; v < mint-x; v++)
	if(in[v*var]==m+1)
	  if(compare( &in[x*var], &in[v*var] )== var-2)
	    {
	      compose( &in[x*var], &in[v*var], out);
	      ret++;
	    }
      ++x;
    }
}

void compose(char* uno, char* due, char* out)
{
  for(int x=0; x <= strl(uno); x++)
    if(uno[x]==due[x])
      out[x]=uno[x];
    else
      out[x]='-';
}
