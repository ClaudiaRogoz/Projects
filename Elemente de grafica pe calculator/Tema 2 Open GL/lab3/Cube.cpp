#include "Cube.h"

Cube::Cube(Layer layer1,Layer layer2,Layer layer3,GLfloat trax,GLfloat tray,GLfloat traz){
	Cube::layer3 = layer3;
	Cube::layer1 = layer1;
	Cube::layer2 = layer2;
	Cube::trax = trax;
	Cube::tray = tray;
	Cube::traz = traz;


}

Cube::~Cube(){
	
}

int Cube::retnrLayer(Layer l){
	
	if(l == L_L1) return 0;
	if(l == L_L2) return 1;
	if(l == L_L3) return 2;
	if(l == L_D1) return 3;
	if(l == L_D2) return 4;
	if(l == L_D3) return 5;
	if(l == L_F1) return 6;
	if(l == L_F2) return 7;
	if(l == L_F3) return 8;
}
void Cube::Draw(GLfloat size, int tip){

	if(tip == 0)
		DrawCube(size);
	else 
		DrawCubeT(size);


}

void Cube::DrawCube(GLfloat size){	
	glBegin(GL_QUADS);
		glColor3f(230/256.0, 13/256.0, 34/256.0);
		glVertex3f( -1*size, -1*size, -1*size);       
		glVertex3f( -1*size,  1*size, -1*size);      
		glVertex3f(  1*size,  1*size, -1*size);      
		glVertex3f(  1*size, -1*size, -1*size);   

		glColor3f(42/256.0,196/256.0,75/256.0);
		glVertex3f(  1*size, -1*size, 1*size );
		glVertex3f(  1*size,  1*size, 1*size );
		glVertex3f( -1*size,  1*size, 1*size );
		glVertex3f( -1*size, -1*size, 1*size );

		glColor3f(52/256.0, 70/256.0, 146/256.0);
		glVertex3f( 1*size, -1*size, -1*size );
		glVertex3f( 1*size,  1*size, -1*size );
		glVertex3f( 1*size,  1*size,  1*size );
		glVertex3f( 1*size, -1*size,  1*size );
 
	
		glColor3f(204/256.0, 77/256.0,39/256.0);
		glVertex3f( -1*size, -1*size,  1*size );
		glVertex3f( -1*size,  1*size,  1*size );
		glVertex3f( -1*size,  1*size, -1*size );
		glVertex3f( -1*size, -1*size, -1*size );
	

		glColor3f(255/256.0, 255/256.0, 37/256.0);
		glVertex3f(  1*size,  1*size,  1*size );
		glVertex3f(  1*size,  1*size, -1*size );
		glVertex3f( -1*size,  1*size, -1*size );
		glVertex3f( -1*size,  1*size,  1*size );

 


		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(  1*size, -1*size, -1*size );
		glVertex3f(  1*size, -1*size,  1*size );
		glVertex3f( -1*size, -1*size,  1*size );
		glVertex3f( -1*size, -1*size, -1*size );


	glEnd();
	glFlush();
}



void Cube::DrawCubeT(GLfloat size){	
		
	glBegin(GL_QUADS);

		glColor3f(210/256.0, 15/256.0, 15/256.0);
		glVertex3f( -1*size, -1*size, -1*size);       // P1
		glVertex3f( -1*size,  1*size, -1*size);       // P2
		glVertex3f(  1*size,  1*size, -1*size);       // P3
		glVertex3f(  1*size, -1*size, -1*size);       // P4

		
		glColor3f(33/256.0,154/256.0,61/256.0);
		glVertex3f(  1*size, -1*size, 1*size );
		glVertex3f(  1*size,  1*size, 1*size );
		glVertex3f( -1*size,  1*size, 1*size );
		glVertex3f( -1*size, -1*size, 1*size );

 
		
		glColor3f(27/256.0, 66/256.0, 203/256.0);
		glVertex3f( 1*size, -1*size, -1*size );
		glVertex3f( 1*size,  1*size, -1*size );
		glVertex3f( 1*size,  1*size,  1*size );
		glVertex3f( 1*size, -1*size,  1*size );
 
		
		glColor3f(173/256.0, 65/256.0,33/256.0);
		glVertex3f( -1*size, -1*size,  1*size );
		glVertex3f( -1*size,  1*size,  1*size );
		glVertex3f( -1*size,  1*size, -1*size );
		glVertex3f( -1*size, -1*size, -1*size );
	
		
		glColor3f(223/256.0, 223/256.0, 0/256.0);
		glVertex3f(  1*size,  1*size,  1*size );
		glVertex3f(  1*size,  1*size, -1*size );
		glVertex3f( -1*size,  1*size, -1*size );
		glVertex3f( -1*size,  1*size,  1*size );

 
		

		glColor3f(207/256.0, 207/256.0, 207/256.0);
		glVertex3f(  1*size, -1*size, -1*size );
		glVertex3f(  1*size, -1*size,  1*size );
		glVertex3f( -1*size, -1*size,  1*size );
		glVertex3f( -1*size, -1*size, -1*size );


	glEnd();
	glFlush();
}

void Cube::Rubik(GLfloat size){
	//gluLookAt(0,0,0,0,0,0,0,1,0);
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			for(int k = 0; k < 3; k++){
				glPushMatrix();
				glTranslatef(2*i*size + i*0.1f, 2*j*size + j*0.1f, 2*k*size + k*0.1f);
				DrawCube(size);
				glPopMatrix();
			}
		}
	}

}