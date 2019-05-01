#include <stdio.h>
#include <stdlib.h>
#include "./klib/klib.h"
#include "tab.h"

int main(int argc, char *argv[])
{
  VET("[numero variabili] [mintermini in decimale]");

  for(int x= 2; x < argc; x++) //controllo i valori inseriti
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
  unsigned int passaggi= 1;
  unsigned int countdown= 2;
  unsigned int implicanti= 0; // numero implicanti primi
  unsigned int essenziali= 0; // numero implicati primi essenziali
  unsigned int mintermini; // numero mintermini

  while(countdown)
    {
      mintermini= argc-2;
      switch(countdown)
        {
        case 2:
          for(int x= 0; x < mintermini; x++)//ogni riga: [numero di 1 nel minterm] [minterm] ['\0']
            {
              charbin( unint(argv[x+2]), &a[x*(var+2)+1], var);
              a[x*(var+2)]= nascii( match( &a[x*(var+2)+1],'1') ); // conta gli '1' nel mint
              a[(x+1)*(var+2)]='\0';
            }
          ordinamint( a, mintermini, var+2); //ordina i minterm in base al numero di 1
          while(mintermini) // finchè restano dei minterm non coperti da implicanti primi
            {
              if(passaggi==1)
                printf("%d. Ordinamento:\n", passaggi);
              else
                puts("-implicanti-");
              ABC(var);
              puts("");
              for(int x= 0; x < mintermini; x++) 
                printf("%s %c\n", &a[x*(var+2)+1], a[x*(var+2)]);
              puts("");
              passaggi++;
              impli( a, b, &mintermini, &implicanti, var+2); // magia nera
              printf("%d. Riduzione:\n", passaggi);
              if(implicanti)
                {
                  puts("-implicanti primi-");
                  ABC(var);
                  puts("");
                  for(int x= 0; x < implicanti; x++)
                    printf("%s\n", &b[x*(var+1)]);
                  puts("");
                }
            }
          break;
        case 1:
          {
            long min[mintermini]; //array di valori decimali
            int next= 1; // imposta la prima riduzione da fare

            for(int x= 0; x < mintermini; x++) //salvo i minterm n decimale
              min[x]= unint(argv[x+2]);

            while(mintermini) // finchè non viene ridotta completamente
              {
                passaggi++;
                char tab[implicanti][mintermini]; // array bidimensionale per la tabella

                for(int x= 0; x < mintermini; x++) // converto i minterm in binario
                  {
                    charbin(min[x], &a[x*(var+1)], var);
                    a[x*(var+1)+var]='\0';
                  }
                for(int y= 0; y < implicanti; y++) // imposto la tabella
                  for(int x= 0; x < mintermini; x++)
                    tab[y][x]= compare( &a[x*(var+1)], &b[y*(var+1)] )== var? 'x': ' ';
                
                if(mintermini) // stampo la tabella
                  {
                    puts("-tabella di copertura-");
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
                  }
                
                switch(next) //seleziona il tipo di riduzione
                  {
                  case 1:
                    if(essential(min, &mintermini, b, &implicanti, *tab, var+1, c, &essenziali)) //altra magia
                      {
                        printf("%d. Implicanti primi essenziali:\n", passaggi);
                        ABC(var);
                        puts("");
                        for(int x= 0; x < essenziali; x++)
                          printf("%s\n", &c[x*(var+1)]);
                        puts("");
                        next= 2;
                        break;
                      }
                  case 2:
                    if(domination_row(mintermini, b, &implicanti, *tab, var+1)) // sempre magia
                      {
                        printf("%d. Applicazione dominanza per righe:\n", passaggi);
                        next= 1;
                        break;
                      }
                  case 3:
                    if(domination_col(min, &mintermini, implicanti, *tab)) // magia molto importante
                      {
                        printf("%d. Applicazione dominanza per colonne:\n", passaggi);
                        next= 1;
                        break;
                      }
                  default:
                    printf("%d. Selezione di una delle espressioni minime:\n", passaggi);
                    implicanti--;
                    printf("-implicante rimosso arbitrariamente-\n%s\n\n", &b[implicanti*(var+1)]);
                    next= 1;
                  }
              }
          }
        }
      countdown--;
    }

  printf("%d. Espressione minima:\n", passaggi);
  for(int x= 0; x < essenziali; x++)
    {
      for(int y= 0; y < var; y++)
        {
          if(c[x*(var+1)+y]!='-')
            printf("%c", c[x*(var+1)+y]=='1'? 'A'+y : 'a'+y);
        }
      if(x<essenziali-1)
        printf(" + ");
    }
  puts("\n");

  return 0;
}
