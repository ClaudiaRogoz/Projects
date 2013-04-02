#include<stdlib.h>
#include <stdio.h>
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



int OrdNP(const void * a,const void * b)
{
    int r=strcmp(((TStud*)a)->nume,((TStud*)b)->nume);
    if(r)
    return r;
    return strcmp(((TStud*)a)->prenume,((TStud*)b)->prenume);
}

    
    
    
    
AGrupa AlocGrupa(int nstud, int nmat)
{      AGrupa ag;
       int i, *p; /* indice student, adresa vector note */
/* aloca spatiu pentru o grupa de nstud studenti, astfel:
   - spatiu pentru TGrupa
   - spatiu pentru vector studenti, initializat cu 0
   - spatiu pentru notele tuturor studentilor (vector initializat cu 0)
*/
       ag = (TGrupa*)malloc(sizeof(TGrupa));
       if(!ag) return NULL;
       ag->std = (TStud*)calloc(nstud, sizeof(TStud));
       if(!ag->std) {free(ag); return NULL;}
       ag->anote = (int*)calloc(nstud * nmat, sizeof(int));
       if (!ag->anote)
       { free(ag->std); free(ag);
         return NULL;
       }
       ag->nrnote = nmat; ag->nrstud = nstud;
/* au reusit toate alocarile; pentru fiecare student  
   memoreaza in campul note adresa zonei destinate notelor sale
*/
       for(i = 0, p = ag->anote; i < nstud; i++, p += nmat)
         ag->std[i].note = p;
       return ag;
}

void ElibGrupa(AGrupa* aag)
{ int i;
  for(i = 0; i < (*aag)->nrstud; i++)
     { free((*aag)->std[i].nume);
       free((*aag)->std[i].prenume);
       free((*aag)->std[i].cnp);
     }
  free((*aag)->anote);
  free((*aag)->std);
  free(*aag);
  *aag = NULL;
}

int CopieDateStud(TStud *s, char nume[], char prenume[], char cnp[])
/* copiaza datele studentului in zone alocate dinamic */
{ s->nume = strdup(nume);
  if (!s->nume) return 0;
  s->prenume = strdup(prenume);
  if (!s->prenume) { free(s->nume); s->nume = NULL; return 0; }
  s->cnp = strdup(cnp);
  if (!s->cnp) 
  { free(s->nume);  s->nume = NULL;
    free(s->prenume); s->prenume = NULL; return 0; }
  return 1;
}

int CitStud(FILE* fs, TGrupa *ag)
/* citeste din fisierul sursa fs, presupus corect,
   nume, prenume si cnp studenti, alocand spatiu corespunzator */
{ int i = 0, *p, *s; /* nr.studenti cititi, adrese note */
  char nume[21], prenume[21], cnp[14];
  while (i < ag->nrstud && fscanf(fs, "%s%s%s", nume, prenume, cnp) == 3)
  { if(!CopieDateStud(ag->std+i, nume, prenume, cnp)) break;
    /* ignora tot ce urmeaza pana la '\n' inclusiv */
    while(fgetc(fs) != '\n');
    i++;
  }
  return i;
}

void TabelStud(TGrupa *ag)
/* afiseaza, pentru fiecare student, nume, prenume, cnp si note */
{ TStud *as, *xs; /* adresa student, limita sup.as */
  int *p, *s;     /* adresa nota, limita sup.p */
  xs = ag->std + ag->nrstud;
  for (as = ag->std; as < xs; as++)
  { printf("%2i. %s %-*s %s|", as - ag->std + 1, 
           as->nume, 41 - strlen(as->nume), as->prenume, as->cnp);
    for (p = as->note, s = p + ag->nrnote; p < s; p++)
      printf("%3i", *p);
    printf("\n");
  }
}
int main()
{
   AGrupa g;
  FILE *f;
  char numefis[21], *nf = numefis;

  /* deschidere fisier */
  fflush(stdin);
  printf("\nNume fisier note: ", numefis); 
  gets(numefis);
  f = fopen(nf, "rt");
  if (!f)
  { printf("Eroare deschidere fisier %s\n", nf);
    return -1;
  }

  /* in fisier, presupus corect, se gasesc nr.de materii (note)
     si informatiile despre studenti: nume, prenume, note */
  fscanf(f, "%i", g->nrnote);
    
  g->nrstud= CitStud(f, g);
  TabelStud(g);
AlocGrupa(g->nrstud,g->nrnote);
 g->nrstud = CitStud(f, g);
 fclose(f);
 
 TabelStud(g);
 
 qsort(g->std,g->nrstud,sizeof(TStud),OrdNP);
 TabelStud(g);
return 0;
getch();
}
 
