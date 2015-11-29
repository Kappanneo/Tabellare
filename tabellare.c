#include <stdio.h>
#include <stdlib.h>
#include "../klib.h"
#include "tab.h"

int main(int argc, char *argv[])
{
  VET("[numero variabili] [mintermini in decimale]");

  for(int x= 2; x < argc; x++)
    {
      if(unint(argv[x])<0)
        {
          fprintf(stderr, "Errore: inserire valori positivi\n");
          return 1;
        }
      if(unint(argv[x])>=pot(2,unint(argv[1])))
        {
          fprintf(stderr, "Errore: valore %s non valido in %s variabili\n", argv[x], argv[1]);
          return 1;
        }
      for(int y= x+1; y < argc; y++)
        if(unint(argv[y])==unint(argv[x]))
          {
            fprintf(stderr, "Errore: valore %s ripetuto\n", argv[x]);
            return 1;
          }
    }
  
  const unsigned int var= unint(argv[1]); // numero variabili
  char *a= malloc(1024);
  char *b= malloc(1024);
  char *c= malloc(1024);
  unsigned int cicli= 0;
  unsigned int countdown= 2;
  unsigned int implicanti= 0; // numero implicanti primi
  unsigned int essenziali= 0; // numero implicati primi essenziali

  while(countdown)
    {
      unsigned int mintermini= argc-2; // numero mintermini

      switch(countdown)
        {
        case 2:
          for(int x= 0; x < mintermini; x++)//ogni riga: [numero di 1 nel minterm] [minterm] ['\0']
            {
              charbin( unint(argv[x+2]), &a[x*(var+2)+1], var);
              a[x*(var+2)]= nascii( match( &a[x*(var+2)+1],'1') ); // conta gli '1' nel mint
              a[(x+1)*(var+2)]='\0';
            }
          ordinamint( a, mintermini, var+2);
          while(mintermini) // finchè restano dei minterm non coperti da implicanti primi
            {
              if(cicli)
                printf("%d. Riduzione\n", cicli);
              ABC(var); // stampa i minterm
              puts("");
              for(int x= 0; x < mintermini; x++) 
                printf("%s %c\n", &a[x*(var+2)+1], a[x*(var+2)]);
              puts("");
              
              impli( a, b, &mintermini, &implicanti, var+2); // magia nera
              if(implicanti)
                {
                  puts("-implicanti primi-");
                  ABC(var);
                  puts("");
                  for(int x= 0; x < implicanti; x++)
                    printf("%s\n", &b[x*(var+1)]);
                  puts("");
                }
              cicli++;
            }
          break;
        case 1:
          {
            long min[mintermini];
            int red= 1;

            for(int x= 0; x < mintermini; x++)
              min[x]= unint(argv[x+2]);

            while(red) // finchè restano minterm non coperti da implicanti essenziali
              {
                for(int x= 0; x < mintermini; x++)
                  {
                    charbin(min[x], &a[x*(var+1)], var);
                    a[x*(var+1)+var]='\0';
                  }
                char tab[implicanti][mintermini];

                for(int y= 0; y < implicanti; y++)
                  for(int x= 0; x < mintermini; x++)
                    tab[y][x]= compare( &a[x*(var+1)], &b[y*(var+1)] )== var? 'x': ' ';
                printf("%d. Tabella di copertura:\n", cicli);
                ABC(var);
                for(int x= 0; x < mintermini; x++)
                  printf(" %ld", min[x]);
                puts("");
                for(int y= 0; y < implicanti; y++)
                  {
                    printf("%s", &b[y*(var+1)]);
                    for(int x= 0; x < mintermini; x++)
                      {
                        for(int s= min[x]==0? 1: min[x]; s > 0; s/=10)
                          putchar(' ');
                        printf("%c", tab[y][x]);
                      }
                    puts("");
                  }
                puts("");

                red= essential(min, &mintermini, b, &implicanti, *tab, var+1, c, &essenziali);

                if(essenziali)
                  {
                    puts("-implicanti primi essenziali-");
                    ABC(var);
                    puts("");
                    for(int x= 0; x < essenziali; x++)
                      printf("%s\n", &c[x*(var+1)]);
                    puts("");
                  }              
                cicli++;
              }
          }

        }
      countdown--;
    }
  return 0;
}
