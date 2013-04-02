/*-- multime.h --*/
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

/*-- declaratii necesare pentru generarea de valori aleatoare --*/
#include <time.h>
#define random(num)   (rand() % (num))
#define randomize()   srand((unsigned)time(NULL))

typedef int(*TFComp)(const void *, const void *);

/*- Operatii asupra multimilor cu elemente de orice tip 
    Parametri folositi:
    a, b - vectori cu na, nb elemente 
    d - dimensiune elemente
    x, nou - element cautat / adaugat
    cmp - functie de comparatie
*/

/*--- operatii asupra multimilor NESORTATE ---*/

int Apartine(void *a, size_t na,  size_t d, void *x, TFComp cmp);
   /* intoarce 1/0 cu semnificatia adevarat/fals*/
     
void* Loc( void *a, size_t na, size_t d, void *x, TFComp cmp);
   /* intoarce adresa elementului cautat sau NULL */
   
int Adauga(void *a, size_t na, size_t d, void *nou, TFComp cmp);
   /* obiectiv: adaugarea unui nou element la sfarsitul vectorului;
      intoarce 1/0/-1 cu semnificatia succes/exista deja/nu exista spatiu */

int Elimina(void *a, size_t na, size_t d, void *x, TFComp cmp);
   /* intoarce 1/0 cu semnificatia eliminat / nu exista */

int Reun1(void *a, size_t na, void *b, size_t nb, size_t d,
          void *r, TFComp cmp);
   /* spatiul pentru reuniune alocat in prealabil, la adresa r;
      intoarce cardinalul reuniunii */

void* Reun2(void *a, size_t na, void *b, size_t nb, size_t d,
            TFComp cmp, int *nr);
   /* spatiu pentru reuniune alocat de functie;
      intoarce adresa vector reuniune sau NULL, daca alocarea esueaza; 
      cardinalul reuniunii (>=0) este memorat la adresa nr */

/*--- operatii asupra multimilor SORTATE ---*/

void* LocO( void *a, size_t na, size_t d, void *x, TFComp cmp);
   /* cautare secventiala, cu oprire la elementul cautat sau la succesor 
      sau la sfarsit; intoarce adresa elementului gasit sau NULL */
int Inserare(void *a, size_t na, size_t d, void *nou, TFComp cmp);
   /* obiectiv: inserarea noului element in vectorul ordonat;
      intoarce 1/0/-1 cu semnificatia succes/exista deja/nu exista spatiu */

int ElimO(void *a, size_t na, size_t d, void *x, TFComp cmp);
   /* intoarce 1/0 cu semnificatia eliminat / nu exista */

void *CautBin(void *a, size_t na, size_t d, TFComp cmp, void *x, int *r);
   /* cautare binara in vector sortat; 
      daca elementul cautat exista intoarce adresa si 1 (la adresa r),
      altfel intoarce adresa primului succesor si 0 */

int Reun1O(void *a, size_t na, void *b, size_t nb, size_t d, 
           void *r, TFComp cmp);
   /* spatiul pentru reuniune alocat in prealabil, la adresa r;
      intoarce cardinalul reuniunii */

void* Reun2O(void *a, size_t na, void *b, size_t nb, size_t d, 
             TFComp cmp, int *nr);
   /* spatiu pentru reuniune alocat de functie;
      intoarce adresa vector reuniune sau NULL, daca alocarea esueaza; 
      cardinalul reuniunii (>=0) este memorat la adresa nr */

/*--- functii auxiliare ---*/

void *DeplDr(void *a, size_t dim, size_t d);
   /* deplaseaza cu d octeti la dreapta un pachet de dim octeti */

void DeplST(void *a, size_t dim, size_t d);
   /* deplaseaza cu d octeti la stanga un pachet de dim octeti */

void copie(void *dest, void *sursa , size_t d);
   /* copiaza la destinatie d octeti de la sursa */

/*-------------*/
