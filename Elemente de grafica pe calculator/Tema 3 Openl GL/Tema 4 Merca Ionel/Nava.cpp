#include "Nava.h"
#include <iostream>

Nava::Nava(){

	string file = "nava.off";
	Nava::nava = new LoadOFF(file);
	trans = 0.3f;
	health = 1;
}

Nava::~Nava(){
	delete nava;
}

void Nava::render(Vector3D * mypos,int deseneaza){
	
	std::cout<<trans<<endl;

	glPushMatrix();
			glPushMatrix();
				glTranslatef(1.0f,-0.2f,-0.7f);
				glTranslatef(mypos->x,mypos->y,mypos->z);
				glScalef(2.0f, 2.0f, 2.0f);
				glRotatef(-90.0f,0.0f,1.0f,0.0f);
			nava->render();
			glPopMatrix();
			glDisable(GL_DEPTH_TEST);
			GLfloat material_ambient2[] = { 0.5f, 0.0f, 0.6f, trans };
			GLfloat material_diffuse2[] = { 0.5f, .0f, 0.5f, trans };
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient2);
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse2);
			glMaterialfv(GL_FRONT,GL_SPECULAR, material_ambient2);
			glPushMatrix();
				glEnable(GL_BLEND);
				glAlphaFunc(GL_LESS, 1);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				
				glTranslatef(mypos->x,mypos->y,mypos->z);
				glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
				glutSolidSphere(2,20,20);
				glDisable(GL_BLEND);
			glPopMatrix();
			glEnable(GL_DEPTH_TEST);
			

	glPopMatrix();
	

}
