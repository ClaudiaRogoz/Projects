#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// functie care citeste dn fisierul de intrare filename si returneaza toti 
// parametrii necesari prelucrarii 
void readFromfile(char * filename, unsigned int* Pmin,unsigned int * Pmax,
				unsigned int* n,int*** tinut, int*** preturi,int *** bugete){
    
				char *line;
				FILE *fp = fopen(filename,"r");
				
		if(fp == NULL)
                {
                      printf("cannot open file");
                      exit(0);
                }
                
                fscanf(fp,"%i %i %i",Pmin,Pmax,n);
                
                int i,j;
                (*tinut) = (int **) malloc((*n)*sizeof(int *));
                (*preturi) = (int **) malloc((*n)*sizeof(int *));
                (*bugete) = (int **) malloc((*n)*sizeof(int *));
                
                for(i = 0; i < *n; i++){
                      (*tinut)[i] = (int *) malloc( (*n) * sizeof(int));
                      (*preturi)[i] = (int *) malloc( (*n) * sizeof(int));
                      (*bugete)[i] = (int *) malloc( (*n) * sizeof(int));
                }
                for(i = 0; i < *n; i++)
                {
                      for(j = 0; j < *n; j++)
                      {
                            int x;
                            
                            fscanf(fp,"%i",&x);
                            (*tinut)[i][j] = x;
                      }
                }
                for(i = 0; i < *n; i++)
                {
                      for(j = 0; j < *n; j++)
                      {
                            int x;
                            fscanf(fp,"%i",&x);
                            (*preturi)[i][j] = x;
                      }     
                }
                for(i = 0; i < *n; i++)
                {
                      for(j = 0; j < *n; j++){
                            int x;      
                            fscanf(fp,"%i",&x);
                            (*bugete)[i][j] =x ;
                      }
                }
				fclose(fp);
				
}

void activitatianuale(int n,int Pmin,int Pmax,int** tinut, int** preturi,int ** bugete,
		int *** pretanv,int*** bugeteanv,int*** tinutanv,int* nr0,int* nr1,int* max0,int* max1){
	
	int i,j,k,l;
	float f  = 0;

	for(i = 0; i < n; i++)
    	{
		for(j = 0; j < n; j++)
        	{
		
			int pretmincomp = 100000;
			int pretres = 10000000;
			int start_s = clock(); 
			for(k = 0; k < n ; k++)
            		{
				for(l = 0 ; l < n; l++)
                		{
					int dist = abs(i - k) + abs(j - l);
				    // gasim costul minim pentru resursa complementara 
				    int cost = preturi[k][l] + dist;
				    if(cost < pretmincomp && tinut[k][l] == (1 - tinut[i][j])){
				            
				            pretmincomp = cost;
				            
				    }
				    // costul minim pentru resursa proprie din perspectiva colonistului i,j
				    int costres = preturi[k][l] + dist;
				    if(costres < pretres && tinut[k][l] == tinut[i][j]){
				    
				            pretres = costres;
				            
				    }
                
                		}
             		}
             		f += (clock() - start_s) / (double)(CLOCKS_PER_SEC)*1000;
             		
             // pretmincompl pretminim pentru resursa complementara din persp lui i,j
             // pretres cost min pentru resursa proprie din persp lui i,j
             
             // daca costul resursei complementare deparseste bugetul alocat in
             // crestem bugetul si se modif pretul resursei proprii 
             if(pretmincomp > bugete[i][j])
             {
                            (*bugeteanv)[i][j]  = pretmincomp;
                            (*pretanv)[i][j] = preturi[i][j] + pretmincomp -  bugete[i][j];
             }
             
             // daca costul resursei compl este sub bugetul alocat pt anul viitor 
             // va scadea bugetul si pretul resursei proprii 
             if(pretmincomp < bugete[i][j])
             {
                            (*bugeteanv)[i][j] = pretmincomp;
                            int dif = (int)((pretmincomp - bugete[i][j])/2);
                            
                            (*pretanv)[i][j] = preturi[i][j] + dif;
                                       
             }
             
             //daca costul resursei pretmincomp este egal cu bugetul din acel an 
             // se modifica doar pretul resursei proprii 
             if(pretmincomp == bugete[i][j])
             {
                            (*bugeteanv)[i][j] = pretmincomp;
                            (*pretanv)[i][j] = pretres + 1;
             }
             
             // daca pretul scade sub limita minima admisa se truncheaza pretul 
             // la pretul minim 
           
             
             if(  (*pretanv)[i][j] < Pmin)
             {                   
                                 (*pretanv)[i][j] = Pmin;
                                 
             }
             
             if((*pretanv)[i][j] > Pmax)
             {                   
                                
                                 (*tinutanv)[i][j] = (1 - tinut[i][j]);
                                 (*bugeteanv)[i][j] = Pmax;
                                 (*pretanv)[i][j] = (int)((Pmin + Pmax)/2);
                                 
             }else{
                                 (*tinutanv)[i][j] = tinut[i][j];
                   }
             
             if((*tinutanv)[i][j] == 0){
             	(*nr0)++;
             	if((*pretanv)[i][j] > (*max0)){
             		(*max0) = (*pretanv)[i][j] ;
             	}
             }else{
             	(*nr1)++;
             	if((*pretanv)[i][j] > (*max1)){
             		(*max1) = (*pretanv)[i][j] ;
             	}
             }

             
         }
     }

}

