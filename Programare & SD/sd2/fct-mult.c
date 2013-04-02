#include "multime.h"
int Apartine(void *a, size_t na,  size_t d, void *x, TFComp cmp)
   /* intoarce 1/0 cu semnificatia adevarat/fals*/
{ void *p=a; void *sf=p+na*d; 
  
  while (p<sf) 
   { if (cmp(p,x)==0) 
   return 1; 
     p+=d;
   }
  
return 0;  
}


void* Loc( void *a, size_t na, size_t d, void *x, TFComp cmp)
{
  void *p=a, *sf=p+na*d; 
  
  while (p<sf) 
   { if (cmp(p,x)==0) 
   return p; 
     p+=d;
   }
return NULL; 
}


int Adauga(void *a, size_t na, size_t d, void *nou, TFComp cmp)
{
     a=(char*)a;
    void *p=a, *sf=p+na*d; 
    nou=(char*)nou;
   while (p<sf)
         {
          if (cmp(p,nou)==0) 
           return 0;
            p+=d;
         }
copie(a+na*d,nou,d);
return 1;
}


void copie (void* dest, void* sursa, size_t d)
{
 char *p=(char*)dest , *sf=p+d , *b=(char*)sursa ;
      for (;p<sf; p++)
      { *p=*b; b++;
      }
}


int Elimina(void *a, size_t na, size_t d, void *x, TFComp cmp)
{   
   char *p=(char *)a, *sf=p+na*d,*b=(char *)x;
     while (p<sf) 
           { if (cmp(p,b)==0)
             { copie(p,sf-d,d);
             return 1;
             }
         p+=d;
         }
         return 0;
}



void* Reun2(void *a, size_t na, void *b, size_t nb, size_t d,TFComp cmp, int *nr)
{
      char *m;
      m=malloc((na+nb)*d);
      if(!m)
      return NULL;
      *nr=Reun1(a,na,b,nb,d,m,cmp);
      return m;
      }
/*
void *CautBin(void *a, size_t na, size_t dim, TFComp cmp, void *x, int *r)
{
 char *p=(char *)a, *sf=p+na*d;
 char *m,*r,*l;
 r=sf;
 l=p;
 int m1=na/2;
 m=p+m1*d;
 while(l<=r)
 {
           if(cmp(x,m)==0)
           return m;
           else
           if(cmp(x,m)>0)
*/


void* LocO( void *a, size_t na, size_t d, void *x, TFComp cmp)
{
      void * loco;
      void *p=a;
      void *sf=a+na*d;
      int r=1;
      while(p<sf)
      {
       r=cmp(p,x);
       if(r>=0)
       break;
       else p+=d;
       }
       return r?NULL:p;
}

void DeplSt(void *a, size_t dim, size_t d)
{
char * dest=(char *)a, *sursa=(char*)a+d,*sf=sursa+dim;
         for(;sursa<sf;dest++,sursa++)
            *dest=*sursa;
}



void *CautBin(void *a, size_t na, size_t d, TFComp cmp, void *x, int *r)
{
     char *inf=(char *)a-d,*sup=(char *)a+na*d,*m;
     int t;
     *r=0;
     while(sup-inf>d)
     {
                     m=inf+((sup-inf)/d+1)/2*d;
                     t=cmp(x,m);
                     if(t==0)
                     {
                             *r=1;
                             return m;
                     }
                     if(t<0)
                     sup=m;
                     else 
                     inf=m;
     }
     return t<0?m:m+d;
}

void *DeplDr(void *a, size_t dim, size_t d)
{
     char *dest=(char *)a+dim,*sursa=(char *)a+dim-d,*sf=sursa+dim;
     for(;sursa>=(char*)a;dest--,sursa--)
     {
         *dest=*sursa;
         }
return a;
         }




int Inserare(void *a, size_t na, size_t d, void *nou, TFComp cmp)
{
 char *p=(char *)a,*sf=p+na*d;
 nou=(char *)nou;
 int r;
 char *pv;
 pv=CautBin(p,na,d,cmp,nou,&r);
 char *in;
 in=pv;
 if(r==1)
 return 0;
 else
 {
 int poz=(pv-p)/d;
 DeplDr(pv,(poz+na)*d,d);
 copie(in,nou,d);
 }
return 1;
}

