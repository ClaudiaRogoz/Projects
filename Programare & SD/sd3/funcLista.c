/*-- funcLista.c --*/
#include <conio.h>
#include <ctype.h>
#include "tlista.h"

/*--- operatii de baza pentru lista simplu inlantuita ---*/

TLista AlocCel(AEL e)          /* adresa celulei create sau NULL */
{ TLista aux = (TLista)malloc(sizeof(TCel));  /* (1) incearca alocare */
  if (aux)                            /* aux contine adresa noii celule */
  { aux->info = *e;                   /* (2,3) completeaza noua celula */
    aux->urm = NULL;
  }
  else
  return NULL;
  return aux;             /* rezultatul este adresa noii celule sau NULL */
}

int InsInc(ALista aL, AEL e)    /* inserare la inceput reusita sau nu (1/0) */
{ TLista aux = (TLista)malloc(sizeof(TCel)); /* (1) incearca alocare */
  if (!aux) return 0;                /* alocare imposibila -> esec */
  aux->info = *e;                    /* (2,3) completeaza noua celula */
  aux->urm = *aL;
  *aL = aux;                         /* (4) lista incepe acum cu noua celula */
  return 1;                          /* operatia de inserare a reusit */
}

ALista InsSfL(ALista aL, AEL e)  /* adresa legatura la celula inserata sau NULL */
{ TLista aux;
  aux = AlocCel(e);                     /* (1) creeaza celula noua */
  if (!aux) return aL;                  /* nu exista spatiu => adr.legatura */
  while (*aL != NULL) aL = &(*aL)->urm; /* (2) localizeaza sfarsitul listei */
  *aL = aux;                            /* (3) ataseaza noua celula */
  return aL;                            /* intoarce adresa legatura */
}
ALista InsSfLR(ALista aL, AEL e)
{
       TLista aux;
       aux=AlocCel(e);
       if(!aux) return aL;
       aux=*aL;
       if(aux==NULL)
       {
                    InsInc(&aux,e);
                    *aL=aux;
                    return aL;
       }
       else
       {
           return InsSfLR(&aux->urm,e);
           }
           }
       


int ElimPL(ALista aL)  /* elimina primul din lista (nevida) */
{ TLista aux = *aL;    /* adresa celulei eliminate */
  if (!aux) return 0;  /* lista vida */
  *aL = aux->urm;      /* deconecteaza celula din lista */
  free (aux);          /* elibereaza spatiul ocupat de celula */
  return 1;
}

void DistrL(ALista a)  /* elimina toate celule din lista */
{ TLista aux;
  while (*a != NULL)   /* cat timp mai exista celule */
  { aux = *a;          /* pregateste eliminarea celulei curente */
    *a = aux->urm;     /* avans la celula urmatoare */
    free (aux);        /* elibereaza spatiul ocupat de celula eliminata */
  }                    /* la iesirea din bucla *a == NULL */
}

size_t LungL(ALista aL)
{ size_t lg;
  TLista p = *aL;
  for (lg = 0; p != NULL; p = p->urm) /* parcurge lista, numarand celulele */
    lg++; 
  return lg;
}
void AfisI(TLista x)
{
     if(!x)
     return;
     AfisI(x->urm);
     printf("%4i",x->info);
     
}



// afiseaza prima aparitie pentru o conditie 
TLista Primap(  TLista x,TFPrelEL f)
{      while(x)
       {
               if(f(&x->info,2))
               return x;
               x=x->urm;
               }
               return NULL;
}
ALista CautLeg(ALista l,TFPrelEL f)
{      TLista p=*l;
       if(!p||(f(&p->info,7)==1))
       return l;
       while(p->urm!=NULL)
       {
               
                 if(f(&p->info,7)==1)
                    break;
                    p=p->urm;
                    }
       return &p->urm;
}
int InsNr(ALista l,int n,TEL *e)    // inserare 
{   int i=1;
TLista aux=NULL;
if(! InsInc(&aux,e))// aloca 
return 0;
for(;i<=n;i++)
{
              if(*l==NULL)
              break;
              l=&((*l)->urm);
}
aux->urm=*l;
*l=aux;
return i;

}

int InsF(ALista l,int n,TEL *e)
{
    int i=1;
    TLista aux=NULL;
    if(!InsInc(&aux,e))
    return 0;
    for(;i<n;i++)
    {
                 if(*l==NULL)
                 break;
                 l=&((*l)->urm);
    }
    aux->urm=*l;
    *l=aux;
    return i;
}





int LungLR(TLista a)
{
    if(!a)
    return 0;
    else return 1+LungLR(a->urm);
}

void AfisareL(ALista aL, char *antet, char *format, char *sf)
       /* afiseaza valorile elementelor din lista */
{ TLista aux = *aL;
  printf("%s", antet);                      /* marcheaza inceput lista */
  for (; aux != NULL; aux = aux->urm)       /* pentru fiecare celula */
    printf(format, aux->info);              /* afiseaza informatie */
  printf("%s", sf);                         /* marcheaza sfarsit lista */
}

TLista GenerL (size_t N, int v1, int v2, char *antet)
       /* genereaza lista cu cel mult N elemente, cu valori intre v1 si v2 */
{ TLista r = NULL;
  TEL x;
  printf ("%s", antet);
  randomize();
  for (; N > 0; N--)               /* cat timp mai sunt necesare inserari */
  { x = random(v2-v1+1) + v1;      /* genereaza o noua valoare */
    if (!InsInc (&r, &x)) break;   /* nu mai exista spatiu pentru inserare */
  }
  return r;                        /* intoarce lista rezultat */
}