int main(int argc, char *argv[]){

	const char* nrani = argv[1];
	char* fisin = argv[2];
	char* fisout = argv[3];
	int Pmin,Pmax,n;
	int **tinut,**preturi,**bugete;
	int **pretanv,**bugeteanv,**tinutanv;
	
	const int nra = atoi(nrani);
	
	readFromfile(fisin,&Pmin,&Pmax,&n,&tinut,&preturi,&bugete);
	
	pretanv = (int **) malloc(n*sizeof(int *));
	bugeteanv = (int **) malloc(n*sizeof(int *));
	tinutanv = (int **)malloc(n*sizeof(int*));
	int i,j;
    	for(i = 0; i < n; i++){
		pretanv[i] = (int *) malloc( n * sizeof(int));
		bugeteanv[i] = (int *) malloc( n * sizeof(int));
		tinutanv[i] = (int *) malloc(n * sizeof(int));
	}

	int iter = 0;
	int retinute[nra*6];
	FILE *fp = fopen(fisout,"w");
	
	while(iter < nra)
	{
             int nr0 = 0, nr1 = 0,max1 = -1,max0 = -1;
             
 	     activitatianuale(n,Pmin,Pmax,tinut,preturi,bugete,
 	     		&pretanv,&bugeteanv,&tinutanv,&nr0,&nr1,&max0,&max1);
        
        
         for(i = 0; i < n; i++){
                   memcpy(tinut[i],tinutanv[i],n*sizeof(int));
                   memcpy(bugete[i],bugeteanv[i],n*sizeof(int));
                   memcpy(preturi[i],pretanv[i],n*sizeof(int));
         }
         
	retinute[iter*4] = nr0;
	retinute[iter*4 + 1] = max0;
	retinute[iter*4 + 2] = nr1;
	retinute[iter*4 + 3] = max1;
        iter ++;
    }
    
    for(i = 0; i < nra ; i++){
    	
         fprintf(fp,"%i %i %i %i\n",retinute[i*4],retinute[i*4+1],retinute[i*4+2],retinute[i*4+3]);
    }
    
    for(i = 0; i < n; i++){
          for(j = 0; j < n; j++)
                fprintf(fp,"(%i,%i,%i) ",tinut[i][j],preturi[i][j],bugete[i][j]);
          fprintf(fp,"\n");
    }
    
}
