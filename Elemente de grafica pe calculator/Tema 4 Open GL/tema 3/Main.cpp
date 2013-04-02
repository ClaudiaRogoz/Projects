//include librarii de opengl, glut si glu
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

//includes
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <math.h>
#include <time.h>
//glut and glew
#include "glut.h"

//ground
#include "ground.h"
#include "TargaImage.h"
//camera
#include "camera.h"
//Cub
#include "Cub.h"
#include "Labirint.h"


using namespace std;
TargaImage *m_textureOne;
unsigned int m_textureObjectOne;
	// componente material
GLfloat diffuse4f [] = {0.0, 0.0, 0.0, 1.0};
GLfloat ambient4f [] = {210/255.0,105/255.0,30/255.0,1.0};
GLfloat ambient4f1 [] = {163.0/255, 188.0/255, 73.0/255,1.0};
GLfloat ambient4f2 [] = {128.0/255, 58.0/255, 203.0/255,1.0};
GLfloat ambient4f3 [] = {117.0/255, 222.0/255, 12.0/255,1.0};
GLfloat ambient4f4 [] = {248.0/255, 152.0/255, 238.0/255,1.0};
GLfloat ambient4f5 [] = {1.0f,1.0f,0.0f};
GLfloat ambient4f6 [] = {0.0f,0.0f,0.0f};

GLfloat specular4f [] = {1.0, 1.0, 1.0, 1.0};
GLfloat shininess = 64.0;
	
	// componente lumina
	// position = x,y,z,w -> w = 0 lumina omnidirectionala pozitionata la infinit; w = 1 lumina directionala la care poate fi setat spotul
GLfloat position4f [] = {1.0, 1.0, 0.5, 0.0};
GLfloat color4f [] = {1.0, 1.0, 1.0, 1.0};
static int tor;
//cam
Camera camera;
Camera camerasec;
float xpos = 0, ypos = 0, zpos = 0 ;
Labirint *l;
//cuburi
float angle = 0, myAngle = 0.1, sumAngle = 0, myDist = 1, sndDist = 1, sndsum = 0, sum = 0, finalangle = 1;
bool gor = true, gorb = false, gol = false, golb = false, gof = false, turn = false, gofb = false;
//char labirint[20][20];
int nrlinii,nrcoloane;
int hand = 0;
int cam = 1;
float totalangle = 0.0f;
char** labirint;
bool colision = false;
Cub *c ;
float R = 0.3f;
vector<Cub *> cuburi;
bool shoot = false;
float shootangle = 0.0f;
float bullettranslate = 0.0f;
Vector3D shootposition ;
Vector3D position = Vector3D(-0.5f,0.0f,1.0f);
bool cubshoot = false,draw = true;
vector<int> distruse;
float total3rdangle = 0.0f;
bool shootbonus = false, nocolbonus = false;
int timebonus = 1200;
int timespent;
bool CubeIntSphere(Vector3D C1, Vector3D C2, Vector3D sphere,float R){
	float dist_squared = R*R;
	
	if(sphere.x < C1.x) dist_squared -= sqrt(sphere.x - C1.x);
	else if(sphere.x > C2.x) dist_squared -= sqrt(sphere.x - C2.x);
	
	if(sphere.y < C1.y) dist_squared -= sqrt(sphere.y - C1.y);
	else if(sphere.y > C2.y) dist_squared -= sqrt(sphere.y - C2.y);
	

	if(sphere.z < C1.z) dist_squared -= sqrt(sphere.z - C1.z);
	else if(sphere.z > C2.z) dist_squared -= sqrt(sphere.z - C2.z);
	return dist_squared > 0;

}

bool SphereIntSphere(Vector3D s1,Vector3D s2,float R1,float R2){
	float distance = sqrt(pow((s1.x - s2.x),2) + pow((s1.y - s2.y),2) + pow((s1.z -s2.z),2));
	return distance < (R1 + R2);
}


