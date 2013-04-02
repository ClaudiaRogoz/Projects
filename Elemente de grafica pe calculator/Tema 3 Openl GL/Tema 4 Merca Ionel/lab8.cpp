// 
// Laborator 8 -- EGC
// 

#include <windows.h>
#include <stdarg.h>
#include <freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#include <iostream>
#include "Cube.h"
#include "Ground.h"
#include "Nava.h"
#include "Camera.h"
#include "Asteroid.h"
// Windows include files 

#ifdef _WIN32
#include <windows.h>
#endif

#define M_PI       3.14159265358979323846

static Nava* nava;

// identificatori pentru stiva de obiecte (necesari pentru selectie)
#define NONE			0
#define CUB1			1
#define CUB2			2
#define GROUND_NAME		3

// tip vedere
#define VEDERE_LATERALA	0
#define VEDERE_NAVA		1
#define VEDERE_ASTEROID 2

// initial nici un obiect nu este selectat
int obiect = NONE;

// rotatia initiala a obiectelor
GLfloat spin=0.0;

GLfloat tr=0.0;

GLfloat dir=1;

int win_w = 1, win_h = 1;
GLfloat aspect = 1;

#define WIRE	0
#define SOLID	1

#define PROJECTIVE_SHADOW	0
#define VOLUME_SHADOW		1

// initial umbra este de tipul projective
int shadow_type = PROJECTIVE_SHADOW;
int shadow_enabled = 0;
// modul initial in care sunt desenate poligoanele
int mode = SOLID;
// vederea initiala
int vedere = VEDERE_LATERALA;
int mainWindow;
//
// vectorul suprafetelor 
Cube* objects[2];

// matricea folosita pentru calculul umbrelor proiectate
GLfloat groundshadow[4][4];
GLfloat plan[4];

GLfloat light_position0[] = { -2.0f, 9.5f, 0.0f, 1.0f };				//seteaza pozitia
Asteroid * asteroid;
// camera
// nume variabile pentru ecuatiile matematice

#define X 0
#define Y 1
#define Z 2
#define W 3

#define A 0
#define B 1
#define C 2
#define D 3

// Camere 
Camera *camera_nava, *camera_asteroid, *camera_laterala;

//int deseneaza = 0;

GLfloat light_ambient0 [] = { 1.0, 1.0, 1.0, 1.0 };				//seteaza componenta ambientala
GLfloat light_difusion0[] = { 1.0, 1.0, 1.0, 1.0 };				//seteaza componenta  de difuzie    
GLfloat light_specular0[] = { 1.0, 1.0, 1.0, 1.0 };				//seteaza componenta speculara
float pos_s2[] = {0.0f, 1.3f, -1.0f, 0.0f};
float ambient_s2[] = {0.5f, 0.0f, 0.0f, 0.01f}; 
float diffuse_s2[] = {0.7f, 0.0f, 0.0f, 0.7f};

float pos_s1[] = {1.0f, 1.0f, 0.0f, 0.0f};
float ambient_s1[] = {0.1f, 0.1f, 0.5f, 0.2f};
float diffuse_s1[] = {0.0f, 1.0f, .5f, 1.0f};

Vector3D* mypos =  new Vector3D(12.0f, 0.0f, 0.0f);
GLfloat inc = 0.1f;

// centura de asteroizi

vector<Asteroid *> centura ;
int curentasteroid = -1;

bool SphereIntSphere(Vector3D s1,Vector3D s2,float R1,float R2){
	float distance = sqrt(pow((s1.x - s2.x),2) + pow((s1.y - s2.y),2) + pow((s1.z -s2.z),2));
	return distance < (R1 + R2);
}



void init(void)
{
	glClearColor(0, 0, 0, 0.0);
	glEnable(GL_DEPTH_TEST);
	srand(time(0));
	nava = new Nava();

	camera_laterala = new Camera();
	
	camera_nava = new Camera();

	camera_nava->SetPosition(new Vector3D(mypos->x,mypos->y,mypos->z));
	camera_nava->SetForwardVector(new Vector3D(-1,0,0));
	camera_nava->SetRightVector(new Vector3D(0,0,1));
	camera_nava->SetUpVector(new Vector3D(0,1,0));

	camera_asteroid = new Camera();

	/*
	GLfloat direction0     [] = { 0.0, -1.0, 0.0};					
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);          
	glLightfv(GL_LIGHT0, GL_AMBIENT , light_ambient0);      
	glLightfv(GL_LIGHT0, GL_DIFFUSE , light_difusion0);          
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);      
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction0);      
	glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,5.0f);
	*/

	
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_s1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_s1);
	glLightfv(GL_LIGHT0, GL_POSITION, pos_s1);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular0);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient_s2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse_s2);
	glLightfv(GL_LIGHT1, GL_POSITION, pos_s2);
	glEnable(GL_LIGHT1);
	
	for(int i = 0; i < 15; i++){

		centura.push_back(new Asteroid(i));

	}

	asteroid = new Asteroid(2);

}



