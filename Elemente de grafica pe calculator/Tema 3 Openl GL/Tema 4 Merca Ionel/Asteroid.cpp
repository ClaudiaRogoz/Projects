#include "Asteroid.h"

Asteroid::Asteroid(int seed){
	alive = true;
	this->seed = seed;
	this->init(seed);
	
}


void Asteroid::init(int seed){
	MAXX = 14.0f,MINX = -12.0f,MAXY = 7.0f,MINY = -7.0f,MAXZ = 6,MINZ = -6;
	MAXSIZE = 1.0f,MINSIZE = 0.2f;
	MAXSPEED = 0.5f; MINSPEED = 0.03f;
	// culoare aleator
	Asteroid::culoare = Vector3D((float)rand()/(float)RAND_MAX,(float)rand()/(float)RAND_MAX,(float)rand()/(float)RAND_MAX);
	// marime aleator 
	Asteroid::size = MINSIZE + (MAXSIZE - MINSIZE)*((float)rand()/(float)RAND_MAX);
	// pozitie aleator;
	float x = MINX -5.0f + (MAXX+ 3.0f - MINX)* ((float)rand()/(float)RAND_MAX);
	float y = MINY + (MAXY - MINY) * ((float)rand()/(float)RAND_MAX);
	float z = MINZ + (MAXZ - MINZ) * ((float)rand()/(float)RAND_MAX);
	pozitie = Vector3D(x,y,z);
	// viteza aleatoare
	//speed = MINSPEED + (MAXSPEED - MINSPEED) * ((float)rand()/(float)RAND_MAX);
	speed = 0.01 + (((float)rand()/(float)RAND_MAX))/10.0f;
}

Asteroid::~Asteroid(){

}

void Asteroid::Render(){
	if(alive){

	glPushMatrix();
		static   GLfloat material_ambient1[] = { 179.0f/255.0f, 157.0f/255.0f, 83.0f/255.0f, 1.0f };
		//static   GLfloat material_diffuse1[] = { 179.0f/255.0f, 157.0f/255.0f, 83.0f/255.0f, 1.0f };
		static GLfloat material[] = { culoare.x,culoare.y,culoare.z,1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material);
		glMaterialfv(GL_FRONT,GL_SPECULAR,material_ambient1);
		glTranslatef(pozitie.x,pozitie.y,pozitie.z);
		glScalef(size,size,size);
		glutSolidDodecahedron();
	glPopMatrix();
	
	}else{
		init(1);
		alive = true;
	}


}

void Asteroid::move(){
	
	this->pozitie.x += speed;
	
	if(this->pozitie.x >= MAXX + 7.0f){
		
		float x = MINX-5.0f;
		this->pozitie.x = x;
		float y = MINY + (MAXY - MINY) * ((float)rand()/(float)RAND_MAX);
		float z = MINZ + (MAXZ - MINZ) * ((float)rand()/(float)RAND_MAX);
	
		this->pozitie.y = y;
		this->pozitie.z = z;
	
	}

}



