/*-- multime3.c --*/
#include "multime.h"
#include <time.h>
//#include <random.h>

typedef struct
{ int v1;
  double v2;
  char v3[21];
} Tx, *Ax;

void inix(Ax x) /* initializare aleatoare element */
{ int i;
  i = x->v1 = random(20)-10;
  x->v2 = random(10000)/100.;
  i = random(8)+2;
  x->v3[i] = '\0';
  while (i-- > 0) x->v3[i] = 'a' + random(26);
}


void afiTx(Ax x, int n)
{ int i = 0;
  printf("      v1     v2   v3\n");
  for( ; i < n; i++) 
    printf("[%2i]%4i%7.2lf  %s\n", i, x[i].v1, x[i].v2, x[i].v3);
}
int cmp( const void * a,const void * b)
{   Tx *x=(Tx *)a;
    Tx *y=(Tx *)b;
    int p=x->v1-y->v1;
    double d=x->v2-y->v2;
    int s=strcmp(x->v3,y->v3);
    if(p==0)
    {
            if(d==0)
            {
            return s;
            }
            else if(d<0)
            return -1;
            else return 1;
    }
    else
    if(p<0)
    return -1;
    else return 1;
}






int main()
{ Tx v[10], x, *r,tv[100];
  int nv = 10, i, nr, vi[7], ni = 7, *ri;
  
  randomize();
  printf("--- Demo multimi generice ---\n");
  for(i = 0; i < nv; i++) inix(v+i);

  

// reuniunea pt multimi sortate interclasare
printf("sortare si afisare elemnete vector:\n");

int nrtv=5;
int nrr1;
for(i = 0; i < nrtv; i++) inix(tv+i);
printf("reuniunea 1:\n");
printf("-- Multimea v --\n"); 
afiTx(v, nv);
printf("-- Multimea tv --\n"); 
  afiTx(tv, nrtv);
  Tx r1[110];
nrr1=Reun1(v,nv,tv,nrtv,sizeof(Tx),r1,cmp);
printf(" nr elem : %i\n",nrr1);
afiTx(r1,nrr1);


/*
// Reun2 reuniunea 2
printf("reuniunea 2:\n");
Tx *r;
r=Reun2(v,nv,tv,nrtv,sizeof(Tx),cmp,&nrr1);
printf(" nr elem2  : %i\n",nrr1);
afiTx(r,nrr1);

*/

printf("sortare si afisare elemnete vector:\n");
// pt vectori sortati
qsort(v,nv,sizeof(Tx),cmp);
printf("-- Multimea v --\n"); 
afiTx(v, nv);
qsort(tv,nrtv,sizeof(Tx),cmp);
printf("-- Multimea tv --\n"); 
afiTx(tv, nrtv);
Tx reun[100];
int nrreun;
printf("reuniunea\n");
nrreun=Reun1O(tv,nrtv,v,nv,sizeof(Tx),reun,cmp);
printf("-- Multimea  reuniune reun --\n"); 
afiTx(reun,nrreun);
// reuniunea cu alocare ;
/*
printf("reuniunea cu alocare\n");
double * reu;
reu=Reun2O(ttv,nrtv,tv,nrv1,sizeof(double),cmp,&nrreun);
afisdouble(reu,nrreun);

*/

Tx ttv[100];
int nrttv=4;
for(i = 0; i < nrttv; i++) inix(ttv+i);

printf("sortarea prin insertie\n");
afiTx(ttv,nrttv);
printf("sortat: \n");
Isort(ttv,nrttv,cmp,sizeof(Tx));
afiTx(ttv,nrttv);
  
  
  
  
  
  
  
  /*
  printf("test apartine \n element pt apartine pt apartine:\n");
  Tx a;
  printf("v1:\n");
  scanf("%i",&a.v1);
  printf("v2:\n");
  scanf("%lf",&a.v2);
  printf("v1:\n");
  scanf("%s",a.v3);
  if(Apartine(v,nv,sizeof(Tx),&a,cmp)==0)
printf("nu apartine\n");
else    
printf("apartine\n");
printf("test localizare\n numarul pt localizare:\n");

  printf("v1:\n");
  scanf("%i",&a.v1);
  printf("v2:\n");
  scanf("%lf",&a.v2);
  printf("v1:\n");
  scanf("%s",a.v3);
if(Loc(v,nv,sizeof(Tx),&a,cmp)==NULL)
printf("nu apartine\n");
else
//printf("%p\n",Loc(v,nv,sizeof(Tx),&a,cmp));
afiTx((Tx*)Loc(v,nv,sizeof(Tx),&a,cmp),1);

printf("test adaugare \n numarul pt adaugare:\n");

  printf("v1:\n");
  scanf("%i",&a.v1);
  printf("v2:\n");
  scanf("%lf",&a.v2);
  printf("v1:\n");
  scanf("%s",a.v3);
if(Adauga(v,nv,sizeof(Tx),&a,cmp)==1)
{
printf("s-a adaugat\n");
nv++;
afiTx(v, nv);
}
else
printf("exista deja\n"); 

  // test elimina 
printf("test eliminare \n numarul pt eliminare:\n");
  printf("v1:\n");
  scanf("%i",&a.v1);
  printf("v2:\n");
  scanf("%lf",&a.v2);
  printf("v1:\n");
  scanf("%s",a.v3);

if(Elimina(v,nv,sizeof(Tx),&a,cmp)==1)
{
printf("s-a eliminat\n");
nv--;
afiTx(v,nv);
}
else
printf("nu exista\n");

Tx t[100],r1[100];
int n=10;
for(i = 0; i < n; i++) inix(t+i);
afiTx(t,n);
printf("reuniunea 1:\n");
int nrr1=Reun1(v,nv,t,n,sizeof(Tx),r1,cmp);
afiTx(r1,nrr1);


// sortate
printf("sortare si afisare elemnete structura:\n");
qsort(v,nv,sizeof(Tx),cmp);

printf("test cautare secventiala LocO \n numarul pt cautare:\n");
Tx *ppv1;
  printf("v1:\n");
  scanf("%i",&a.v1);
  printf("v2:\n");
  scanf("%lf",&a.v2);
  printf("v1:\n");
  scanf("%s",a.v3);
ppv1=LocO(v,nv,sizeof(Tx),&a,cmp);
if(ppv1==NULL)
printf("cautare esuata\n");
else 
printf("element localizat\n");
//cautare binara
printf("test cautare binare \n numarul cautare binara:\n");
  printf("v1:\n");
  scanf("%i",&a.v1);
  printf("v2:\n");
  scanf("%lf",&a.v2);
  printf("v1:\n");
  scanf("%s",a.v3);

  
  
  
  
  */
  
  getch();
  
/* S = secventa de prelucrari, folosind operatii generice:
   - test apartenenta
   - test localizare
   - adaugare 2 noi elemente: unul care nu exista si altul care exista
   - afisare multime
   - eliminare 2 elemente: unul care exista si altul care nu exista
   - afisare multime
*/

/* Sortare multime, urmata de afisare */

/* Repetarea S folosind functii specifice multimii sortate */

  return 0;
}

