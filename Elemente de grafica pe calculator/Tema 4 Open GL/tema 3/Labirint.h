#include "glut.h"
#include "Cub.h"
#include <vector>
#include <time.h>
#include <iostream>

class Labirint{
	public:
		Labirint(int nrcol,int nrlini,GLfloat pexi,GLfloat peyi, char** labirint,std::vector<int> distruse,int tor);
		~Labirint();
		void DrawLabirint();
		void Init();
		std::vector<Cub* > cuburi;
		Vector3D torpoz;
		std::vector<int> distruse;
		std::vector<Vector3D> emptyspace;
	private:
		bool Labirint::edistrus(int ind);
		int nrcoloane,nrlinii;
		GLfloat pexi,peyi;
		char** labirint;
		int tor;

};