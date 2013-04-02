/*-- L-funcCS.c -- operatii Colectie Siruri --*/
#include "CS.h"

ACS AlocCS(size_t d, size_t e)
 /* aloca descriptor colectie si spatiu pentru d adrese de siruri */
{ 
     ACS p;
     p=(ACS)malloc(sizeof(TCS));
     if(!p)
     return NULL;
     printf("");
    p->c=(char **)calloc (d, sizeof (char*));
     p->nc=0;
     p->na=d;
     p->ne=e;
     return p;
}

void DistrugeCS(ACS *x)
     /* elibereaza intregul spatiu ocupat de o colectie */
{ int i;
     for(i=0;i<(*x)->nc;i++)
     free((*x)->c[i]);
     free(*x);
     *x=NULL;
  }

int AdaugaCS(ACS x, char *s)
     /* adauga copia sirului s, daca este posibil */
{ char ** aux;
   if (x->nc>=x->na)
    { aux=(char **)realloc(x->c, (x->na+x->ne)*sizeof(char *));
     x->c=aux;
     } 
     x->c[x->nc]=strdup(s);
  x->nc++;
}

size_t CitireCS(ACS a, FILE *f, int (*Ad)(ACS, char*))
     /* citeste din fisierul f, oprindu-se la epuizarea spatiului sau la sfarsitul fisierului. 
        Pentru adaugarea sirului in colectie apeleaza functia data ca parametru (Ad).
        Intoarce numarul de valori citite (>= 0) -*/
{ size_t i = 0;   /* numar valori citite = indicele urmatorului element */
  char linie[81],*ac;
  int j;
  linie[80] = '\0';
  /*- cat timp mai exista linii in fisier si spatiu, citeste din fisier -*/
  while (fgets(linie, 80, f) != NULL)
  { j = strlen(linie);
    if (linie[j-1] == '\n') linie[j-1]='\0';
    if (!Ad(a, linie)) break;
    i++;
  }
  return i;
}

void AfiCS(ACS x)
     /* afiseaza sirurile din colectie */
{ size_t i, n = 0;
  for (i = 0; i < x->nc; i++)
    printf("%2i.\"%s\"\n", i+1, x->c[i]);
}

size_t PrelCondCS(ACS x, int (*Prel)(char *s,...),
		   int (*test)(char *s,...), int cod)
     /* aplica functia Prel sirurilor din colectie
	pentru care functia test intoarce cod */
{ size_t i, n = 0;
  for (i = 0; i < x->nc; i++)
    if (test (x->c[i]) == cod)
    { Prel(x->c[i]);
      n++;
    }
  return n;
}