// functia pentru desenarea unui text 3D
void output(GLfloat x, GLfloat y, GLfloat z,GLfloat rotation[3],char *format,...)
{
	va_list args;

	char buffer[1024],*p;

	va_start(args,format);

	vsprintf(buffer, format, args);

	va_end(args);

	glPushMatrix();
	
	glTranslatef(x,y,z);

	glRotatef(rotation[0],1,0,0);
	glRotatef(rotation[1],0,1,0);
	glRotatef(rotation[2],0,0,1);

	glScalef(0.0045, 0.0045, 0.0); /* 0.1 to 0.001 as required */

	for (p = buffer; *p; p++)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *p);

	glPopMatrix();
}


void output2(GLfloat x, GLfloat y, char *format,...)
{
	va_list args;

	char buffer[1024],*p;

	va_start(args,format);

	vsprintf(buffer, format, args);

	va_end(args);

	glPushMatrix();
	
	glTranslatef(x,y,0);

	glRotatef(180,1,0,0);

	glScalef(0.08, 0.08, 0.0); /* 0.1 to 0.001 as required */

	for (p = buffer; *p; p++)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *p);

	glPopMatrix();
}

void draw_my_hud(void)
{
	static int frame = 0, last_time = 0;
	static GLfloat fps = 0;
	int time;
	int startY = 13 , startX = 5;
	int pasY = 13;

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - last_time > 1000) {
		fps = frame * 1000.0 / (time - last_time);
		last_time = time;
		frame = 0;
	}

	/* begin text rendering mode */
	glPushAttrib(GL_ENABLE_BIT);

	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, win_w, win_h, 0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glLoadIdentity();
	glColor4f(1, 1, 1, 1);

	output2(win_w-26*4,startY, "FPS: %.1f",fps);

	

	output2(startX, startY, "Click stanga: Animatie/selectie obiecte");
	startY+=pasY;
	


	// in functie de ce este selectat se afiseaza textul corespunzator
	
	switch (obiect)
	{
		case 4: 
			output2(startX, startY, "Obiect      : Nava");
			startY+=pasY;
			break;
		case 5: 
			output2(startX, startY, "Obiect      : Dodecadron");
			startY+=pasY;
			break;
		case GROUND_NAME:
			output2(startX, startY, "Obiect      : Sol");
			startY+=pasY;
			break;
		case NONE:
			output2(startX, startY, "Obiect      : Nici unul");
			startY+=pasY;
			break;
		default:
			output2(startX, startY, "Obiect      : Altul(neprocesat in hit list)");
			startY+=pasY;
	}
	
	// Restore previous states
	glPopAttrib();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	/* end text rendering mode */
}

// functia pentru desenarea scenei 3D
void drawScene(int deseneaza)
{
	// initilizeaza stiva de nume necesara pentru selectie
	glInitNames();
	if(vedere == VEDERE_LATERALA){
		camera_laterala->Render();
	}else if(vedere == VEDERE_NAVA){
		camera_nava->Render();
	}else {
		camera_asteroid->Render();
	}
	// Activeaza iluminarea
	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	

	glPushMatrix();
	static   GLfloat material_a1[] = { 0.14f, 0.46f, 0.3f, 1.0f };
	static   GLfloat material_d1[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_a1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_d1);
	glMaterialfv(GL_FRONT,GL_SPECULAR,material_a1);

	
	//glTranslatef(mypos->x,mypos->y,mypos->z);
	
	nava->render(mypos,deseneaza);
	
	glPopMatrix();

	//glPushMatrix();
	//glColor3f(1.0f,1.0f,1.0f);
	//glScalef(15,12,11);
	//glutWireCube(1);

	//glPopMatrix();
	//
	
	// asteroid;
	
	glPushMatrix();
	
	
	for(int i = 0; i < 15; i++){
		Vector3D pos = centura.at(i)->pozitie;
		Vector3D me = Vector3D(mypos->x,mypos->y,mypos->z);
		if(SphereIntSphere(me,pos,1,centura.at(i)->size)){
			cout<<"coliziune"<<i<<endl;
			nava->trans-=0.04f;
			centura.at(i)->alive = false;
			if(nava->trans < 0){
				nava->health --;
			}
			if(nava->health == 0){
				Sleep(3000);
				init();
			}

		}
		
		glPushName(i);
		centura.at(i)->move();
		centura.at(i)->Render();
		glPopName();
		if(curentasteroid == i && vedere == VEDERE_ASTEROID){
			camera_asteroid->SetPosition(new Vector3D(pos.x+3.0f,pos.y,pos.z));
		}

	}
	
	
	glPopMatrix();

	//spoturile de la nava
	GLfloat color_spot1[] = {1.0f, 0.0f, 0.0f, 1.0f};
	GLfloat position_spot1[] = {mypos->x, mypos->y, mypos->z+ 0.1, 1.0f};
	GLfloat direction_spot1[] = {-1.0f, 0.0f, 0.0f};
	
	glLightfv(GL_LIGHT2, GL_POSITION, position_spot1);
	glLightfv(GL_LIGHT2, GL_AMBIENT, color_spot1);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, direction_spot1);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 5.0f);
	glEnable(GL_LIGHT2);

	GLfloat color_spot2[] = {0.0f, 0.0f, 1.0f, 1.0f};
	GLfloat position_spot2[] = {mypos->x, mypos->y, mypos->z-0.1, 1.0f};
	GLfloat direction_spot2[] = {-1.0f, 0.0f, 0.1f};

	glLightfv(GL_LIGHT3, GL_POSITION, position_spot2);
	glLightfv(GL_LIGHT3, GL_AMBIENT, color_spot2);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, direction_spot2);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 5.0f);
	glEnable(GL_LIGHT3);


	
}

