#include "Rubik.h"


Rubik::Rubik(GLfloat size ){
	Rubik::size = size;
	
}

Rubik::~Rubik(){
	
}


void Rubik::init(){
	
	 for(int i = -1; i < 2; i++){
		for(int j = -1; j < 2; j++){
			for(int k =-1; k < 2; k++){
				glPushMatrix();
					float t1=2*i*size + i*0.1f,t2 =  2*j*size + j*0.1f,t3 = 2*k*size + k*0.1f;
					glTranslatef(t1,t2, t3);
					
					Cube::Layer ind1,ind2,ind3;
					if( i == -1 ){
						
						ind1 = Cube::L_L1;
					}else
						if( i == 0){
							ind1 = Cube::L_L2;
						}else
							if(i == 1){
								ind1 = Cube::L_L3;
							}

					if( j == -1){
						ind2 = Cube::L_D1;
					}else
						if(j == 0){
							ind2 = Cube::L_D2;		
						}else
							if(j == 1){
								ind2 = Cube::L_D3;
							}

					if(k == 1){
						ind3 = Cube::L_F1;
					}else
						if(k == 0)
							ind3 = Cube::L_F2;
						else
							if( k == -1)
								ind3 = Cube::L_F3;

					
					Cube* c;
					c = new Cube(ind1,ind2,ind3,t1,t2,t3);
					cuburi.push_back(c);

				glPopMatrix();
			}
		}
	}

}



void Rubik::DrawRubik(GLfloat rot, Cube::Layer primary,int iterr,vector<Cube::Layer> alllayers,vector<int> allrotlayers){
	int injuraxei = -1;
	if(primary == Cube::L_L1 || primary == Cube::L_L2 || primary == Cube::L_L3){
		injuraxei = 1;
	}
	else 
		if(primary == Cube::L_D1 || primary == Cube::L_D2 || primary == Cube::L_D3){
			injuraxei = 2;
		}
		else
			if(primary == Cube::L_F1 || primary == Cube::L_F2 || primary == Cube::L_F3){
				injuraxei = 3;
			}


	vector<Cube*> primare ;
	int k = 0;
	
	for(list<Cube*>::iterator it = cuburi.begin(); it!= cuburi.end(); it++){
		Cube * c = (*it);
		glPushMatrix();

			if(c->layer1 == primary || c->layer2 == primary || c->layer3 == primary){
				
				primare.push_back(c);
				
			}else 
				glTranslatef(c->trax + size*0.1,c->tray + size*0.1,c->traz+ size*0.1);
				c->Draw(size,0);
			

			
		glPopMatrix();
	}
	
	if(injuraxei == 1)
		glRotatef(rot,1.0f,0.0f,0.0f);
	else 
		if(injuraxei == 2)
			glRotatef(rot,0.0f,1.0f,0.0f);
		else
			if(injuraxei == 3)
				glRotatef(rot,0.0f,0.0f,1.0f);

	for(vector<Cube*>::iterator it = primare.begin(); it!= primare.end(); it++){
		
		Cube * c = (*it);
		glPushMatrix();
			glTranslatef(c->trax,c->tray,c->traz);
			c->Draw(size,1);
		glPopMatrix();

	}
	
}
