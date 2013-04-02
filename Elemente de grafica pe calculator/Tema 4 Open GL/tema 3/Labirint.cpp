#include "Labirint.h"

Labirint::Labirint(int nrcol,int nrlini,GLfloat pexi,GLfloat peyi,char** labirint,std::vector<int> distruse,int tor){
	this->nrcoloane = nrcol;
	this->nrlinii = nrlini;
	this->pexi = pexi;
	this->peyi = peyi;
	this->labirint = labirint;
	this->distruse = distruse;
	this->tor = tor;
}

Labirint::~Labirint(){
	
	
}

bool Labirint::edistrus(int ind){
	for(int i = 0; i < distruse.size(); i++){
		if(distruse.at(i) == ind){
			return true;
		}
	}
	return false;
}

void Labirint::DrawLabirint(){
	
	GLfloat pexi1 = pexi; 
	GLfloat peyi1 = peyi;

	int nr = 0;
	for(int i = 0; i < nrlinii; i++){
		
		pexi1 = pexi;
		for(int j = 0; j < nrcoloane; j++){
			// deseneaza cub daca este 0 altfel treci mai departe
			
			if(labirint[i][j] == '*'&& !edistrus(i*nrlinii+ j)){
				glPushMatrix();
				
				Cub * c = new Cub(pexi1 + j*2 , 0, peyi1 + 2*i, 1, i* nrlinii + j);
				
				c->DrawCub();
				cuburi.push_back(c);
				glPopMatrix();
			}else {
				emptyspace.push_back(Vector3D(pexi1 + j*2 , 0, peyi1 + 2*i));

				nr++;
				if(nr == tor){
					glPushMatrix();
					glTranslatef(pexi1 + j*2,0,peyi1 + 2*i);
					torpoz = Vector3D(pexi1 + j*2,0,peyi1 + 2*i);
						glutSolidTorus(0.2,0.4,20,20);
					glPopMatrix();

				}


			}
		}
		
	}


}