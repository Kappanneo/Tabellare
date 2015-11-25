#include <stdio.h>
#include <stdlib.h>
#include "../klib.h"

void abc(unsigned int); // stampa le prime n lettere dell'alfabeto
void ordinamint(char*, unsigned int, unsigned int); // ordina le stringhe in base al primo char
unsigned int impli(char* in, char* out, unsigned int* mint, unsigned int var, unsigned int); //it's compli
void compose(char*, char*, char*); // compone i primi due array nel terzo
unsigned int compare(char*, char*); // rende il numero di char uguali o indifferenti
void over(char*, char*, unsigned int); // sovrescrive un dato numero di elementi sul primo array

int main(int argc, char *argv[])
{
  VET("[numero variabili] [mintermini in decimale]");

  const unsigned int var= unint(argv[1]); // numero variabili
  unsigned int mint= argc-2; // numero mintermini
  char (*minterm)[var+2]= malloc(1024); // puntatore ad array di caratteri,  ogni riga: [numero di 1 nel minterm] [minterm] ['\0'] 
  unsigned int implicanti= 0; // numero implicanti primi
  char (*impl)[var+1]= malloc(1024); // ogni riga: [implicante] ['\0']

  for(int x= 0; x < argc-2; x++) //compone ogni riga
    {
      charbin( unint(argv[2+x]), &(minterm[x])[0], var);
      minterm[x][0]= nascii( match( &(minterm[x])[1],'1') ); // conta gli '1' nel minterm
      minterm[x][var+1]='\0';
    }
  ordinamint(*minterm, mint, var+2); // ordinamento (*minterm => &(*minterm)[0])

  while(mint) // finchè restano dei minterm non coperti da implicanti primi
    {
      abc(var); // stampa i minterm
      for(int x= 0; x < mint; x++) 
	printf("%s %c\n", &(minterm[x])[1], minterm[x][0]);
      puts("");

      implicanti += impli( &(*minterm)[0], &(*impl)[0], &mint, var+2 ,implicanti); // magia nera

      if(implicanti) // stampa gli implicanti primi (se ci sono)
	{      
	  puts("Implicanti primi:");
	  abc(var);
	  for(int x= 0; x < implicanti; x++)
	    printf("%s\n", impl[x]);
	}
      puts("");
    }
  return 0;
}

void abc(unsigned int n)
{
  for(char lettera='A';lettera-64 <= n; lettera++) // 'A' ha valore 65
    printf("%c", lettera);
  puts("");
}

void ordinamint(char* minterm, unsigned int mint, unsigned int var)
{
  for(int z= mint; z > 0; z--)
    for(int x= 1; x < z; x++) // mint! volte
      if(minterm[(x-1)*var] > minterm[x*var]) // minterm[a*colonne_t +b] => minterm[a][b]
	scambia( &minterm[(x-1)*var], &minterm[x*var]);
}

unsigned int impli(char* in, char* out, unsigned int* min, unsigned int var, unsigned int imp)
{
  int ret= 0; // nuovi implicanti primi
  int new= 0; //numero di minterm ridotti
  char m='0'; // valore corrente di match
  int x= 0;
  unsigned int mint= *min;
  char (*temp)[var]= malloc(2048);
  while(x < mint) // per ogni minterm
    {
      while(in[x*var]==m) //se ha valore m
	{
	  for(int v= x+1; v < mint; v++) // lo confronto con ogni minterm
	    if(in[v*var]==m+1) // che abbia valore m+1
	      if( compara( &in[x*var], &in[v*var]) == var-3) // se differiscono di uno oltre al primo
		{
		  compose( &in[x*var+1], &in[v*var+1], &temp[new][1]); // li riduco in temp
		  temp[new][0]= in[x*var]; // il numero di 1 è uguale
		  for(int r= 0; r < new; r++) // per ogni implicante
		    if( compara( &(temp[new])[1], &(temp[r])[1]) == var-2) // se è uguale ad un'altro
		      {
			new--; // quindi verrà sovrascritto
			break;
		      }
		  new++; // passo al prossimo implicante
		}
	  ++x; // registro l'avanzamento sui minterm totali
	}
      ++m; // passo al prossimo gruppo di minterm con valore +1
    }

  for(int x= 0; x < mint; x++) // per ogni minterm
      {
  	int n= 0;
  	for(int t= 0; t < new; t++) // per ogni implicante
	  if( compare( &in[x*var+1], &(temp[t])[1]) == var-2) //se il minterm è coperto
	    ++n;
  	if(!n) // se un minterm non è coperto da nessun impicante
  	  {
  	    copia( &in[x*var+1], &out[(ret+imp)*(var-1)] ); // lo salvo come implicante primo
  	    ret++;
  	  }
      }

  *min= new;
  over(in, temp[0], new*var); // sovrascrivo i minterm con i loro implicanti
  free(*temp); // libero la locazione di temp
  return ret;
}

void compose(char* uno, char* due, char* out)
{
  int x= 0;
  while(x < strl(uno))
    {
      if(uno[x]==due[x])
	out[x]=uno[x];
      else
	out[x]='-'; // sostituisce i caratteri differenti con '-'
      ++x;
    }
  out[x]='\0';
}
  
unsigned int compare(char* uno, char* due)
{
  unsigned int match= 0;
  int x= 0;
  while(x < strl(uno))
    {
      if(uno[x]==due[x]||due[x]=='-')
	match++;
      ++x;
    }
  return match;
}

void over(char* uno, char* due, unsigned int tot)
{
  for(int x= 0; x <= tot; x++)
    uno[x]= due[x];
}