// functia de display
void display(void)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	drawScene(1);
	
	draw_my_hud();
	glutSwapBuffers();
}


// functia de animatie ( functia de idle a GLUT-ului -- similara cu un thread separat)
void spinAnimation()
{
	drawScene(1);
	glutPostRedisplay();
}

void vedereDinFata()
{
	int w,h;
	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);

	aspect = (GLfloat) w / (GLfloat) h;
	win_w = w;
	win_h = h;
	
	glViewport(0,0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (float)w/h, 1.0, 40.0); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// vedere din FATA
	//gluLookAt(0.0, 0.0, -15.0,   //observatorul este in origine departat pe Z
	//	      0.0, 0.0, 1.0,     //si priveste in directia pozitiva a axei oz
	//		  0.0, 1.0, 0.0);  

	init();

}

void vedereDeSus()
{
	int w,h;
	w = glutGet(GLUT_WINDOW_WIDTH);
	h = glutGet(GLUT_WINDOW_HEIGHT);

	aspect = (GLfloat) w / (GLfloat) h;
	win_w = w;
	win_h = h;

	glViewport(0,0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (float)w/h, 1.0, 40.0); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// vedere de deasupra
	gluLookAt(0.0, 15.0, -5.0,   //observatorul este in origine departat pe Y
		      0.0, -1.0,  0.0,   //si priveste in directia negativa a axei oy
			  0.0, 0.0, 1.0);  

	init();

}

void processhits (GLint hits, GLuint buffer[])
{
   int i;
   GLuint names, *ptr, minZ,*ptrNames, numberOfNames;

   ptr = (GLuint *) buffer;
   minZ = 0xffffffff;
   for (i = 0; i < hits; i++) {	
      names = *ptr;
	  ptr++;
	  if (*ptr < minZ) {
		  numberOfNames = names;
		  minZ = *ptr;
		  ptrNames = ptr+2;
	  }
	  
	  ptr += names+2;
  }

  ptr = ptrNames;
  
  obiect = *ptr;
     
}

void pick(int x, int y)
{
	GLuint buffer[1024];
	GLint nhits;

	GLint	viewport[4];

	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(1024, buffer);
	
	// se intra in modul de selectie
	glRenderMode(GL_SELECT);

	// se renderizeaza doar o zona mica din jurul cursorului mouseului
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glGetIntegerv(GL_VIEWPORT,viewport);
	gluPickMatrix(x,viewport[3]-y,1.0f,1.0f,viewport);

	gluPerspective(90,(viewport[2]-viewport[0])/(GLfloat) (viewport[3]-viewport[1]),0.1,1000);
	glMatrixMode(GL_MODELVIEW);

	// se va desena scena in modul de selectie (de fapt nimic nu este desenat propriu-zis : "desenarea" se face
	// in bufferul de selectie si nu pe ecran
	drawScene(0);

	glMatrixMode(GL_PROJECTION);						
	glPopMatrix();						
	glMatrixMode(GL_MODELVIEW);						
	nhits=glRenderMode(GL_RENDER);	
	
	// initial nici un obiect selectat
	obiect = NONE;

	// proceseaza bufferul de selectie si alege obiectul cel mai apropiat (daca exista)
	if(nhits != 0)
		processhits(nhits,buffer);
				
}



