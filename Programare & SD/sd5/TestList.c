/*--- TestList.c ---*/
#include <conio.h>
#include <ctype.h>
#include "tlista.h"
#include <stdarg.h>
ALista InsSfLr (ALista a, AEL x)
  /* functie recursiva de inserare la sfarsitul listei; 
     intoarce adresa legatura la celula inserata sau NULL */
{// este in funcLista.c
     
}
int f(AEL e,...)
{ va_list ap;
va_start(ap,e);

    if(*e%va_arg(ap,int)==0)
   {                        va_end(ap);
                             return 1;
                             }
    else
    {   va_end(ap);
         return 0;
}

}


ALista aux;
ALista CautaU_r(ALista a, TFPrelEL f, int Gasit)
  /* functie recursiva - intoarce NULL sau adresa legatura la ultima celula 
     pentru a carei info functia f intoarce valoarea Gasit */
{
     ALista p;
     p=a;
     if(f(&(*p)->info,7)==Gasit)
               aux=p;
     if((*p)->urm==NULL)
               return aux;
     return CautaU_r(&(*p)->urm,f,Gasit);
}
int ElimCond(ALista a, TFPrelEL f, int Gasit)
  /* obiectiv: eliminarea din lista a primei celule pentru a carei info 
     functia f intoarce valoarea Gasit; rezultat 1 = succes, 0 = esec */
{    TLista aux;

     for(;(*a)->urm!=NULL;a=&(*a)->urm)
     {
              if(f(&(*a)->info,5)==Gasit)
              {
              aux=(*a);
           *a=(aux)->urm;// de ce nu // a=&aux->urm;
              free(aux);
              return 1;
              }
              }
              return 0;
}
int Test(AEL e,...) /* functie de test, la alegere */
{
}

int main ()
{ TLista x = NULL;     /* Lista prelucrata */
  size_t lx;           /* lungime lista */

  for (;;)
  { printf("\nLungime lista: ");
    fflush(stdin); scanf("%i", &lx);
    if (lx <= 0) break;
    /* genereaza si afiseaza lista cu maxim lx elemente */
    x = GenerL(lx, -20, 50, "");
    AfisareL(&x, "x: [", "%4i", " ]\n");

    printf("\n--- Inserari la sfarsitul listei ---\n");
    /* - cat timp se citeste o valoare insereaza la sfarsitul listei 
       - afisare lista */
    int a;
    for(;;)
    { printf("introduceti element la sfars\n");
      if(scanf("%i",&a))
      InsSfLR(&x,&a);
      else
      break;
      }
      AfisareL(&x, "x: [", "%4i", " ]\n");
      
      
    
    printf("\n--- Eliminari din lista ---\n");
    /* - cat timp se citeste o valoare
         { apeleaza ElimCond 
           daca succes atunci afisare lista
                       altfel afisare mesaj
         }              
    */
    
         if(ElimCond(&x,f,1))
         AfisareL(&x, "x: [", "%4i", " ]\n");
         else
         printf("nu s-a gasit");
           
           
           
    printf("\n--- Cautari in lista ---\n");  
    /* - cat timp se citeste o valoare
            apeleaza CautaU_r si afiseaza rezultat (adresa si info) */
    ALista ax;
      ax=CautaU_r(&x,f,1);
    if(ax)
    { printf("gasit \n");
    AfisareL(ax, "Gasit: [", "%4i", " ]\n");
    }
    else
    printf("nu s-a gasit");
    
    
    
    // alte chestii
    printf("test numara recursiv \n");
    printf("%i\n",LungLR(x));
  //  AfisI(x);
    ALista q;
  q=CautLeg(&x,f);
    printf("legatura\n");
    printf("%i",(*q)->info);
    // inserare pe pozitia dorita 
    int nrp=6;
    printf("inserati pozitia pe pozitie:\n");
    InsNr(&x,nrp,&nrp);
    AfisareL(&x, "x: [", "%4i", " ]\n");
    int nrp1=5;
    InsF(&x,7,&nrp1);
    AfisareL(&x, "x: [", "%4i", " ]\n");
    
    
    
    
    DistrL(&x);
    printf ("\n  Inca un test ? [D/] ");
    if (toupper(getch()) != 'D') break;
  }
}

