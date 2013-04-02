/*-- multime.c --*/
#include "multime.h"

/*-- functie de afisare multime --*/
void afisint( int v[100], int n)
{    int i;
     for(i=0;i<n;i++)
         printf(" v[%i]=%i \n",i+1,v[i]);
}

/*-- functie de comparatie --*/
int cmp( const void * a,const void * b)
{   int *x=(int *)a;
    int *y=(int *)b;
    return *x-*y;
}
int Dis(void *a,size_t na,void *b,size_t nb,size_t d,TFComp comp)
{
    char *x=(char *)a,*sfx=x+na*d;
 
    
    while(x<sfx)
    {
     if(Apartine(b,nb,d,x,cmp)==0)
     { 
     x+=d;
     }
                else 
                return 0;
                }
return 1;
}




int main()
{/* declaratie vector de intregi initializat ca multime */
int v[]={5,6,3,1,73,2,54,21,4,123};
int tv[]={30,40,50,60,70,120,4};
int m=7;
int n=10;
afisint(v,n);
int a;
afisint(tv,m);
/*
int ok=Dis(v,n,tv,m1,sizeof(int),cmp);
if(ok==1)
printf("sunt disjuncte");
else
printf("nu sunt disjuncte");











printf("test apartine \nnumarul pt apartine:\n");
scanf("%i",&a);
int t[]={5,6,100,10,20,30};
int m=6;
// test apartine
printf("test apartine \nnumarul pt apartine:\n");
scanf("%i",&a);
if(Apartine(v,n,sizeof(int),&a,cmp)==0)
printf("nu apartine\n");
else    
printf("apartine\n");
printf("test apartine \nnumarul pt apartine:\n");
scanf("%i",&a);
if(Apartine(v,n,sizeof(int),&a,cmp)==0)
printf("nu apartine\n");
else    
printf("apartine\n");
// test localizare
printf("test localizare\n numarul pt localizare:\n");
scanf("%i",&a);
int *ppv=Loc(v,n,sizeof(int),&a,cmp);
if(ppv==NULL)
printf("nu apartine\n");
else
printf("%i\n",ppv-v);

printf("test localizare\n numarul pt localizare:\n");
scanf("%i",&a);
if(Loc(v,n,sizeof(int),&a,cmp)==NULL)
printf("nu apartine\n");
else
printf("%d\n",Loc(v,n,sizeof(int),&a,cmp));

// test adaugare element la vector
printf("test adaugare \n numarul pt adaugare:\n");
scanf("%i",&a);

if(Adauga(v,n,sizeof(int),&a,cmp)==1)
{
printf("s-a adaugat\n");
n++;
afisint(v,n);
}
else
printf("exista deja\n"); 
printf("test adaugare \n numarul pt adaugare:\n");
scanf("%i",&a);

if(Adauga(v,n,sizeof(int),&a,cmp)==1)
{
printf("s-a adaugat\n");
n++;
afisint(v,n);
}
else
printf("exista deja\n"); 
// test elimina 
printf("test eliminare \n numarul pt eliminare:\n");
scanf("%i",&a);

if(Elimina(v,n,sizeof(int),&a,cmp)==1)
{
printf("s-a eliminat\n");
n--;
afisint(v,n);
}
else
printf("nu exista\n");
printf("test eliminare \n numarul pt eliminare:\n");
scanf("%i",&a);

if(Elimina(v,n,sizeof(int),&a,cmp)==1)
{
printf("s-a eliminat\n");
n--;
afisint(v,n);
}
else
printf("nu exista\n");
*/


//Reun1 reuniuunea 1

int *r,r1[100];
int nrr1;
int nrr2;

printf("reuniunea 1:\n");
afisint(v,n);
afisint(tv,m);
nrr1=Reun1(v,n,tv,m,sizeof(int),r1,cmp);
printf(" nr elem : %i\n",nrr1);
afisint(r1,nrr1); 


// Reun2 reuniunea 2
 
printf("reuniunea 2:\n");
r=Reun2(v,n,tv,m,sizeof(int),cmp,&nrr2);
printf(" nr elem2  : %i\n",nrr2);
afisint(r,nrr2);


/*
// test cautare secventiala LocO
int *pv;
int cau;
printf("test cautare secventiala LocO \n numarul pt cautare:\n");
scanf("%i",&cau);
pv=LocO(tv,nrv1,sizeof(int),&cau,cmp);
if(pv==NULL)
printf("cautare esuata\n");
else 
printf("elem cautat gasit :%i\n",*pv);
printf("test cautare secventiala LocO \n numarul pt cautare:\n");
scanf("%i",&cau);
pv=LocO(tv,nrv1,sizeof(int),&cau,cmp);
if(pv==NULL)
printf("cautare esuata\n");
else 
printf("elem cautat gasit :%i\n",*pv);




// test deplasare stanga
printf("deplasare stanga\n");

DeplSt(tv+5,(nrv1-4)*sizeof(int),sizeof(int));
afisint(tv,nrv1-1);



//test deplasare dreapta
afisint(tv,nrv1-1);
printf("test deplasare dreapta\n");
DeplDr(tv+3,(nrv1-3)*sizeof(int),sizeof(int));
afisint(tv,nrv1);



//test cautare binara;

//int tv[100]={5, 26,12,33,3,1,73,2,54,21,4,123};
int r11;

afisint(tv,nrv1);
printf("test cautare binare \n numarul cautare binara:\n");
scanf("%i",&cau);

pv=CautBin(tv,nrv1,sizeof(int),cmp,&cau,&r11);
if(r11==1)
printf("s-a gasit binar %i\n",*pv);
else 
printf("nu am gasit %i succesor predecesor \n",*pv);


//test inserare

printf("inserare\n");
afisint(tv,nrv1);
printf("test inserare \n numarul pt inserare:\n");
scanf("%i",&cau);
int rez=Inserare(tv,nrv1,sizeof(int),&cau,cmp);
if(rez==0)
printf("exista deja");
else
afisint(tv,nrv1+1);




//test eliminare
int tv1[]={-5,2,13,7,-4,12,11};
nrv1=7;
qsort(tv1,nrv1,sizeof(int),cmp);

afisint(tv1,nrv1);
printf("test eliminare \n numarul pt eliminare:\n");
scanf("%i",&cau);


printf("eliminare");
ok=ElimO(tv1,nrv1,sizeof(int),&cau,cmp);
if(ok==1)
afisint(tv1,nrv1-1);
else
printf("nu exista\n");
*/
// reuniunea pt multimi sortate interclasare
printf("sortare si afisare elemnete vector:\n");
int t[100]={5,0, 26,12,10};
int ttv[100]={0,-1,10,101,201};
int nrtv=5;
int nrv1=5;
// pt vectori sortati
qsort(t,nrv1,sizeof(int),cmp);
printf("primul vector");
afisint(t,nrv1);
qsort(ttv,nrtv,sizeof(int),cmp);
printf("al doilea vector");
afisint(ttv,nrtv);
int reun[100];
int nrreun;
printf("reuniunea\n");
nrreun=Reun1O(ttv,nrtv,t,nrv1,sizeof(int),reun,cmp);
afisint(reun,nrreun);
// reuniunea cu alocare ;
printf("reuniunea cu alocare\n");
int * reu;
reu=Reun2O(ttv,nrtv,t,nrv1,sizeof(int),cmp,&nrreun);
afisint(reu,nrreun);
printf("sortarea prin insertie");

int isort[100]={1,3,2,4,-1,10,100,-21,1};
int nri=9;
afisint(isort,nri);
Isort(isort,nri,cmp,sizeof(int));
afisint(isort,nri);









/* S = secventa de prelucrari, folosind operatii generice:
   - afisare multime
   - test apartenenta
   - test localizare
   - adaugare 2 noi elemente: unul care nu exista si altul care exista
   - afisare multime
   - eliminare 2 elemente: unul care exista si altul care nu exista
   - afisare multime
*/

/* Sortare multime */

/* Repetarea S folosind functii specifice multimii sortate */
   getch();
  return 0;
}