// functia pentru procesarea evenimentelor de la mouse
void mouse(int buton, int stare, int x, int y)
{
	switch(buton)
	{
	case GLUT_LEFT_BUTTON:
		if(stare == GLUT_DOWN)
		{
			// se efectueaza selectia unde a avut loc click-ul
			pick(x,y);
			cout<<obiect<<endl;
			if(vedere == VEDERE_ASTEROID){
				if(0 <= obiect && obiect < 20){
					camera_asteroid->SetPosition(new Vector3D(centura.at(obiect)->pozitie.x,
							centura.at(obiect)->pozitie.y,centura.at(obiect)->pozitie.z));
					camera_asteroid->SetForwardVector(mypos);
					curentasteroid = obiect;
				}
			}else
			if(0 <= obiect && obiect < 20){
				centura.at(obiect)->alive = false;
				Vector3D pos = centura.at(obiect)->pozitie;
				glPushMatrix();
				glDisable(GL_LIGHTING);
				glColor3f(1.0f,0.0f,0.0f);
				glBegin(GL_LINES);  
				glVertex3f (mypos->x,mypos->y,mypos->z); 
				glVertex3f (pos.x,pos.y,pos.z); glEnd();
				//drawOneLine(mypos->x,mypos->y,mypos->z,pos.x,pos.y,pos.z);
				glEnable(GL_LIGHTING);
				glPopMatrix();
			}

			// se porneste animatia
			glutIdleFunc(spinAnimation);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if(stare== GLUT_DOWN)
			glutIdleFunc(NULL);
		break;
	}
}

// functia pentru procesarea evenimentelor de la tastatura
void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27:
			exit(0);
			break;
		case '1':
			camera_laterala->Render();
			vedere = VEDERE_LATERALA;
			curentasteroid = -1;
			glutPostRedisplay();
			break;
		case '2':
			camera_nava->Render();
			vedere = VEDERE_NAVA;
			curentasteroid = -1;
			glutPostRedisplay();
			break;
		case '3':
			camera_asteroid->Render();
			vedere = VEDERE_ASTEROID;
			glutPostRedisplay();
		case 'a':
			
			if(vedere == VEDERE_NAVA || vedere == VEDERE_LATERALA ){
				camera_nava->MoveLeft(inc);
				mypos->z += inc;
			}
			break;
		case 'd':
			if(vedere == VEDERE_NAVA || vedere == VEDERE_LATERALA ){
				camera_nava->MoveRight(inc);
				mypos->z -=inc;
			}
			
			break;
		case 'w':
			if(vedere == VEDERE_NAVA || vedere == VEDERE_LATERALA){
				camera_nava->MoveForward(inc);
				mypos->x -= inc;
			}
			
			break;
		case 's':
			if(vedere == VEDERE_NAVA || vedere == VEDERE_LATERALA){
				camera_nava->MoveBackward(inc);
				mypos->x += inc;
			}
			
			break;
		case 'q':
			if(vedere == VEDERE_NAVA || vedere == VEDERE_LATERALA){
				camera_nava->MoveUpward(inc);
				mypos->y += inc;
			}
			
			break;
		case 'e':
			if(vedere == VEDERE_NAVA || vedere == VEDERE_LATERALA){
				camera_nava->MoveDownward(inc);
					mypos->y -=inc;
			}
			break;
		case 'r':
			if(vedere == VEDERE_LATERALA){
				camera_laterala->MoveForward(inc);
			}
			break;
		case 't':
			if(vedere == VEDERE_LATERALA){
				camera_laterala->MoveBackward(inc);
			}
			break;
		case 'f':
			if(vedere == VEDERE_LATERALA){
				camera_laterala->MoveLeft(inc);
			}
			break;
		case 'g':
			if(vedere == VEDERE_LATERALA){
				camera_laterala->MoveRight(inc);
			}
			break;
		case 'v':
			if(vedere == VEDERE_LATERALA){
				camera_laterala->MoveUpward(inc);
			}
			break;
		case 'b':
			if(vedere == VEDERE_LATERALA){
				camera_laterala->MoveDownward(inc);
			}
			break;
	}
	glutPostRedisplay();
}


void reshape(int w, int h)
{
	vedereDinFata();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(100,100);
	
	mainWindow = glutCreateWindow("Asteroizi");
	
	init();
	glClearColor(0, 0, 0, 1.0);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	 // Read file
	
	glutMainLoop();

	return 0;
}