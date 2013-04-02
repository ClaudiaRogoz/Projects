//programul deseneaza figuri care incep sa se roteasca la apasarea
//butonului din stanga al mouse-ului si se opresc la apasarea
//butonului din dreapta.
#include <cstdlib>
#include "dependente\freeglut.h"
#include <iostream>
#include "Rubik.h"
#define KEY_ESC 27
#define KEY_SPACE 32

using namespace std;
int initialwindow;
GLfloat spin=0.0;
GLfloat aspect = 1;
int other_window;

int nrmutarisolve = 0;
int win_w = 1, win_h = 1;
float lastx = 0.0f,lasty = 0.0f;
GLfloat rot = 0.0f;
bool enable = false;
int itt = 0;
// pozitia camerei
float xpos = 0, ypos = 0, zpos = 0 ;
// unghiuri de rotatie ale camerei 
float xrot = 0, yrot = 0, angle=0.0;

GLfloat rotx= 0.0f,roty = 0.0f, rotz = 0.0f;
int enablerotx = 0, enableroty = 0, enablerotz = 0;
int iterx=0,itery = 0, iterz = 0;
int enablesolve2 = 0;
vector<Cube::Layer> alllayers;
int layerind = 0;
static Cube::Layer primaryL= Cube::L_F1;
Rubik* rub = new Rubik(0.5f);
int nrmutariinit = 0;
int enablesolve = 0;
vector<int> allrotlayers;
vector<int> iterrotlayers;
int itertosolve = 0;
void initrot(){
	for(int i = 0; i < 9; i++){
		allrotlayers.push_back(0);
		iterrotlayers.push_back(0);
	}
}

void initLayers(){

	alllayers.push_back(Cube::L_F1);
	alllayers.push_back(Cube::L_F2);
	alllayers.push_back(Cube::L_F3);
	alllayers.push_back(Cube::L_L1);
	alllayers.push_back(Cube::L_L2);
	alllayers.push_back(Cube::L_L3);
	alllayers.push_back(Cube::L_D1);
	alllayers.push_back(Cube::L_D2);
	alllayers.push_back(Cube::L_D3);
	
}


void init(void)
{	//specifica valorile r,g,b,a folosite atunci cand se sterge bufferul de culoare cu glClear

	initLayers();
	initrot();
	rub->init();
	glClearColor(0.0f, 0.0f, 0.1f, 0.0f);

}

void initother(void){
		glClearColor(0.0f, 0.0f, 0.1f, 0.0f);
}



void camera () {

    glRotatef(xrot,1.0,0.0,0.0);  //rotatie pe axa x stanga dreapta 
    glRotatef(yrot,0.0,1.0,0.0);  //rotatie pe axa y sus jos
    glTranslated(-xpos,-ypos,-zpos); // translatie poz camera

}

//functia de afisare
void display(void)
{
	
	//initializeaza bufferul de culoare
	//clear screen and z-buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	camera();
	gluLookAt(4,4,4,0,0,0,0,1,0);
	glPushMatrix();
	
		if(enablesolve){
			
			if(itertosolve <= 100){
				Cube * c = new Cube(Cube::NONE,Cube::NONE,Cube::NONE,0,0,0);
				glTranslatef(3.0f,3.0f,0.0f);
				c->DrawCube(0.2f);
				itertosolve ++;
			}
			else{
				enablesolve =!enablesolve;
				enablesolve2 = 1;
				itertosolve = 0;
			}
		}
	glPopMatrix();

	if(enable){
		
		allrotlayers[Cube::retnrLayer(primaryL)]++;
		if(allrotlayers[Cube::retnrLayer(primaryL)] >= 90*iterrotlayers[Cube::retnrLayer(primaryL)]) {
			enable = false;
			
		}
	}

	if(enablerotx){

		if(rotx <= iterx*90){
			rotx = rotx + 1;
			
		}else{
			enablerotx = 0;
		}
		
		glutPostRedisplay();
	
	}
	if(enableroty){

		if(roty <= itery*90){
			roty = roty + 1;
			
		}else{
			enableroty = 0;
		}
		
		glutPostRedisplay();
	}
	
	if(enablerotz){

		if(rotz <= iterz*90){
			rotz = rotz + 1;
			
		}else{
			enablerotz = 0;
		}
		
		glutPostRedisplay();
	
	}


	glRotatef(rotx,1.0f,0.0f,0.0f);
	glRotatef(roty,0.0f,1.0f,0.0f);
	glRotatef(rotz,0.0f,0.0f,1.0f);
	
	rub->DrawRubik(allrotlayers[Cube::retnrLayer(primaryL)],primaryL,itt+1,alllayers,allrotlayers);

	
	//give the double buffering effect
	glutSwapBuffers();
	angle++;
}