bool CollisionLabirint(Vector3D sphere, float R){
	
	
	for(int i = 0; i < cuburi.size(); i++){
		Cub * cub = cuburi.at(i);
		if(CubeIntSphere(cub->C1(),cub->C2(),sphere,R)){
			
			return true;
		}
	}

	return false;
	
}

bool CollisionShoot(Vector3D sphere, float R,int * ind){
	
	
	for(int i = 0; i < cuburi.size(); i++){
		Cub * cub = cuburi.at(i);
		if(CubeIntSphere(cub->C1(),cub->C2(),sphere,R)){
			
			*ind = cub->ind;
			return true;
		}
	}
	
	return false;
	
}



void inittextures(){

	glClearColor(0.0, 0.0, 0.0, 0.0);
	const GLfloat globalAmbientColor4f [] = {0.2, 0.2, 0.2, 1.0};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor4f);
	
	glEnable(GL_DEPTH_TEST);	// pornire depth test
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);	// model iluminare

	// setare parametrii lumina 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, color4f);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, color4f);
	glLightfv(GL_LIGHT0, GL_POSITION, position4f);

	glEnable(GL_LIGHT0); // pornire lumina 0

	// enable 2D texturing
	glEnable(GL_TEXTURE_2D);

	m_textureOne = new TargaImage;
	
	// load texture image data
	m_textureOne->Load("rock.tga");
	
	// retrieve "unused" texture object
	glGenTextures(1, &m_textureObjectOne);

	// bind the texture object
	glBindTexture(GL_TEXTURE_2D, m_textureObjectOne);

	// minimum required to set the min and mag texture filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// now that the texture object is bound, specify a texture for it
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_textureOne->GetWidth(), m_textureOne->GetHeight(),
				 0, GL_RGB, GL_UNSIGNED_BYTE, m_textureOne->GetImage());
	
	glBindTexture(GL_TEXTURE_2D, m_textureObjectOne);
	//glDeleteTextures(1, &m_textureObjectOne);
	m_textureOne->Release();
	delete m_textureOne;
	
	glutSetCursor(GLUT_CURSOR_NONE);
	


}

