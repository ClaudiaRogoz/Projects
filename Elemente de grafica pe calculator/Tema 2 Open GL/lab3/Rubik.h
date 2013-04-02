
#include "dependente\freeglut.h"
#include "Cube.h"
#include <list>
#include <vector>
#include <iostream>

using namespace std;

class Rubik{
	
	public: 
		
		list<Cube*> cuburi;
		Rubik(GLfloat size);
		~Rubik();
		GLfloat size;
		void DrawRubik(GLfloat rot,Cube::Layer primaryLayer,int iterr,vector<Cube::Layer> alllayers,vector<int> allrotlayers);
		void init();
    
};