void display_1(void)
{
	
	//initializeaza bufferul de culoare
	//clear screen and z-buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	camera();
	gluLookAt(0,2,3,0,0,0,0,1,0);
	glPushMatrix();
	
	int all = 0;
		int k = 0;
		int tray = 1.9;
		float size = 0.1;
		cout<<(int )(nrmutarisolve /10)<<"\n"<<nrmutarisolve%10<<"\n";
		//Cube * c = new Cube(Cube::NONE,Cube::NONE,Cube::NONE,0,0,0);

		//			for(int i = 0; i < 10; i++){
		//				glPushMatrix();
		//				glTranslatef(-1.8 + i*size*4,1.5,0);
		//				c->DrawCube(size);
		//				glPopMatrix();
		//			}
		int trx = -2.6;

		Cube *c = new Cube(Cube::NONE,Cube::NONE,Cube::NONE,0,0,0);
		for(int i = 0; i < (int )(nrmutarisolve /10);i++){
			trx = -2.6;
			tray = tray - i*size*4;
			for(int j = 0; j < 10; j++){
				glPushMatrix();
					
					glTranslatef(trx + j*size*4,tray+i*size*4 ,0);
					c->DrawCube(size);
				glPopMatrix();
			}
			
		}
		trx = -2.6;
		while(all < nrmutarisolve%10){
			cout<<"aiciwhile";
			all++;
			glPushMatrix();
					Cube *c = new Cube(Cube::NONE,Cube::NONE,Cube::NONE,0,0,0);
					glTranslatef(trx +all*size*4 ,tray-size*4 ,0);
					c->DrawCube(size);
				glPopMatrix();
		}
	glPopMatrix();
	//give the double buffering effect
	glutSwapBuffers();
	angle++;
}

void animatieDisplay()
{
	
	spin=spin+1;

	if(spin>360.0)
		spin= spin -360.0f;

	
	glutPostRedisplay();
}
//
//void animatiex(){
//	
//	if(enablerotx){
//
//		if(rotx <= iterx*90){
//			rotx = rotx + 5;
//		}else{
//			enablerotx = 0;
//		}
//	}
//
//	glutPostRedisplay();
//
//}
//

void reshape_1(int w, int h)
{

	glutSetWindow(other_window);
	//transformarea in poarta de vizualizare
	glViewport(0,0, (GLsizei) w, (GLsizei) h);

	aspect = (GLfloat) w / (GLfloat) h;

	//se lucreaza pe matricea de proiectie
	glMatrixMode(GL_PROJECTION);
	//se porneste de la matricea identitate
	glLoadIdentity();
	//transformarea de proiectie - specifica si volumul de vizualizare
	gluPerspective(60.0f, aspect, 0.1f, 100.0f);

	//se lucreaza pe matricea de modelare vizualizare
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 0.0,   //observatorul este in origine
			  0.0, 0.0, 1.0,   //si priveste in directia pozitiva a axei oz
			  0.0, 2.0, 0.0);  



}

void reshape(int w, int h)
{

	//transformarea in poarta de vizualizare
	glViewport(0,0, (GLsizei) w, (GLsizei) h);

	aspect = (GLfloat) w / (GLfloat) h;

	//se lucreaza pe matricea de proiectie
	glMatrixMode(GL_PROJECTION);
	//se porneste de la matricea identitate
	glLoadIdentity();
	//transformarea de proiectie - specifica si volumul de vizualizare
	gluPerspective(60.0f, aspect, 0.1f, 100.0f);

	//se lucreaza pe matricea de modelare vizualizare
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 0.0,   //observatorul este in origine
			  0.0, 0.0, 1.0,   //si priveste in directia pozitiva a axei oz
			  0.0, 2.0, 0.0);  

	win_w = w;
	win_h = h;


}

//functie apelata la actionarea mouse-ului
void mouse(int buton, int stare, int x, int y)
{
	switch(buton)
	{
	case GLUT_LEFT_BUTTON:
		if(stare == GLUT_DOWN)
			//functia idle animatieDisplay() se apeleaza oricand nu sunt evenimente
			glutIdleFunc(animatieDisplay);
		break;
	case GLUT_RIGHT_BUTTON:
		if(stare== GLUT_DOWN)
			//functia idle este dezactivata 
			glutIdleFunc(NULL);
		break;
	}
}

void mouseMovement(int x, int y) {
    int diffx=x-lastx; //check the difference between the current x and the last x position
    int diffy=y-lasty; //check the difference between the current y and the last y position
    lastx=x; //set lastx to the current x position
    lasty=y; //set lasty to the current y position
    xrot += (float) diffy; //set the xrot to xrot with the additionof the difference in the y position
    yrot += (float) diffx;    //set the xrot to yrot with the additionof the difference in the x position
}