static int bonuspos1,bonuspos2;
//functie afisare
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//setup view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse4f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient4f1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular4f);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	if(cam == 1){
		gluLookAt(0, 44, 0, 0, 1.0, 0, 0, 0, -1);
	}else{
		if(cam == 2){
			camera.render(position);
		}else if(cam == 3){

			float x1 =0*cos((-total3rdangle)) - 2*sin((-total3rdangle));
			float z1 =0*sin((-total3rdangle)) + 2*cos((-total3rdangle));
			camerasec.render(Vector3D(position.x+x1,position.y+3,position.z+z1+1), position);
		
		}
	}
		
		////ground
		glColor3f(185.0/255, 122.0/255, 87.0/255);
		draw_ground(2*nrcoloane,2*nrlinii, 2, 2, -1);
		// desenam labirintul
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse4f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient4f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular4f);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
		//glColor3f(1.0f,1.0f,0.0f);
		Labirint *l = new Labirint(nrcoloane,nrlinii,-13.0f,-15.0f,labirint,distruse,tor);
		l->DrawLabirint();
		cuburi = l->cuburi;
		//if(!cubshoot){
		//	glPushMatrix();
		//		glColor3f(1.0f,1.0f,0.0f);
		//		c = new Cub(0.0f,0.0f,-8.0f,1.0f,1.0f);
		//		c->DrawCub();
		//	glPopMatrix();
		//}
		
	
	bonuspos1 = 2561 % (l->emptyspace.size() -1) ;
	//draw sphere that give you power to shoot 
	if(!shootbonus){
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse4f);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient4f5);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular4f);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
			Vector3D pos = l->emptyspace.at(bonuspos1);
			glTranslatef(pos.x,pos.y,pos.z);
			glutSolidSphere(0.3,20,20);
		glPopMatrix();

		if(SphereIntSphere(pos,position,R,0.3)){
			shootbonus = true;
			timespent = 0;
			cout<<"shoot"<<shoot<<"\n";
		}

	}else{
		timespent ++;
		if(timespent > timebonus){
			shootbonus = false;
		}
	}

	bonuspos2 = 4735 % (l->emptyspace.size() -1) ;
	// no colision bonus
	if(!nocolbonus){
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse4f);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient4f6);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular4f);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

			Vector3D pos = l->emptyspace.at(bonuspos2);
			glTranslatef(pos.x,pos.y,pos.z);
			glutSolidSphere(0.3,20,20);
		glPopMatrix();

		if(SphereIntSphere(pos,position,R,0.3)){
			nocolbonus = true;
			timespent = 0;
			
		}
	}else{
		timespent ++;
		if(timespent > timebonus){
			nocolbonus = false;
		}
	}

	if(cam == 3){
		if(draw){
			glPushMatrix();
			
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse4f);
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient4f2);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular4f);
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
				
				glTranslatef(position.x,position.y ,position.z);
				glRotatef(totalangle,0.0f,1.0f,0.0f);
				glPushMatrix();
					glColor3f(1.0f,0.0f,0.0f);
					glRotatef(180,1.0f,0.0f,0.0f);
					glTranslatef(0.0f,0.0f,R);
					
					glutSolidCone(R+0.1f,R,20,20);
				glPopMatrix();
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse4f);
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient4f3);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular4f);
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
				glutSolidSphere(R,20,20);
			
			glPopMatrix();
		}
	}else if(cam == 1){
		if(draw){
			glPushMatrix();
			glTranslatef(position.x,position.y ,position.z);
			glRotatef(totalangle,0.0f,1.0f,0.0f);
			
			glPushMatrix();
				
				glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse4f);
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient4f2);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular4f);
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
				
				glRotatef(180,1.0f,0.0f,0.0f);
				glTranslatef(0.0f,0.0f,R);
				glutSolidCone(R,2*R,20,20);
			glPopMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse4f);
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient4f3);
				glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular4f);
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
			glutSolidSphere(R,20,20);
			glPopMatrix();
		}
	}
	
	if(shoot && draw && shootbonus){
		bullettranslate+=0.1f;
		float x1 =0*cos((-shootangle)*3.1415f/180.0) - bullettranslate*sin((-shootangle)*3.1415f/180.0);
		float z1 =0*sin((-shootangle)*3.1415f/180.0) + bullettranslate*cos((-shootangle)*3.1415f/180.0);

		glTranslatef(shootposition.x - x1 ,shootposition.y,shootposition.z - z1);
		glRotatef(totalangle,0.0f,1.0f,0.0f);
		glPushMatrix();
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse4f);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient4f4);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular4f);
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
			glutSolidSphere(0.3f,20,20);
		glPopMatrix();
		if(bullettranslate > 25.0f){
			shoot = false;
		}
		int ind ;
		if(CollisionShoot(Vector3D(shootposition.x - x1 ,shootposition.y,shootposition.z - z1),0.3f,&ind)){
			
			shoot = false;
			cubshoot = true;
			bullettranslate = 0.0f;
			shootangle = 0.0f;
			distruse.push_back(ind);
			
		}

	}

	if(SphereIntSphere(position,l->torpoz,R,0.4)){
		draw = false;
	}
	

	//swap buffers
	glutSwapBuffers();
}



void reshape(int width, int height){
	//set viewport
	glViewport(0,0,width,height);
	
	//set proiectie
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective(45, (float)width/(float)height, 0.2, 100);
}


void idle();