int ElimO(void *a, size_t na, size_t d, void *x, TFComp cmp)
{
    char *p=(char *)a,*sf=p+na*d;
    x=(char*)x;
    int r;
    char *pv;
    pv=(char*)CautBin(p,na,d,cmp,x,&r);
    if(r==1)
    {
    DeplSt(pv,na*d,d);
    return 1;
    }
    else
    return 0;
}
int Reun1(void *a, size_t na, void *b, size_t nb, size_t d,
          void *r, TFComp cmp)
{
  int nr=0;         

  char *p=(char *)a,*sfa=p+na*d;
  char *q=(char *)b,*sfb=q+nb*d;
  char *m=(char*)r;
  if(na>=nb)
  {
  nr=na;
  while (p<sfa) 
   {  
        copie(m,p,d); 
     p+=d;
     m+=d;
   }
   p=(char*)a;
  while(q<sfb)
  { 
  if (cmp(q,p)!=0)
  {
  
  copie(m,q,d);
  nr++;
  m+=d;
  }
  
  q+=d;
  p+=d;             
}}
else 
{ nr=nb;
     while (q<sfb) 
   {  
        copie(m,q,d); 
     q+=d;
     m+=d;
   }
   q=(char*)a;
  while(p<sfa)
  {
  if (cmp(q,p)!=0)
  {
  nr++;
  copie(m,p,d);
  }
  q+=d;
  p+=d;
  m+=d;
}} 
             
return nr;
}  

int Reun1O(void *a, size_t na, void *b, size_t nb, size_t d,void *r, TFComp cmp)
{
    char *x=(char *)a, *sfx=a+na*d;
    char *y=(char *)b, *sfy=b+nb*d;
    r=(char *) r;
    int nr=0;
    while(x<sfx)
    {           if(y<sfy)
                {           
                if(cmp(x,y)==0)
                {
                               nr++;
                               copie(r,x,d);
                               x+=d;
                               y+=d;
                               r+=d;
                }
                else
                if(cmp(x,y)>0)
                {
                              nr++;
                              copie(r,y,d);
                              y+=d;
                              r+=d;
                }
                else
                {
                              nr++;
                              copie(r,x,d);
                              x+=d;
                              r+=d;
                }}
                else
                {
                         nr++;
                         copie(r,x,d);
                         x+=d;
                         r+=d;
                }}
    if(y<sfy)
    while(y<sfy)
    {
                nr++;
                copie(r,y,d);
                y+=d;
                r+=d;
                }
                
return nr;
}
void* Reun2O(void *a, size_t na, void *b, size_t nb, size_t d, 
             TFComp cmp, int *nr)
{
         
      char *m;
      m=malloc((na+nb)*d);
      if(!m)
      return NULL;
      *nr=Reun1O(a,na,b,nb,d,m,cmp);
      return m;
}
void Isort(void *a,size_t n,TFComp cmp,size_t d)
{
      char  *aux;
     aux=malloc(n*d);
     a=(char*)a;
     if(!aux)
    return;
     int i,j;
     
     for(i=1;i<n;i++)
     {
                  copie(aux,a+i*d,d);
                   j=i-1;
while((j>=0) && (/**aux < a[j]*/cmp(aux,a+j*d)<0))
{
copie(a+(j+1)*d,a+j*d,d);
j--;
}

copie(a+(j+1)*d,aux,d);   
}}

/*
void Isort(int *a,size_t n,size_t d,TFComp cmp)
{
     int *aux;
     aux=malloc(n*d);
     if(!aux)
     return;int i,j;
     for(i=1;i<n;i++)
     {
                     copie(aux,a+i*d,d);
                     j=i-1;
                     while((cmp(a+j*d,a+i*d)>0)&&(j>=0))
                     {
                                                copie(a+(j+1)*d,a+j*d,d);
                                                j--;
                                                
                                                }
                                                
                     copie(a+j*d,a+i*d,d);
     }
     }

*/
