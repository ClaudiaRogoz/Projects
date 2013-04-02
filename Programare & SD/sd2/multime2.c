/*-- multime.c --*/
#include "multime.h"

/*-- functie de afisare multime --*/
void afisdouble( double v[100], int n)
{    int i;
     for(i=0;i<n;i++)
         printf(" v[%i]=%.2lf \n",i+1,v[i]);
}

/*-- functie de comparatie --*/
int cmp( const void * a,const void * b)
{   double *x=(double *)a;
    double *y=(double *)b;
    double p=*x-*y;
	if(p==0)
	return 0;
	else if(p>0)
	return 1;
	else return -1;
}


int main()
{/* declaratie vector de intregi initializat ca multime */
double v[]={5.1,5};
int n=2;
afisdouble(v,n);
double a;

printf("test apartine \nnumarul pt apartine:\n");
scanf("%lf",&a);
double t[]={5,6,100,10,20,30};
int m=6;
/*
// test apartine
if(Apartine(v,n,sizeof(double),&a,cmp)==0)
printf("nu apartine\n");
else    
printf("apartine\n");


//test adugaree


// test localizare
printf("test localizare\n numarul pt localizare:\n");
scanf("%lf",&a);
if(Loc(v,n,sizeof(double),&a,cmp)==NULL)
printf("nu apartine\n");
else
printf("%lf\n",(double*)Loc(v,n,sizeof(double),&a,cmp));



// test elimina
double elim; 
printf("test eliminare \n numarul pt eliminare:\n");
scanf("%lf",&elim);

if(Elimina(v,n,sizeof(double),&elim,cmp)==1)
{
printf("s-a eliminat\n");
n--;
afisdouble(v,n);
}
else
printf("nu exista\n");
// test adaugare element la vector
printf("test adaugare \n numarul pt adaugare:\n");
scanf("%lf",&a);

if(Adauga(v,n,sizeof(double),&a,cmp)==1)
{
printf("s-a adaugat\n");
n++;
afisdouble(v,n);
}
else
printf("exista deja\n"); 
printf("test adaugare \n numarul pt adaugare:\n");
scanf("%lf",&a);

if(Adauga(v,n,sizeof(double),&a,cmp)==1)
{
printf("s-a adaugat\n");
n++;
afisdouble(v,n);
}
else
printf("exista deja\n"); 
printf("test adaugare \n numarul pt adaugare:\n");
scanf("%lf",&a);

if(Adauga(v,n,sizeof(double),&a,cmp)==1)
{
printf("s-a adaugat\n");
n++;
afisdouble(v,n);
}
else
printf("exista deja\n"); 

*/
//Reun1 reuniuunea 1
double *r,r1[100];
int nrr1;
int nrr2;

printf("reuniunea 1:\n");
printf("primul vector");
afisdouble(v,n);
printf("al doile vector");
afisdouble(t,m);
nrr1=Reun1(v,n,t,m,sizeof(double),r1,cmp);
printf(" nr elem : %i\n",nrr1);
afisdouble(r1,nrr1); 


// Reun2 reuniunea 2
printf("reuniunea 2:\n");
r=Reun2(v,n,t,m,sizeof(double),cmp,&nrr2);
printf(" nr elem2  : %i\n",nrr2);
afisdouble(r,nrr2);
printf("sortare si afisare elemnete vector:\n");
/*
double tv[100]={5, 26,12,33,3,1,73,2,54,21,4,123};
int nrv1=12;
// pt vectori sortati
qsort(tv,nrv1,sizeof(double),cmp);
afisdouble(tv,nrv1);

// test cautare secventiala LocO
double *pv;
double cau;
printf("test cautare secventiala LocO \n numarul pt cautare:\n");
scanf("%lf",&cau);
pv=LocO(tv,nrv1,sizeof(double),&cau,cmp);
if(pv==NULL)
printf("cautare esuata\n");
else 
printf("elem cautat gasit :%lf\n",*pv);




// test deplasare stanga
printf("deplasare stanga\n");

DeplSt(tv+5,(nrv1-4)*sizeof(double),sizeof(double));
afisdouble(tv,nrv1-1);



//test deplasare dreapta

printf("test deplasare dreapta\n");
DeplDr(tv+3,9*sizeof(double),sizeof(double));
afisdouble(tv,nrv1+1);



//test cautare binara;

//double tv[100]={5, 26,12,33,3,1,73,2,54,21,4,123};
int r11;

afisdouble(tv,nrv1);
printf("test cautare binare \n numarul cautare binara:\n");
scanf("%lf",&cau);

pv=CautBin(tv,nrv1,sizeof(double),cmp,&cau,&r11);
if(r11==1)
printf("s-a gasit binar %lf\n",*pv);
else 
printf("nu am gasit %lf succesor predecesor \n",*pv);


//test inserare

printf("inserare\n");
afisdouble(tv,nrv1);
printf("test inserare \n numarul pt inserare:\n");
scanf("%lf",&cau);
int rez=Inserare(tv,nrv1,sizeof(double),&cau,cmp);
if(rez==0)
printf("exista deja");
else
afisdouble(tv,nrv1+1);




//test eliminare
printf("test eliminare \n numarul pt eliminare:\n");
scanf("%lf",&cau);

double tv1[]={-5.1,0.2,0.1,13,7,-4,0.11,12,11};
nrv1=7;
qsort(tv1,nrv1,sizeof(double),cmp);
afisdouble(tv1,nrv1);
printf("eliminare");
int ok=ElimO(tv1,nrv1,sizeof(double),&cau,cmp);
if(ok==1)
afisdouble(tv1,nrv1-1);
else
printf("nu exista\n");

*/

// reuniunea pt multimi sortate interclasare
printf("sortare si afisare elemnete vector:\n");
double tv[100]={5.1,0.2, 26,12,10};
double ttv[100]={0,-1,10.3,101.2,201};
int nrtv=5;
int nrv1=5;
// pt vectori sortati
qsort(tv,nrv1,sizeof(double),cmp);
printf("primul vector");
afisdouble(tv,nrv1);
qsort(ttv,nrtv,sizeof(double),cmp);
printf("al doilea vector");
afisdouble(ttv,nrtv);
double reun[100];
int nrreun;
printf("reuniunea\n");
nrreun=Reun1O(ttv,nrtv,tv,nrv1,sizeof(double),reun,cmp);
afisdouble(reun,nrreun);
// reuniunea cu alocare ;
printf("reuniunea cu alocare\n");
double * reu;
reu=Reun2O(ttv,nrtv,tv,nrv1,sizeof(double),cmp,&nrreun);
afisdouble(reu,nrreun);


printf("sortarea prin insertie");
double isort[100]={1.2,3.3,2,4,-1.3,10.23,100,-21,1};
int nri=9;
afisdouble(isort,nri);
printf("sortat \n");
Isort(isort,nri,cmp,sizeof(double));
afisdouble(isort,nri);




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



