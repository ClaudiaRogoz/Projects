#include <stdio.h>
#include "Complex.h"
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "mpi.h"

using namespace std;

// functie de citire din fisier 
int readfromfile(char * fisin,int* type,double * xmin,double * xmax,
		double * ymin,double * ymax,double * resolution,int* maxsteps,double * compp1,double *compp2){
	int tip,max;
	double  xmi,xma,ymi,yma,res,comp1,comp2;
	
	FILE* f = fopen(fisin,"r");
	
	if(f==NULL){
		return 0;
	}
	
	fscanf(f,"%i\n%lf %lf %lf %lf\n%lf\n%i",type,xmin,xmax,ymin,ymax,resolution,maxsteps);

	
	if(*type == 1){
		fscanf(f,"%lf %lf",compp1,compp2);
		
	}
	
	
	fclose(f);
	
	
	return 1;
	
}



void writePGM(char * fisout,int**matrix,int height, int width){

	FILE* f = fopen(fisout,"w");
	
	fprintf(f,"P2\n%i %i\n255\n",width,height);
	for(int i = height - 1; i >= 0 ;i--){
		for(int j = 0; j < width ; j++){
			fprintf(f,"%i ",matrix[i][j]);
			
		}
		fprintf(f,"\n");
	}
	fclose(f);
}


void Mandelbrot(double  xmin,double  xmax,double  ymin,double  ymax, double  resolution,int maxsteps,
		int* matrix,int height,int width,int lines,int rank,int notask){
	
	int i = rank * lines,j = 0;
	double  x = xmin;
	double  y = ymin + resolution*rank*lines;
	int k = 0;
	Complex *c,*z;
	if(rank!= notask-1){
		while(i < (rank*lines + lines)){
			x = xmin;
			j = 0;
			
			while(j < width){
				
				c = new Complex(x,y);
				z = new Complex(0,0);
				int step = 0;
			
				while( z->modul() < 4 && step < maxsteps){
				
					z->inmultire(z);
					z->plus(c);
					step++;
				
				}
				int color = step % 256;
				matrix[k] = color;
				x += resolution;
				j++;
				k++;
			}
			y+= resolution;
			i++;
		}
	}else{
		while(i < height){
			x = xmin;
			j = 0;
			
			while(j < width){
				
				c = new Complex(x,y);
				z = new Complex(0,0);
				int step = 0;
			
				while( z->modul() < 4 && step < maxsteps){
				
					z->inmultire(z);
					z->plus(c);
					step++;
				
				}
				int color = step % 256;
				matrix[k] = color;
				x += resolution;
				j++;
				k++;
			}
			y+= resolution;
			i++;
		}
	}
//	cout<<"Si am scris aici in Mandelbrot "<<k <<" chestii\n";
	
}


void Julia(double  xmin,double  xmax,double  ymin,double  ymax, double  resolution,
		int maxsteps,int* matrix,int height,int width,double  compp1,double  compp2,int lines,int rank,int notask){
	
	int i = rank * lines,j = 0;
	double  x = xmin;
	double  y = ymin + resolution*rank*lines;
//	cout<<"Am aici commp1 si compp2"<<compp1<<" "<<compp2<<"\n";	
	Complex *c = new Complex(compp1,compp2);
//	cout<<"\t Julia sunt in threadul"<<rank<<"si am x de inceput: "<<x<<" si y de inceput "<<y<<"\n";
	
	Complex *z;
	int k = 0;
	if(rank != notask -1){
		while(i < (rank*lines + lines)){
			x = xmin;
			j = 0;
		
			while(j < width){
			
			
				z = new Complex(x,y);
				int step = 0;
			
				while( z->modul() < 4 && step < maxsteps){
					z->inmultire(z);
					z->plus(c);
					step++;
				}
				int color = step % 256;
				matrix[k] = color;
				x += resolution;
				j++;
				k++;
			
			}
			y+= resolution;
			i++;
		}
	}else{
		while(i < height){
			x = xmin;
			j = 0;
		
			while(j < width){
			
			
				z = new Complex(x,y);
				int step = 0;
			
				while( z->modul() < 4 && step < maxsteps){
					z->inmultire(z);
					z->plus(c);
					step++;
				}
				int color = step % 256;
				matrix[k] = color;
				x += resolution;
				j++;
				k++;
			
			}
			
			y+= resolution;
			i++;
		}
	}
//	cout<<"Si am scris aici in Julia "<< k <<" chestii \n";	
}




