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
{   printf("%s",a);
    if(a==b)
    return 1;
    return 0;
}





int main()
{/* declaratie vector de intregi initializat ca multime */
int v[]={5,6,3,1,73,2,54,21,4,123};
int n=10;
afisint(v,n);

                    if(cmp("ana","ana"))
                printf("sunt egale");
                else printf("nu sunt egale");
                
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



