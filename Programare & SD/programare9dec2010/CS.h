/*-- CS.h -- tip Colectie Siruri --*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct colectie_siruri
{ char **c;
  size_t nc, na, ne; /* nr.curent, alocat, extindere */
} TCS, * ACS;

ACS AlocCS (size_t d, size_t e);
     /* aloca descriptor colectie si spatiu pentru d adrese de siruri */
void DistrugeCS(ACS *x);
     /* elibereaza intregul spatiu ocupat de o colectie */
int AdaugaCS(ACS x, char *s);
     /* adauga copia sirului s, daca este posibil; intoarce 1 sau 0 */
int AdaugaCS_E(ACS x, char *s);
     /* adauga copia sirului s, cu eventual extindere, daca este posibil */
int ExtindeCS(ACS x);
     /* extinde colectia x cu spatiu pentru x->ne siruri, daca este posibil */
size_t CitireCS(ACS a, FILE *f, int (*Ad)(ACS, char*));
     /* citeste din fisierul f, oprindu-se la epuizarea spatiului sau la sfarsitul fisierului. 
        Pentru adaugarea sirului in colectie apeleaza functia data ca parametru (Ad).
        Intoarce numarul de valori citite (>= 0) -*/
void AfiCS(ACS a);
     /* afiseaza sirurile din colectie */
size_t PrelCondCS(ACS x, int (*Prel)(char *s,...),
                  int (*test)(char *s,...), int cod);
     /* aplica functia Prel sirurilor din colectie
	pentru care functia test intoarce cod */

/*-----*/