void onKey1(unsigned char key){
	float xrotrad, yrotrad;
	
	switch(key){
		case 'o':
		
			glutSetWindow(initialwindow);
			glutDestroyWindow(other_window);
			init();
			break;
		case 'w':
			
			yrotrad = (yrot / 180 * 3.141592654f);
			xrotrad = (xrot / 180 * 3.141592654f);
			xpos += float(sin(yrotrad)) ;
			zpos -= float(cos(yrotrad)) ;
			ypos -= float(sin(xrotrad)) ;
			break;
		// camera in spate
		case 's':
			yrotrad = (yrot / 180 * 3.141592654f);
			xrotrad = (xrot / 180 * 3.141592654f);
			xpos -= float(sin(yrotrad));
			zpos += float(cos(yrotrad)) ;
			ypos += float(sin(xrotrad));
			break;
		// camera in dreapta 
		case 'd':
			
			yrotrad = (yrot / 180 * 3.141592654f);
			xpos += float(cos(yrotrad)) * 0.2;
			zpos += float(sin(yrotrad)) * 0.2;
			break;
		case 'a':
			
			yrotrad = (yrot / 180 * 3.141592654f);
			xpos -= float(cos(yrotrad)) * 0.2;
			zpos -= float(sin(yrotrad)) * 0.2;
			break;
		default:
			break;
	}

}
void keyboardCallbackFunction1(unsigned char key, int posx, int posy){
	if(key==KEY_ESC) glutExit();
	//call client function
	onKey1(key);
}

void onKey(unsigned char key){
	float xrotrad, yrotrad;
	
	switch(key){
		//rotirea cubului pe x
		case 'o':
				glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
				glutInitWindowSize(640,480);
				glutInitWindowPosition(200,150);
				other_window = glutCreateWindow("Scor");
				init();
				glutSetWindow(other_window);
				glutDisplayFunc(display_1);
				//functia reshape() este apelata la redimensionarea ferestrei de afisare 
				//sau cand sistemul determina ca s-a acoperit (partial) fereastra
				glutReshapeFunc(reshape_1);
				glutKeyboardFunc(keyboardCallbackFunction1);
				glEnable(GL_DEPTH_TEST);//adaugat de mine
				glutMainLoop();
			break;
		case 't':
			if(!enableroty || !enablerotz){
				enablerotx = 1;
				iterx++;
			}
			break;
		case 'y' : 
			if(!enablerotz || !enableroty){
				enableroty = 1;
				itery++;
			}
			break;
		case 'u' : 
			if(!enablerotx || !enableroty){
				enablerotz = 1;
				iterz++;
			}
			break;
		case 'z' :
			enable = true;
			iterrotlayers[Cube::retnrLayer(primaryL)]++;
			nrmutariinit++;
			if(nrmutariinit == 4){
				enablesolve = 1;
			}
			if(enablesolve2){
				nrmutarisolve++;
			}
			glutPostRedisplay();
			break;
		case 'c':
			if(!enable){
				layerind ++;
				if(layerind >= 9){
					layerind = 0;
				
				}
				primaryL = alllayers.at(layerind);

			}
			glutPostRedisplay();
			break;
		// camera jos
		case 'q':
			xrot +=1;
			if(xrot > 360) 
				xrot -=360;
			break;
		// camera sus
		case 'e':
			xrot -=1;
			if(xrot < -360) xrot += 360;
			break;
		// camera in fata
		case 'w':
			
			yrotrad = (yrot / 180 * 3.141592654f);
			xrotrad = (xrot / 180 * 3.141592654f);
			xpos += float(sin(yrotrad)) ;
			zpos -= float(cos(yrotrad)) ;
			ypos -= float(sin(xrotrad)) ;
			break;
		// camera in spate
		case 's':
			yrotrad = (yrot / 180 * 3.141592654f);
			xrotrad = (xrot / 180 * 3.141592654f);
			xpos -= float(sin(yrotrad));
			zpos += float(cos(yrotrad)) ;
			ypos += float(sin(xrotrad));
			break;
		// camera in dreapta 
		case 'd':
			
			yrotrad = (yrot / 180 * 3.141592654f);
			xpos += float(cos(yrotrad)) * 0.2;
			zpos += float(sin(yrotrad)) * 0.2;
			break;
		case 'a':
			
			yrotrad = (yrot / 180 * 3.141592654f);
			xpos -= float(cos(yrotrad)) * 0.2;
			zpos -= float(sin(yrotrad)) * 0.2;
			break;
		default:
			break;
	}

}



void keyboardCallbackFunction(unsigned char key, int posx, int posy){
	if(key==KEY_ESC) glutExit();
	//call client function
	onKey(key);
}


int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100,100);
	initialwindow = glutCreateWindow("Animatie");
	
	init();
	
	//functia de afisare se numeste display()
	glutDisplayFunc(display);
	
	//functia reshape() este apelata la redimensionarea ferestrei de afisare 
	//sau cand sistemul determina ca s-a acoperit (partial) fereastra
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardCallbackFunction);
	//functia mouse() se apeleaza la actionarea mouse-ului
	glutMouseFunc(mouse);
	//glutPassiveMotionFunc(mouseMovement);
	glEnable(GL_DEPTH_TEST);//adaugat de mine

	//contine o bucla in care aplicatia asteapta evenimente
	glutMainLoop();
	return 0;
}