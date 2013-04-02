/*-- TL2.h -- Lista generica dublu inalntuita, circulara, cu santinela --*/
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#ifndef _random_
  #define _random_
  #define random(n) (rand() % (n))
  #define randomize() (srand((unsigned)time(NULL)))
#endif
#ifndef _LISTA_DUBLU_INLANTUITA_
#define _LISTA_DUBLU_INLANTUITA_
typedef struct 
{
        int x,y;
} TPct,* APct;
typedef int (*TF1)(void*,...);     /* functie prelucrare un element */
typedef int (*TF2)(void*, void*);  /* functie prelucrare doua elemente */

typedef struct cel2
{ struct cel2 *pre, *urm;  /* legaturi spre celulele vecine */
  void* info;              /* adresa element (orice) */
} TCel2, *TL2;

#define VidaL2(s) ((s)->urm == (s))   /* lista vida contine numai santinela */

/*- operatii; param.adrese: s - santinela, p - celula oarecare, x - element -*/

TL2 InitL2(void* x); 
      /* -> lista vida, cu info din santinela specifica aplicatiei */

int InsL2(TL2 p, void* x); /* inserare dupa celula cu adresa p -> 1/0 */

void* ExtrL2(TL2 p);       /* elimina celula de la adresa p -> adresa info */

size_t NrElem(TL2 s);      /* numarul de elemente din lista */

int PreL2(TL2 s, TF1 f);
    /* aplica functia f tuturor elementelor -> numar elemente */

/*- functii de eliberare spatiu; parametrul fe - functie care elibereaza 
    spatiul ocupat de un element */

void ResetL2(TL2 s, void (*fe)(void*));  
     /* transforma lista in lista vida */

void DistrL2(TL2* as, void (*fe)(void*));
     /* elibereaza tot spatiul ocupat de lista, inclusiv santinela */

#endif
