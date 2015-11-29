void ordinamint(char*, unsigned int, unsigned int); // ordina le stringhe in base al primo char
void impli(char*, char*, unsigned int*, unsigned int*, unsigned int);
void compose(char*, char*, char*); // compone i primi due array nel terzo
unsigned int compare(char*, char*); // rende il numero di char uguali o indifferenti
void over(char*, char*, unsigned int); // sovrascrive un dato numero di elementi
int essential(long*, unsigned int*, char*, unsigned int*, char*, unsigned int, char*, unsigned int*);

#define ABC(N) for(char lettera='A';lettera-64 <= N && lettera <= 'Z'; lettera++) printf("%c", lettera)
