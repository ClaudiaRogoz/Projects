#include "Cub.h"



Cub::Cub(GLfloat trax,GLfloat tray,GLfloat traz,float size,int ind){
	
	this->trax = trax;
	this->tray = tray;
	this->traz = traz;
	this->size = size;
	this->ind = ind;
	

	
}

Cub::~Cub(){

}



void Cub::init(){

}

Vector3D Cub::C1(){
	return Vector3D(-1*size + trax, -1*size + tray, -1 * size + traz);
}
 
Vector3D Cub::C2(){
	return Vector3D(size + trax, size + tray,  1*size + traz);
}


void Cub::DrawCub(){

	glTranslatef(trax,tray,traz);
		glBegin(GL_QUADS);
		glColor3f(210/255.0,105/255.0,30/255.0);
		glNormal3f(0.0f,0.0f,-1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f( -1*size, -1*size, -1*size);       // P1
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f( -1*size,  1*size, -1*size);       // P2
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(  1*size,  1*size, -1*size);       // P3
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(  1*size, -1*size, -1*size);       // P4

		glNormal3f(0.0f,0.0f,1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(  1*size, -1*size, 1*size );
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(  1*size,  1*size, 1*size );
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f( -1*size,  1*size, 1*size );
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f( -1*size, -1*size, 1*size );

		glNormal3f(1.0f,0.0f,0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f( 1*size, -1*size, -1*size );
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f( 1*size,  1*size, -1*size );
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f( 1*size,  1*size,  1*size );
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f( 1*size, -1*size,  1*size );
		
		glNormal3f(-1.0f,0.0f,0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f( -1*size, -1*size,  1*size );
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f( -1*size,  1*size,  1*size );
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f( -1*size,  1*size, -1*size );
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f( -1*size, -1*size, -1*size );
	
		glNormal3f(0.0f,1.0f,0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(  1*size,  1*size,  1*size );
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(  1*size,  1*size, -1*size );
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f( -1*size,  1*size, -1*size );
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f( -1*size,  1*size,  1*size );

		glNormal3f(0.0f,-1.0f,0.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(  1*size, -1*size, -1*size );
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(  1*size, -1*size,  1*size );
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f( -1*size, -1*size,  1*size );
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f( -1*size, -1*size, -1*size );

		
	glEnd();
	
	glFlush();
	
}
void Cub::DrawCubU(){

	
	glTranslatef(trax,tray,traz);
		glBegin(GL_QUADS);
	
		glVertex3f( -1*size, -1*size, -1*size);       // P
		glVertex3f( -1*size,  1*size, -1*size);       // P2
		glVertex3f(  1*size,  1*size, -1*size);       // P3
		glVertex3f(  1*size, -1*size, -1*size);       // P4

		
		glVertex3f(  1*size, -1*size, 1*size );
		glVertex3f(  1*size,  1*size, 1*size );
		glVertex3f( -1*size,  1*size, 1*size );
		glVertex3f( -1*size, -1*size, 1*size );

	
		glVertex3f( 1*size, -1*size, -1*size );
		glVertex3f( 1*size,  1*size, -1*size );
		glVertex3f( 1*size,  1*size,  1*size );
		glVertex3f( 1*size, -1*size,  1*size );
		
		
		glVertex3f( -1*size, -1*size,  1*size );
		glVertex3f( -1*size,  1*size,  1*size );
		glVertex3f( -1*size,  1*size, -1*size );
		glVertex3f( -1*size, -1*size, -1*size );
	

		glVertex3f(  1*size,  1*size,  1*size );
		glVertex3f(  1*size,  1*size, -1*size );
		glVertex3f( -1*size,  1*size, -1*size );
		glVertex3f( -1*size,  1*size,  1*size );


		glVertex3f(  1*size, -1*size, -1*size );
		glVertex3f(  1*size, -1*size,  1*size );
		glVertex3f( -1*size, -1*size,  1*size );
		glVertex3f( -1*size, -1*size, -1*size );

		
	glEnd();
	
	glFlush();
	
}
