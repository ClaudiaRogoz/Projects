
#include <string>
#include "Vector3D.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>
#include "Help.h"
//glut 
#include <GL/gl.h>
#include <GL/glu.h>
#include "dependente\freeglut.h"

using namespace std;


class LoadOFF{
	public:
		LoadOFF();
		LoadOFF(string file);
		~LoadOFF();
		void render();
		
	private:

		string file;
		Mesh* readoff();
		Mesh *mesh;

};