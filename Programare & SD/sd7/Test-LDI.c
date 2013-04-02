#include "TL2.h"
#include<time.h>


void AfisareL(TL2 aL, char *antet, char *format, char *sf)
       /* afiseaza valorile elementelor din lista */
{ TL2 aux;
  printf("%s", antet);                      /* marcheaza inceput lista */
  for (aux=aL->urm; aux != aL; aux = aux->urm)       /* pentru fiecare celula */
    printf("(%4i,%4i)", ((TPct*)(aux->info))->x,((TPct*)(aux->info))->y);              /* afiseaza informatie */
  printf("%s", sf);                         /* marcheaza sfarsit lista */
}

TL2 GenerL (size_t N, int v1, int v2, char *antet)
       /* genereaza lista cu cel mult N elemente, cu valori intre v1 si v2 */
{ TL2 r;
  int x,y;
  int  n=0;
  TPct * p;
  r=InitL2(&n);
  printf ("%s", antet);
  randomize();
  
  for (; N > 0; N--)               /* cat timp mai sunt necesare inserari */
  { p=(APct)malloc(sizeof(TPct));
      p->x = random(v2-v1+1) + v1;      /* genereaza o noua valoare */
    p->y = random(v2-v1+1) + v1; 
  //    printf(" %i %i",p.x,p.y);
    
    if (!InsL2(r,p)) break;   /* nu mai exista spatiu pentru inserare */

  
  }
  return r;                        /* intoarce lista rezultat */
}
void fe (void *x)
{
     TL2 aux=(TL2)x;
     ((TL2)x)->urm->pre=((TL2)x)->pre;
     ((TL2)x)->pre->urm=((TL2)x)->urm;
     free(aux->info);
     free(aux);
     
     
 }



int main()
{
    TL2 x = NULL;     /* Lista prelucrata */
    size_t lx=0;           /* lungime lista */
 
     printf("\nLungime lista: ");
     fflush(stdin); scanf("%i", &lx);
     
     x=GenerL(lx, -20, 50, "");
     TL2 aux;
 //  for (aux=x->urm->urm; aux != x ;aux = aux->urm)       /* pentru fiecare celula */
  //  printf("(%4i,%4i)", ((TPct*)(aux->info))->x,((TPct*)(aux->info))->y);  
   AfisareL(x, "x: [", "(%4i,%4i)\n", " ]\n");
   printf("\n numarul de elem%i\n",NrElem(x));
      ResetL2(x,fe);
      x=GenerL(lx, -30, 10, "");
      
       AfisareL(x, "x: [", "(%4i,%4i)\n", " ]\n");
      
      
      DistrL2(&x,fe);
      getch();
    return 0;    
}