int main (int argc, char *argv[])
{	
	int noTasks, rank, n = 10;
	int tag = 0;
	int i;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &noTasks);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(rank == 0){
		char* fisin, *fisout;
		if(argc < 3){
			printf("Not proper use, use ./foobar fisin fisout\n");
			return 0;
		}else{
			fisin = argv[1];
			fisout = argv[2];
//			printf("fisin : %s fisout : %s\n",fisin,fisout);
		}
		int tip,maxsteps;
		double  xmin,xmax,ymin,ymax,resolution,compp1,compp2;
	
		if(!readfromfile(fisin,&tip,&xmin,&xmax,&ymin,&ymax,&resolution,&maxsteps,&compp1,&compp2)){
			return 1;
		}
	
		const int width = floor((xmax - xmin)/resolution);
		const int height = floor((ymax - ymin)/ resolution);
	
		int lines = height/(noTasks);
	      	for(int i = 1; i < noTasks; i++){
	      		
	      		double send[12];
	      		send[0] = (double) lines;
	      		send[1] = tip; send[2] = resolution; send[3] = maxsteps;
	      		send[4] = height; send[5] = width;
	      		send[6] = xmin;send[7] = xmax; send[8] = ymin; send[9] = ymax;
	      		
	      		if(tip == 1){
	      			
	      			send[10]=compp1; send[11] = compp2;
	      		
	      		}
	      		// trimitem 
	      		MPI_Send(send, 12, MPI_DOUBLE, i, tag, MPI_COMM_WORLD);	
	      		
	      	}
	      	
	      	
		int **image ;
		image = new int*[height];
	 	for (int i = 0 ; i <height ; i++)
	      		image[i] = new int[width];
	      	int imag[width*height];
	      	if(tip == 0){
	
			Mandelbrot(xmin,xmax,ymin,ymax,resolution,maxsteps,imag,height,width,lines,rank,noTasks);	
	
		}else{
	
			Julia(xmin,xmax,ymin,ymax,resolution,maxsteps,imag,height,width,compp1,compp2,lines,rank,noTasks);
			
		}
		
		for(int i = 0; i < lines;i++){
			for(int j = 0; j < width; j++){
				image[i][j] = imag[i*width+j];
			}
		}
		
		for(int i = 1; i < noTasks; i++){
			int *imagerec ;
			imagerec = new int[width*height];
	      		MPI_Recv(imagerec, width*height, MPI_INT, i, tag, MPI_COMM_WORLD,&status);
//	      		cout<<"Am primit in master de la "<<i<<"\n";
	      		if(i != (noTasks - 1)){
				for(int k = i*lines;k < (i+1)*lines; k++){
	      				for(int j = 0;j < width; j++){
	      					image[k][j] = imagerec[(k - i*lines)*width + j];
	      				}
	      			}
			}else{
				for(int k = (noTasks-1)*lines;k < height; k++){
                        		for(int j = 0;j < width; j++){
                                        	image[k][j] = imagerec[(k - (noTasks-1)*lines)*width + j];
                        		}
                		}

			}
		}
		
//		int *imagerec ;
//		imagerec = new int[width*height];
//	      	MPI_Recv(imagerec, width*height, MPI_INT, (noTasks -1), tag, MPI_COMM_WORLD,&status);
		
//		for(int k = (noTasks-1)*lines;k < height; k++){
//	      		for(int j = 0;j < width; j++){
//	      				image[k][j] = imagerec[(k - (noTasks-1)*lines)*width + j];
//	      		}
//	      	}
		
		writePGM(fisout,image,height,width);
		
      	}else{
      		
      		int tip,maxsteps;
		double  xmin,xmax,ymin,ymax,resolution,compp1,compp2;
		double send[12];
		double xin,xax,yin,yax;
		int imin,imax,jmin,jmax;
		int height, width;
		int lines;
		// primim date de la threadul master
		MPI_Recv(send, 12, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD,&status);
		lines = (int)send[0]; tip = send[1]; resolution = send[2]; maxsteps = send[3];
		height = send[4]; width = send[5]; xmin = send[6]; xmax = send[7]; ymin = send[8]; ymax = send[9];
      		if(tip == 1){
	      			
	      		compp1= send[10]; compp2 = send[11] ;
	      		
	      	}	
      		int imag[width*height];
		if(tip == 0){
	
			Mandelbrot(xmin,xmax,ymin,ymax,resolution,maxsteps,imag,height,width,lines,rank,noTasks);	
	
		}else{
	
			Julia(xmin,xmax,ymin,ymax,resolution,maxsteps,imag,height,width,compp1,compp2,lines,rank,noTasks);
			
		}
		
	//	cout<<"!!!!!!!Am executat algoritmii!!!!!!!!\n";
		MPI_Send(imag, width*height, MPI_INT, 0, tag, MPI_COMM_WORLD);
//		cout<<"Am trimis catre master\n";
		
		
	}
	
	MPI_Finalize();
	return 0;
	
	
	
	
}
