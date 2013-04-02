#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char *argv[])
{
  unsigned int iseed = (unsigned int)time(NULL);
  srand (iseed);

  /* Now generate 5 pseudo-random numbers */
  int i;
  unsigned int x[11] ;
  for(i = 0 ; i <= 10 ; i++){
	x[i] = 0;
  }
  for( i = 0 ; i < 100000; i++){
	int i = rand()*(10 - 0) + 0 ;
	x[i] ++;	
  }

 for(i = 0 ; i <= 10 ; i++){
        printf("%i  %i \n",i,x[i]); 
  }

  return 0;
}
