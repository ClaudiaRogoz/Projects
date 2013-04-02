/*--- OpL2.c --- 
      operatii lista generica dublu inlantuita, circulara, cu santinela ---*/

#include "TL2.h"

int InsL2 (TL2 p, void* e)  /* inserare dupa celula cu adresa p -> 1/0 */
{ 
    TL2 aux=(TL2)malloc(sizeof(TCel2));

if(!aux)
return 0;
aux->info=e;


aux->pre=p;

aux->urm=p->urm;

p->urm=aux;

aux->urm->pre=aux;
return 1;
}

size_t NrElem (TL2 s)      /* numarul de elemente din lista */
{      TL2 x;
        int nr=0;
        for(x=s->urm;x!=s;x=x->urm)
        nr++;
        return nr;
        
}

/*- functii de eliberare spatiu; parametrul fe - functie care elibereaza 
    spatiul ocupat de un element */

void ResetL2(TL2 s, void (*fe)(void*))
     /* transforma lista in lista vida */
{   
    TL2 x;
    for(x=s;x!=s->pre;)
    {
           fe(x->urm);
           
           } 
           
}

void DistrL2(TL2* as, void (*fe)(void*))
     /* elibereaza tot spatiul ocupat de lista, inclusiv santinela */
{ 
     ResetL2(*as,fe);
     free((*as)->info);
     free(*as);
     printf("eliberata");
}

TL2 InitL2(void* x)
    /* -> lista vida, cu info din santinela specifica aplicatiei */
{ TL2 aux = malloc (sizeof(TCel2));   /* incearca alocare santinela */

  if (aux)                              /* aux contine adresa santinelei */
  { aux->pre = aux->urm = aux;          /* completeaza celula */
    aux->info = x;
  }
  return aux->urm->urm;     /* rezultatul este adresa santinelei sau NULL */
}

void* ExtrL2 (TL2 p)  /* elimina celula de la adresa p -> adresa info */
{ void* r = p->info;             /* memoreaza adresa element */
  if (p == p->urm) return NULL;  /* lista vida -> NULL */
  p->pre->urm = p->urm;          /* deconecteaza din lista */
  p->urm->pre = p->pre;
  free (p);                      /* elibereaza spatiul ocupat de celula */
  return r;                      /* -> adresa element extras din lista */
}


int PreL2(TL2 s, TF1 f)
    /* aplica functia f tuturor elementelor -> numar elemente */
{ int i = 0;
  TL2 p = s->urm;
  for (; p != s; p = p->urm, i++)  /* pentru fiecare element */
    f(p->info);                    /* aplica functia f */
}

