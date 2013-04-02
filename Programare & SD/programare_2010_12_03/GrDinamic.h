/*-- GrDinamic.h--*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <conio.h>

#define MAXS 32    /* numar maxim studenti in grupa */

typedef struct
	{ char *nume, *prenume, *cnp;
	  int *note;  /* adresa vector note */
	} TStud;
typedef struct
	{ int nrnote, nrstud;
	  TStud *std; /* adresa vector studenti */
	  int *anote; /* adresa succesiune grupuri note */
	} TGrupa, *AGrupa;

AGrupa AlocGrupa(int nstud, int nmat);
/* aloca spatiu pentru o grupa de nstud studenti, astfel:
   - spatiu pentru TGrupa
   - spatiu pentru vector studenti, initializat cu 0
   - spatiu pentru notele tuturor studentilor (vector initializat cu 0)
   daca au reusit toate alocarile, pentru fiecare student 
   memoreaza in campul note adresa zonei destinate notelor sale
*/

void ElibGrupa(AGrupa* aag);
/* elibereaza intreg spatiul alocat pentru grupa de studenti */

int InfoStud(FILE *fs, TStud *s);
/* citeste din fisierul sursa fs (presupus corect), nume, prenume si cnp 
   pentru studentul de la adresa s, alocand spatiu corespunzator */

int CitStud(FILE* fs, TGrupa *ag);
/* citeste din fisierul sursa fs, presupus corect,
   informatiile despre studentii din grupa de la adresa ag */

void TabelStud(TGrupa *ag);
/* afiseaza, pentru fiecare student, nume, prenume, cnp si note */

/*-- sfarsit fisier L11-Gr.h --*/