void onKey(unsigned char key){
	Vector3D aux ,aux1;
	float z1,x1;
	float ang;
	switch(key){
		case 'w':
			x1 =0*cos(-totalangle) - sndDist*sin((-totalangle)*3.1415f/180.0);
			z1 =0*sin(-totalangle) + sndDist*cos((-totalangle)*3.1415f/180.0);
			aux = Vector3D(position.x - x1,position.y,position.z - z1);
			if(!CollisionLabirint(aux,2*R) ){
					position = aux;
			}else if(nocolbonus){
				position = aux;
			}
			break;
		case 's':
			x1 = 0*cos(-totalangle)  - sndDist*sin((-totalangle)*3.1415f/180.0);
			z1 = 0*sin(-totalangle) + sndDist*cos((-totalangle)*3.1415f/180.0);
			aux = Vector3D(position.x + x1, position.y,position.z + z1 );
			if(!CollisionLabirint(aux,2*R)){
					position = aux;
			}else if(nocolbonus){
				position = aux;
			}
			break;
		case 'a':
			
			if(!CollisionLabirint(position,2*R)){
					ang = ((myAngle)*180.0)/3.1415f;
					totalangle += ang;
					camera.rotateFPS_OY(-myAngle);	
			}else if(nocolbonus){
					ang = ((myAngle)*180.0)/3.1415f;
					totalangle += ang;
					camera.rotateFPS_OY(-myAngle);	
			}
			break;
		case 'd':
			
			if(!CollisionLabirint(position,2*R)){
					ang = ((-myAngle)*180.0)/3.1415f;
					totalangle += ang;
					camera.rotateFPS_OY(myAngle);	
			}else if(nocolbonus){
					ang = ((-myAngle)*180.0)/3.1415f;
					totalangle += ang;
					camera.rotateFPS_OY(myAngle);	
			}
			break;
		case '4':
			
			ang = myAngle;
			total3rdangle += ang;
			camerasec.rotateFPS_OY(myAngle);
			
			break;
		case '6':
			
			ang = -myAngle;
			total3rdangle += ang;
			camerasec.rotateFPS_OY(myAngle);
			break;
		case ' ':
			shoot = true;
			shootangle = totalangle;
			shootposition = position;
			break;
		case '1':
			cam = 1;
			break;
		case '2':
			cam = 2;
			
			break;
		case '3':
			cam = 3;
			break;
		default:
			break;
	}

}

void keyboard(unsigned char ch, int x, int y){
	switch(ch){
		case 27:
			exit(0);
			break;
		default:
			break;
	}
	onKey(ch);
	
}

void mouse(int button, int state, int x, int y){
	
	if(button == GLUT_LEFT_BUTTON){
		
	
			
	}
	
}
void mousemovement(int x,int y){
	
	glutWarpPointer(600 / 2, 500 / 2);
	
	
}

//idle
void idle(){
	angle = angle + 0.01;
	if(angle > 360) 
		angle = angle - 360;
	
	
	glutPostRedisplay();
}



void read(char* name){
	FILE *file = fopen(name, "r");
	if(file == NULL)
		return;

	fscanf(file,"%i\n",&nrlinii);
	fscanf(file,"%i\n",&nrcoloane);
	labirint = (char**) malloc(nrlinii*sizeof(char *));
	for(int i = 0; i < nrlinii; i++){
		labirint[i] = (char*) malloc(nrcoloane * sizeof(char));
	}

	for(int i = 0; i < nrlinii; i++){
		for(int j = 0; j < nrcoloane; j++){
			fscanf(file,"%c",&labirint[i][j]);
		}
		fscanf(file,"\n");
	}

	

}



int main(int argc, char *argv[]){
	read("labirint.txt");

	srand(time(NULL));
	tor = rand() % 40;
	//init glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	//init window
	glutInitWindowSize(600,500);
	glutInitWindowPosition(100,100);
	glutCreateWindow("Labirint");
	inittextures();
	//callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	//glutPassiveMotionFunc(mousemovement);
	glutIdleFunc(idle);


	//z test on
	glEnable(GL_DEPTH_TEST);

	//set background
	glClearColor(0.2,0.2,0.2,1.0);

	//init camera
	camera.init();
	camerasec.init();
	//loop
	glutMainLoop();

	return 0;
}