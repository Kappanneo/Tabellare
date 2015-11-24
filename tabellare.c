#include <stdio.h>
#include <stdlib.h>
#include "../klib.h"

void abc(unsigned int); // stampa le prime n lettere dell'alfabeto
void ordinamint(char*, unsigned int, unsigned int); // ordina le stringhe in base al primo char
unsigned int impli(char* in, char* out, unsigned int* mint, unsigned int var); // it's compli
void compose(char*, char*, char*); // compone i primi due array nel terzo
unsigned int compare(char*, char*);
void over(char*, char*, unsigned int);

int main(int argc, char *argv[])
{
  VET("[numero variabili] [mintermini in decimale]");

  const unsigned int var= unint(argv[1]); // numero variabili
  unsigned int mint= argc-2; // numero mintermini
  char (*minterm)[var+2]= malloc(1024); // puntatore ad array di caratteri,  ogni riga: [numero di 1 nel minterm] [minterm] ['\0'] 
  unsigned int implicanti= 0; // numero implicanti primi
  char (*impl)[var+1]= malloc(1024); // ogni riga: [implicante] ['\0']

  //------------------------------------------------------- conversione

  for(int x= 0; x < argc-2; x++)
    {
      charbin( unint(argv[2+x]), &(minterm[x])[0], var);
      minterm[x][0]= nascii( match( &(minterm[x])[1],'1') ); // conta gli '1' nel minterm
      minterm[x][var+1]='\0';
    }

  //------------------------------------------------------- ordinamento
  
  ordinamint(*minterm, mint, var+2); // *minterm => &(*minterm)[0]

  //------------------------------------------------------- stampa

  abc(var);
  for(int x= 0; x < mint; x++)
    printf("%s %c\n", &(minterm[x])[1], minterm[x][0]);

  //------------------------------------------------------- analisi

  implicanti += impli( &(*minterm)[0], &(*impl)[0], &mint, var+2);

  //------------------------------------------------------- fine

  puts("---------------");
  abc(var);
  for(int x= 0; x < mint; x++)
    printf("%s %c\n", &(minterm[x])[1], minterm[x][0]);

  free(*minterm);
  free(*impl);

  return 0;
}

void abc(unsigned int n)
{
  for(char lettera='A';lettera-64 <= n; lettera++)
    printf("%c", lettera);
  puts("");
}

void ordinamint(char* minterm, unsigned int mint, unsigned int var)
{
  for(int z= mint; z > 0; z--)
    for(int x= 1; x < z; x++) // mint! volte
      if(minterm[(x-1)*var] > minterm[x*var])
	scambia( &minterm[(x-1)*var], &minterm[x*var]);
}

unsigned int impli(char* in, char* out, unsigned int* min, unsigned int var)
{
  int ret= 0; //numero di implicanti primi
  char m='0'; // valore corrente di match
  int x= 0;
  unsigned int mint= *min;
  char (*temp)[var]= malloc(2048);
  while(x < mint)
    {
      while(in[x*var]==m)
	{
	  for(int v= x+1; v < mint; v++)
	    if(in[v*var]==m+1)
	      if( compara( &in[x*var], &in[v*var])== var-2)
		{
		  compose( &in[x*var+1], &in[v*var+1], &temp[ret][1]);
		  temp[ret][0]= in[x*var];
		  for(int r= 0; r < ret-1; r++)
		    if( compara( temp[ret], temp[r]) == var)
		      {
			ret--;
			break;
		      }
		  ret++;
		}
	  ++x;
	}
      ++m;
    }
  // verifica implicanti <--------
  over(in, temp[0], ret*var);
  *min= ret;
  free(*temp);
  return ret; //in realtà ret va sostituito tutto con un'altra variabile (ret => impl)
}

void compose(char* uno, char* due, char* out)
{
  int x= 0;
  while(x < strl(uno))
    {
      if(uno[x]==due[x])
	out[x]=uno[x];
      else
	out[x]='-';
      ++x;
    }
  out[x]='\0';
}
  
unsigned int compare(char* uno, char* due)
{
  unsigned int match= 0;
  int x= 0;
  while(++x <= strl(uno))
    if(uno[x]==due[x]||due[x]=='-')
      match++;
  return match;
}

void over(char* uno, char* due, unsigned int tot)
{
  for(int x= 0; x <= tot; x++)
    uno[x]= due[x];
}
