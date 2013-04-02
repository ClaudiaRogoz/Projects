#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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

int min4(int a,int b,int c,int d){
	int min = a;
	if(min > b){
		min = b;
	}
	if(min > c){

			min = c;
	
	}
		
	if(min > d){
				min = d;
	}
	return min;
	
}


void activitatianuale(int n,int Pmin,int Pmax,int** tinut, int** preturi,int ** bugete,
		int *** pretanv,int*** bugeteanv,int*** tinutanv,int* nr0,int* nr1,int* max0,int* max1){
	
	int i,j,k,l;
	float f  = 0;
	int vsc01[n][n],vsc02[n][n],vsc03[n][n],vsc04[n][n];
	int vsc11[n][n],vsc12[n][n],vsc13[n][n],vsc14[n][n];
    
    for(i = 0; i < n ; i++){
    	for(j = 0; j < n; j++){
    		if(tinut[i][j] == 0){
    			vsc01[i][j] = preturi[i][j];
    			vsc11[i][j] = 1000000;
    			vsc02[i][j] = preturi[i][j];
    			vsc12[i][j] = 1000000;
    			vsc03[i][j] = preturi[i][j];
    			vsc13[i][j] = 1000000;
    			vsc04[i][j] = preturi[i][j];
    			vsc14[i][j] = 1000000;
    		}else{
    			vsc01[i][j] = 1000000;
    			vsc11[i][j] = preturi[i][j];
    			vsc02[i][j] = 1000000;
    			vsc12[i][j] = preturi[i][j];
    			vsc03[i][j] = 1000000;
    			vsc13[i][j] = preturi[i][j];
    			vsc04[i][j] = 1000000;
    			vsc14[i][j] = preturi[i][j];
    		}
    	}
    }
	
    for(i = 0; i < n ; i++){
    	for(j = 0; j < n; j++){
    		
    		int min = vsc01[i][j];
    		// vreau sa cumpar 0 primul colt prima matrice stanga sus 
    		if(i-1 >= 0){
    			if(min > vsc01[i-1][j]){
    			
    				min = vsc01[i-1][j] + 1;
    				
    			}
    		}
    		
    		if(j-1 >=0){
    			if(min > vsc01[i][j-1]){
    				min = vsc01[i][j-1] + 1;
    			}
    		}
    		vsc01[i][j] = min;
    		
    		// vreau sa cumpar 1 primult colt 
    		min = vsc11[i][j];
    		if(i-1 >= 0){
    			if(min > vsc11[i-1][j] ){
    			
    				min = vsc11[i-1][j] + 1;
    				
    			}
    		}
    		if(j-1 >=0){
    			if(min > vsc11[i][j-1]){
    				min = vsc11[i][j-1] + 1;
    			}
    		}
    		vsc11[i][j] = min;
    		
    		
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			int o = n - i - 1, p = j;
			min = vsc02[o][p];
    		// vreau sa cumpar 0 colt 2 dreapta sus
    		if(o+1 < n){
    			if(min > vsc02[o+1][j]){
    			
    				min = vsc02[o+1][j] + 1;
    				
    			}
    		}
    		if(j-1 >=0){
    			if(min > vsc02[o][j-1]){
    				min = vsc02[o][j-1] + 1;
    			}
    		}
    		vsc02[o][j] = min;
    		
    		// vreau sa cumpar 1 colt 1 dreapta sus 
    		min = vsc12[o][j];
    		if(o+1 < n){
    			if(min > vsc12[o+1][j]){
    			
    				min = vsc12[o+1][j] + 1;
    				
    			}
    		}
    		if(j-1 >=0){
    			if(min > vsc12[o][j-1] ){
    				min = vsc12[o][j-1] + 1;
    			}
    		}
    		vsc12[o][j] = min;


//+++++++++++++++++++++++++++++++++++++++++++====

			int p1 = n - j - 1;
			min = vsc03[i][p1];
    		// vreau sa cumpar 0 primul colt prima matrice stanga jos
    		if(i-1 >= 0){
    			if(min > vsc03[i-1][p1]){
    			
    				min = vsc03[i-1][p1] + 1;
    				
    			}
    		}
    		if(p1+1 < n){
    			if(min > vsc03[i][p1+1] ){
    				min = vsc03[i][p1+1] + 1;
    			}
    		}
    		vsc03[i][p1] = min;
    		
    		// vreau sa cumpar 1 stanga jos
    		min = vsc13[i][p1];
    		if(i-1 >= 0){
    			if(min > vsc13[i-1][p1]){
    			
    				min = vsc13[i-1][p1] + 1;
    				
    			}
    		}
    		
    		if(p1+1 < n){
    			if(min > vsc13[i][p1+1]){
    				min = vsc13[i][p1+1] + 1;
    			}
    		}
    		
    		vsc13[i][p1] = min;   
    		
//++++++++++++++++++++++++++++++++++++++++++++++++++
			int o2 = n - i -1; int p2 = n - j - 1;
			min = vsc04[o2][p2];
    		// vreau sa cumpar 0 primul colt prima matrice stanga jos
    		if(o2+1 < n){
    			if(min > vsc04[o2+1][p2]){
    			
    				min = vsc04[o2+1][p2] + 1;
    				
    			}
    		}
    		if(p2+1 < n){
    			if(min > vsc04[o2][p2+1]){
    				min = vsc04[o2][p2+1] + 1;
    			}
    		}
    		vsc04[o2][p2] = min;
    		
    		// vreau sa cumpar 1 stanga jos
    		min = vsc14[o2][p2];
    		if(o2+1 < n){
    			if(min > vsc14[o2+1][p2]){
    			
    				min = vsc14[o2+1][p2] + 1;
    				
    			}
    		}
    		
    		if(p2+1 < n){
    			if(min > vsc14[o2][p2+1]){
    				min = vsc14[o2][p2+1] + 1;
    			}
    		}
    		
    		vsc14[o2][p2] = min;   
 		

    	}
    }

    	
	
	for(i = 0; i < n; i++)
    	{
		for(j = 0; j < n; j++)
        	{
        	vsc01[i][j] = min4(vsc01[i][j],vsc02[i][j],vsc03[i][j],vsc04[i][j]);
    		vsc11[i][j] = min4(vsc11[i][j],vsc12[i][j],vsc13[i][j],vsc14[i][j]);
    		
    		
        		int pretmincomp,pretres;
				if(tinut[i][j] == 0){
					pretmincomp = vsc11[i][j];
					pretres = vsc01[i][j];
				}else{
					pretmincomp = vsc01[i][j];
					pretres = vsc11[i][j];
				}
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

