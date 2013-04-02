/*-- L-CS.c --*/
#include <conio.h>
#include "CS.h"

void Eroare(char mesaj[], int k)
{ fprintf (stderr, "%s\n", mesaj);
  getch();
  exit(k);
}

int ExCifre(char *s,...)
{ char *p = s;
  for(; *p != '\0'; p++)
    if (*p >= '0' && *p <= '9') return 1;
  return 0;
}

int Afi(char *s,...)
{ return printf("%s\n", s); }

int main ()
{ char c;
  int nCitit, n;
  ACS ac1;
  char nume[100], tip;
  FILE *f;
  size_t k;
  
  ac1 = AlocCS(5,5);
  if (!ac1) Eroare ("\nAlocare imposibila\n", 1);
  /*-- preia date din fisier --*/
  printf ("Nume fisier citire siruri: "); fflush(stdin);
  gets(nume);
  if (nume[0] == '\0') Eroare ("Nume fisier citire vid!!!", 2);
  f = fopen(nume, "rt");
  nCitit = CitireCS(ac1, f, AdaugaCS);
  fclose (f);
  printf ("S-au citit %i siruri\n\n", nCitit);
  if (nCitit == 0) return -1; 
  AfiCS(ac1);
  printf("\n-- Siruri cu cifre\n", n);
  n = PrelCondCS(ac1, Afi, ExCifre, 1);
  if (!n) printf("\tNu exista\n");
  else printf("\t%i %s\n", n, n > 1 ? "siruri" : "sir");
  getch();

  printf("\n-- Siruri fara cifre\n", n);
  n = PrelCondCS(ac1, Afi, ExCifre, 0);
  if (!n) printf("\tNu exista\n");
  else printf("\n\t%i %s\n", n, n > 1 ? "siruri" : "sir");
  getch();
}
