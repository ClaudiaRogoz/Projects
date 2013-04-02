#include "GrDinamic.h"
#include<conio.h>
int main()
{
    AGrupa g;
    FILE *f;
    int nstud,nmat,nrnote;
    char numefis[21], *nf=numefis;
    printf("introduceti numele fisierului:\n",numefis);
    gets(numefis);
    f=fopen(numefis,"rt");
    if(!f)
    { printf("Eroare la deschidere fisier %s\n",nf);
     getch();
     return -1;
     
     }
     int nrstud=6,nrmat;
    g=AlocGrupa(nrstud,nrmat);
   (*g).nrstud=CitStud(f,g);
    fclose(f);
    if(g->nrnote==0)
    { printf("Fisier vid!!!\n");
    return -2;
    }
    TabelStud(g);
    getch();
    return 0;
}
