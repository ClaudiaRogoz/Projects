/*-- tlista.h --- LISTA SIMPLU INLANTUITA cu elemente de tip intreg ---*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifndef _random_
#define _random_
#define random(n) (rand() % (n))
#define randomize() (srand((unsigned)time(NULL)))
#endif

#ifndef _LISTA_SIMPLU_INLANTUITA_
#define _LISTA_SIMPLU_INLANTUITA_

typedef int TEL, *AEL;     /* tipurile Element si Adresa_Element */
typedef struct cellista
{ TEL info;
  struct cellista*urm;
} TCel, *TLista, **ALista; /* tipurile Celula, Lista si Adresa_Lista */

#define VidaL(L) ((L) == NULL)

typedef int (*TFPrelEL)(AEL e,...);  /* functie prelucrare element lista */

/*-- operatii elementare --*/
ALista CautLeg(ALista ,TFPrelEL );
int LungLR(TLista ); // numarul de elemente recursiv
TLista AlocCel(AEL);          /* adresa celulei create sau NULL */
int    InsInc (ALista, AEL);  /* inserare la inceput reusita sau nu (1/0) */
ALista InsSfL (ALista, AEL);  /* adresa legatura la celula inserata sau NULL */
ALista InsSfLR (ALista, AEL);
int    ElimPL (ALista);       /* elimina prima celula din lista (nevida) */
void   DistrL (ALista);       /* elimina toate celulele din lista */
size_t LungL  (ALista);       /* numarul de elemente din lista */
ALista CautaL (ALista aL, TFPrelEL f, int Gasit);
       /* daca exista celula pentru care f(element) intoarce Gasit
           atunci intoarce adresa legaturii catre celula respectiva,
	       altfel intoarce adresa campului legatura (urm) din ultima celula */

/*-- operatii de afisare si creare; incep prin afisarea unui antet --*/

void AfisareL (ALista aL, char *antet, char *format, char *sf);
       /* Afiseaza valorile elementelor din lista, cu formatul specificat,
	      urmate de sirul sf. 
	      Exemplu de apel:  Afisare(&L1, "Prima lista: [", " %i", " ]\n");  */

TLista GenerL (size_t N, int v1, int v2, char *antet);
       /* genereaza lista cu cel mult N elemente, cu valori intre v1 si v2 */

#endif
