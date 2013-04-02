//-----------------------------------------------------------------------------------------------
//					LAB 1
//
//	Fisiere de interes: Transform2d.cpp main.cpp
//
//	Functii WorldDrawer2d:
//	-init e apelat o singura data, la inceput.
//	-idle e apelat per cadru de desenare
//	-onKey la apasarea unei taste.
//
//	Obiecte:
//	- un obiect este reprezentat prin punct si topologia punctelor (cum sunt legate pctele)
//	- obiectele sunt compuse din triunghiuri! de exemplu cu 4 puncte si 6 indici de topologie
//	pot crea 2 triunghiuri adiacente ce impreuna formeaza un dreptunghi.
//
//	Sisteme de coordonate:
//	- sunt 2 tipuri de sisteme de coordonate (fix - bleu&magenta) si dinamic(rosu&albastru)
//	- ca un obiect sa fie desenat trebuie sa fie atasat unui sistem de coordonate
//	- cand un obiect e atasat la un sistem de coordonate urmeaza transformarile sistemului.
//
//	Control obiecte:
//	- daca translatez/rotesc un obiect/punct direct (ex: o->translate(1,1)) o fac in coordonate globale
//	- daca translatez/rotesc un obiect printr-un sistem de coordonate o fac in coordonate locale
//	- pentru simplitate toate coordonatele mentinute in obiecte(de c++) sunt globale.
//
//	Happy coding.
//----------------------------------------------------------------------------------------------
#include <cstdlib>
#include <time.h>
#include "WorldDrawer2d.h"
#include <Windows.h>
bool WorldDrawer2d::animation=false;
bool ok = false;
bool fr = false;
int i = 0;
float totalangle = 0;
int curentteam = 0;
//used global vars
CoordinateSystem2d *cs1, *cs2,*cs3;
std::vector<Object2d*> players1;
std::vector<Object2d*> players2;
Object2d *o1, *o2, *o3,*o4,*o5,*o6,*o7,*o8,*o9,*o10,*o11,*o12,*o13,*o14,*o15,*o16,*o17;
Object2d *o18,*o19,*o20,*o21;
Object2d *b1,*b2,*b3,*b4;
Object2d *curent;
std::vector<Object2d *> spectatori;
Point2d scor = Point2d(0,0);
int sensx = 1,sensy = 1;
float movex= 0, movey =0;
float colx , coly;

bool WorldDrawer2d::collisionCL(Point2d x, float raza, Point2d p1, Point2d p2){
	
	float m = (p2.y - p1.y) / ( p2.x - p1.x);
	float d = 0;
	if((p2.x - p1.x)== 0){
		d = abs(x.x - p2.x);
	}else 
		if(p2.y == p1.y){
			d = abs(x.y - p1.y);
	}
	else{
		d = abs(m * x.x - x.y - m * p1.x + p1.y)/ (sqrt(m*m+ 1));
	}
	if(d <= raza){
		if(((p2.x-p1.x) == 0) && x.y <= p1.y && x.y >= p2.y ){
			return true;
		}
		if(m == 0 && x.x >= p1.x && x.x <= p2.x){
			return true;
		}
		return false;
	}else{
		return false;
	}

}

void WorldDrawer2d::DrawTribune(std::vector<Object2d *> * v){
	
	Object2d *t1,*t2,*t3,*t4;
	DrawFour(0.1f,12.0f,&t1,0.0f,0.0f,0.0f);
	DrawFour(0.1f,12.0f,&t2,0.0f,0.0f,0.0f);
	DrawFour(3.0f,0.1f,&t3,0.0f,0.0f,0.0f);
	DrawFour(3.0f,0.1f,&t4,0.0f,0.0f,0.0f);
	t1->translate(-14.0f,0.0f);
	t2->translate(-19.0f,0.0f);
	t3->translate(-16.0f,-12.0f);
	t4->translate(-16.0f,12.0f);
	float p = -18.5f;
	srand(time( 0) );
	for(int j = 0; j < 5; j+=2){
		float k = -11.0f;
		
		for(int i = 0 ; i < 24; i+=2){
			Object2d * o1;
			if(i < 12){
				float r = (float) rand()/RAND_MAX*(0.5f - 0);
				float g = (float) rand()/RAND_MAX*(0.5f - 0);
				float b = (float) rand()/RAND_MAX;
				
				DrawCircle(&o1,1.0f,0.0f,0.0f);

			}else{
				float r = (float) rand()/RAND_MAX;
				float g = (float) rand()/RAND_MAX;
				float b = (float) rand()/RAND_MAX;
				
				DrawCircle(&o1,1.0f,1.0f,0.0f);
			
			}
			o1->scaleRelativeToPoint(o1->points[0],0.5f,0.5f);
			o1->translate(p,k);
			v->push_back(o1);
			k+=2;

		}
		p+=2;
	}

}

void WorldDrawer2d::DrawCircle(Object2d ** o1, float r,float g,float b){
	

	std::vector<Point2d> points;
	std::vector<int> topology;
	points.push_back(Point2d(0,0));
	for(int i = 0; i < 360; i++){
		float x = sin(3.1415f * i / 180) * 1;
		float y = cos(3.1415f * i / 180) * 1;
		points.push_back(Point2d(x,y));
	}
	topology.push_back(0);
	topology.push_back(1);
	topology.push_back(2);
	topology.push_back(2);
	topology.push_back(3);
	topology.push_back(0);
	for( int i = 3; i < points.size()-1; i++){
		topology.push_back(i);
		topology.push_back(i+1);
		topology.push_back(0);
	}
	topology.push_back(points.size()-1);
	topology.push_back(1);
	topology.push_back(0);
	(*o1) = new Object2d(points,topology);
	(*o1)->setcolor(r,g,b);
	cs1->objectAdd(*o1);


}



void WorldDrawer2d::DrawField(float lung,float lat){

	std::vector<Point2d> points2;
	std::vector<int> topology2;
	points2.push_back(Point2d(1,-1));
	points2.push_back(Point2d(-1,-1));
	points2.push_back(Point2d(-1,1));
	points2.push_back(Point2d(1,1));
	topology2.push_back(0);
	topology2.push_back(1);
	topology2.push_back(2);
	topology2.push_back(2);
	topology2.push_back(3);
	topology2.push_back(0);
	o2 = new Object2d(points2,topology2);
	o2->setcolor(0.0f,0.7f,0.0f);
	o2->scaleRelativeToPoint(Point2d(0,0),lat,lung);
	cs1->objectAdd(o2);

}

void WorldDrawer2d::DrawFour(float lat, float lung,Object2d ** o3,float r,float g,float a){
	
	std::vector<Point2d> points2;
	std::vector<int> topology2;
	points2.push_back(Point2d(1,-1));
	points2.push_back(Point2d(-1,-1));
	points2.push_back(Point2d(-1,1));
	points2.push_back(Point2d(1,1));
	topology2.push_back(0);
	topology2.push_back(1);
	topology2.push_back(2);
	topology2.push_back(2);
	topology2.push_back(3);
	topology2.push_back(0);
	(*o3) = new Object2d(points2,topology2);
	(*o3)->setcolor(r,g,a);
	(*o3)->scaleRelativeToPoint(Point2d(0,0),lat,lung);
	cs1->objectAdd(*o3);
	
}

void WorldDrawer2d::DrawPlayers(std::vector<Object2d*>* vector,float r, float g, float b){

	for(int i = 0; i < 6; i++){
		Object2d * obj;
		DrawCircle(&obj,r,g,b);
		vector->push_back(obj);
	}


}

void WorldDrawer2d::putBall(){
	srand ( time(NULL) );
	int rnd = rand();
	if(rnd % 2 == 0 ){
		
		int r = rand();
		int i = r % 5;
		
		float x , y;
		curent = players1.at(i);
		curentteam = 1;
		x = players1.at(i)->points.at(1).x;
		y = players1.at(i)->points.at(1).y;
		o1->translate(x,y);
		colx = curent->points[0].x;
		coly = curent->points[0].y;
	}else{
		
		int r = rand();
		int i = r % 5;
		float x , y;
		
		curent = players2.at(i);
		curentteam = 2;
		x = players2.at(i)->points.at(1).x;
		y = players2.at(i)->points.at(1).y;
		
		colx = curent->points[0].x;
		coly = curent->points[0].y;
		o1->translate(x,y);
	}

}



//add
void WorldDrawer2d::init(){
	cs1 = new CoordinateSystem2d();
	cs2 = new CoordinateSystem2d();
	cs_used.push_back(cs2);
	cs_used.push_back(cs1);
	DrawCircle(&o1,0.0f,0.0f,0.5f);
	o1->scaleRelativeToPoint(o1->points.at(0),0.5f,0.5f);
	DrawCircle(&b1,1.0f,1.0f,1.0f);
	DrawCircle(&b2,1.0f,1.0f,1.0f);
	DrawCircle(&b3,1.0f,1.0f,1.0f);
	DrawCircle(&b4,1.0f,1.0f,1.0f);
	DrawTribune(&spectatori);
	DrawFour(0.25f,18.0f,&o3,1.0f,1.0f,1.0f);
	DrawFour(0.25f,18.0f,&o4,1.0f,1.0f,1.0f);
	DrawFour(4.0f,0.25f,&o5,1.0f,1.0f,1.0f);
	DrawFour(4.0f,0.25f,&o6,1.0f,1.0f,1.0f);
	DrawFour(4.0f,0.25f,&o7,1.0f,1.0f,1.0f);
	DrawFour(4.0f,0.25f,&o8,1.0f,1.0f,1.0f);
	DrawFour(4.0f,0.25f,&o9,1.0f,1.0f,1.0f);
	DrawFour(4.0f,0.25f,&o10,1.0f,1.0f,1.0f);
	DrawFour(0.25f,1.0f,&o11,1.0f,1.0f,1.0f);
	DrawFour(0.25f,1.0f,&o12,1.0f,1.0f,1.0f);
	DrawFour(0.25f,1.0f,&o13,1.0f,1.0f,1.0f);
	DrawFour(0.25f,1.0f,&o14,1.0f,1.0f,1.0f);
	DrawFour(12.0f,0.1f,&o15,1.0f,1.0f,1.0f);
	DrawFour(6.0f,0.1f,&o16,1.0f,1.0f,1.0f);
	DrawFour(6.0f,0.1f,&o17,1.0f,1.0f,1.0f);
	DrawFour(0.1f,1.3f,&o18,1.0f,1.0f,1.0f);
	DrawFour(0.1f,1.3f,&o19,1.0f,1.0f,1.0f);
	DrawFour(0.1f,1.3f,&o20,1.0f,1.0f,1.0f);
	DrawFour(0.1f,1.3f,&o21,1.0f,1.0f,1.0f);

	DrawPlayers(&players1,1.0f,1.0f,0.0f);
	DrawPlayers(&players2,1.0f,0.1f,0.1f);
	DrawScore(1.0f,1.0f,0.0f,1.0f,0.1f,0.1f);
	DrawField(18,12);
	
	o3->translate(12.25f,0.0f);
	o4->translate(-12.25f,0.0f);
	o5->translate(-8.25f,18.0f);
	o6->translate(8.25f,18.0f);
	o7->translate(-8.25f,-18.0f);
	o8->translate(8.25f,-18.0f);
	o9->translate(0.0f,19.7f);
	o10->translate(0.0f,-19.7f);
	o11->translate(4.0f,18.75f);
	o12->translate(-4.0f,18.75f);
	o13->translate(-4.0f,-18.75f);
	o14->translate(4.0f,-18.75f);
	o16->translate(0.0f,15.5f);
	o17->translate(0.0f,-15.5f);
	o18->translate(6.0f,16.8f);
	o19->translate(-6.0f,16.8f);
	o20->translate(6.0f,-16.8f);
	o21->translate(-6.0f,-16.8f);
	players1.at(0)->translate(0.0f,17.7f);
	players1.at(1)->translate(-5.0f,10.0f);
	players1.at(2)->translate(5.0f,10.0f);
	players1.at(3)->translate(3.0f,-3.0f);
	players1.at(4)->translate(-6.0f,-3.0f);
	players1.at(5)->translate(0.0f,-9.0f);
	players2.at(0)->translate(0.0f,-17.7f);
	players2.at(1)->translate(5.0f,-10.0f);
	players2.at(2)->translate(-5.0f,-10.0f);
	players2.at(3)->translate(-3.0f,3.0f);
	players2.at(4)->translate(6.0f,3.0f);
	players2.at(5)->translate(0.0f,9.0f);

	putBall();
	b1->scaleRelativeToPoint(b1->points[0],0.75f,0.75f);
	b2->scaleRelativeToPoint(b2->points[0],0.75f,0.75f);
	b3->scaleRelativeToPoint(b3->points[0],0.75f,0.75f);
	b4->scaleRelativeToPoint(b4->points[0],0.75f,0.75f);

	b1->translate(-4.0f,18.0f);
	b2->translate(4.0f,18.0f);
	b3->translate(-4.0f,-18.0f);
	b4->translate(4.0f,-18.0f);

}

bool okgol1 = false,okgol2 = false;
int iteration=1;
void WorldDrawer2d::onIdle(){	//per frame
	
	detectCB();
	detectC();
	srand(time(NULL));
	int gol = detectGol();
	if(gol == 1){
			scor.y++;
			okgol1 = true;
			giveBall(1);

	}else if(gol == 2){
			scor.x++;
			okgol2 = true;
			giveBall(2);
	}
	if(gol!=0){
		DrawScore(1.0f,1.0f,0.0f,1.0f,0.1f,0.1f);
	
	}
	
	srand(time(NULL));
	if(okgol1 || okgol2){

		if(iteration <= 50){
			
			if(okgol2){
				for(int i = 0 ; i < 3; i++){
					for(int j = 6; j < 12; j++){
						float r = (float) rand()/RAND_MAX;
						float g = (float) rand()/RAND_MAX;
						float b = (float) rand()/RAND_MAX;
						spectatori[i * 12 + j]->setcolor(r,g,b);
					}
				}
				
			}else{
				for(int i = 0 ; i < 3; i++){
					for(int j = 0; j < 6; j++){
						float r = (float) rand()/RAND_MAX;
						float g = (float) rand()/RAND_MAX;
						float b = (float) rand()/RAND_MAX;
						spectatori[i * 12 + j]->setcolor(r,g,b);
					}
				}
			}
			iteration ++;
		}else{
			if(okgol2){
				for(int i = 0 ; i < 3; i++){
					for(int j = 6; j < 12; j++){
						spectatori[i * 12 + j]->setcolor(1.0f,1.0f,0.0f);
					}
				}
				
			}else{
				for(int i = 0 ; i < 3; i++){
					for(int j = 0; j < 6; j++){
						spectatori[i * 12 + j]->setcolor(1.0f,0.0f,0.0f);
					}
				}
			}
			okgol1 = false;
			okgol2 = false;
			iteration = 1;

		}
	}

	if(scor.y == 3 || scor.x == 3){
		Sleep(3000);
		int i = rand();
		scor.x = 0;
		scor.y = 0;
		DrawScore(1.0f,1.0f,0.0f,1.0f,0.1f,0.1f);
		if(i % 2== 0){
			giveBall(1);
		}else{
			giveBall(2);
		}

	}



	detectCP();
	
	if(animation){
		
		o1->translate(movex,movey);
		

	}

}

void WorldDrawer2d::giveBall(int team){
	o1->translate(-o1->points[0].x,-o1->points[0].y);
	srand(time(NULL));
	int i = rand() % 6;
	float x,y;
	if(team == 1){
		x = players1.at(i)->points.at(1).x;
		y = players1.at(i)->points.at(1).y;
		o1->translate(x,y);
		curent = players1.at(i);
		curentteam = 1;
		colx = curent->points[0].x;
		coly = curent->points[0].y;

	}else{
		
		x = players2.at(i)->points.at(1).x;
		y = players2.at(i)->points.at(1).y;
		o1->translate(x,y);
		curent = players2.at(i);
		curentteam = 2;
		colx = curent->points[0].x;
		coly = curent->points[0].y;

	}
		totalangle = 0;
		fr = false;
}

void WorldDrawer2d::onKey(unsigned char key){
	switch(key){
		// controale prima echipa
		case 'a':
			players1[0]->translate(-0.5f,0.0);
			if(curent == players1[0]){
				o1->translate(-0.5f,0.0f);
			}
			break;
		case 'd':
			players1[0]->translate(0.5f,0.0);
			if(curent == players1[0]){
				o1->translate(0.5f,0.0f);
			}
			break;
		case 'r':
			if(!fr && curentteam == 1){
				curent->rotateRelativeToPoint(curent->points.at(0),0.1);
				o1->rotateRelativeToPoint(curent->points.at(0),0.1);
				totalangle -= 0.05f;
				
			}

			break;
		case 'w':
			if(!fr && curentteam == 1){
				curent->rotateRelativeToPoint(curent->points.at(0),-0.1);
				o1->rotateRelativeToPoint(curent->points.at(0),-0.1);
				totalangle += 0.05f;
			
			}
			break;
		case 'e':
			if(!fr && curentteam == 1){
				movex = 0.7 * (o1->points[0].x - colx);
				movey = 0.7 * (o1->points[0].y - coly);
				fr = true;
				o1->translate(movex*2,movey*2);
				animation=!animation;
			}
			break;
		// controale a doua echipa
		case '4':
			players2[0]->translate(-0.5f,0.0);
			if(curent == players2[0]){
				o1->translate(-0.5f,0.0f);
			}
			break;
		case '6':
			players2[0]->translate(0.5f,0.0);
			if(curent == players2[0]){
				o1->translate(0.5f,0.0f);
			}
			break;
		case '7':
			if(!fr && curentteam == 2){
				curent->rotateRelativeToPoint(curent->points.at(0),0.1);
				o1->rotateRelativeToPoint(curent->points.at(0),0.1);
				totalangle -= 0.05f;
				
			}

			break;
		case '9':
			if(!fr && curentteam == 2){
				curent->rotateRelativeToPoint(curent->points.at(0),-0.1);
				o1->rotateRelativeToPoint(curent->points.at(0),-0.1);
				totalangle += 0.05f;
			
			}
			break;
		case '8':
			if(!fr && curentteam == 2){
				movex = 0.7 * (o1->points[0].x - colx);
				movey = 0.7 * (o1->points[0].y - coly);
				fr = true;
				o1->translate(movex*2,movey*2);
				animation=!animation;
			}
			break;
		default:
			break;
	}

}


void WorldDrawer2d::detectCB(){
			float m1 = (o1->points[0].x - (b1)->points[0].x)*(o1->points[0].x - (b1)->points[0].x) + 
				(o1->points[0].y - (b1)->points[0].y)*(o1->points[0].y - (b1)->points[0].y);
			float m2 = 1.25f*1.25f;
			
			if(m1 < m2){
				movey *= -1;
			}
			m1 = (o1->points[0].x - (b2)->points[0].x)*(o1->points[0].x - (b2)->points[0].x) + 
				(o1->points[0].y - (b2)->points[0].y)*(o1->points[0].y - (b2)->points[0].y);
			m2 = 1.25f*1.25f;
			if(m1 < m2){
				movey*=-1;
			}
			m1 = (o1->points[0].x - (b3)->points[0].x)*(o1->points[0].x - (b3)->points[0].x) + 
				(o1->points[0].y - (b3)->points[0].y)*(o1->points[0].y - (b3)->points[0].y);
			m2 = 1.25f*1.25f;
			if(m1 < m2){
				movey*=-1;
			}
			m1 = (o1->points[0].x - (b4)->points[0].x)*(o1->points[0].x - (b4)->points[0].x) + 
				(o1->points[0].y - (b4)->points[0].y)*(o1->points[0].y - (b4)->points[0].y);
			m2 = 1.25f*1.25f;
			if(m1 < m2){
				movey*=-1;
			}
}

void WorldDrawer2d::detectCP(){

	for(std::vector<Object2d*>::iterator it = players1.begin(); it!= players1.end(); it++){
		//if((*it) != curent){
			
			float m1 = (o1->points[0].x - (*it)->points[0].x)*(o1->points[0].x - (*it)->points[0].x) + 
				(o1->points[0].y - (*it)->points[0].y)*(o1->points[0].y - (*it)->points[0].y);
			float m2 = 1.5f*1.5f;
			
			if(m1 <= m2){
				float angle = atan(abs(o1->points[0].y - (*it)->points[0].y)/abs(o1->points[0].x - (*it)->points[0].x));
				WorldDrawer2d::animation = false;
				curent = (*it);
				curentteam = 1;
				totalangle = angle;
				colx = (*it)->points[0].x;
				coly = (*it)->points[0].y;
				fr = false;
				return;
			//}
		}
	}

	for(std::vector<Object2d*>::iterator it = players2.begin(); it!= players2.end(); it++){
		//if((*it) != curent){
			
			float m1 = (o1->points[0].x - (*it)->points[0].x)*(o1->points[0].x - (*it)->points[0].x) + 
				(o1->points[0].y - (*it)->points[0].y)*(o1->points[0].y - (*it)->points[0].y);
			float m2 = 1.5f*1.5f;

			if(m1 <= m2){
				float angle = atan(abs(o1->points[0].y - (*it)->points[0].y)/abs(o1->points[0].x - (*it)->points[0].x));
				WorldDrawer2d::animation = false;
				colx = (*it)->points[0].x;
				coly = (*it)->points[0].y;
				curent = (*it);
				curentteam = 2;
				totalangle = angle;
				fr = false;
				return;
			}
		//}
	}
}



int WorldDrawer2d::detectGol(){
	std::vector<Point2d> poarta1;
	std::vector<Point2d> poarta2;


	poarta1.push_back(Point2d(-4,19.7));
	poarta1.push_back(Point2d(4,19.7));
	poarta1.push_back(Point2d(-4,19.7));
	poarta1.push_back(Point2d(-4,18));
	poarta1.push_back(Point2d(4,19.7));
	poarta1.push_back(Point2d(4,18));

	poarta2.push_back(Point2d(-4.0f,-19.7f));
	poarta2.push_back(Point2d(4.0f,-19.7f));
	poarta2.push_back(Point2d(-4.0f,-18.0f));
	poarta2.push_back(Point2d(-4.0f,-19.7f));
	poarta2.push_back(Point2d(4.0f,-18.0f));
	poarta2.push_back(Point2d(4.0f,-19.7f));

	for(std::vector<Point2d>::iterator it = poarta1.begin(); it != poarta1.end(); it+=2){
		if(collisionCL(o1->points.at(0),sqrt((o1->points[0].x - o1->points[1].x)*(o1->points[0].x - o1->points[1].x) + 
			(o1->points[0].y - o1->points[1].y)*(o1->points[0].y - o1->points[1].y)),*it,*(it+1))){
				WorldDrawer2d::animation = false;
				o1->setcolor(1.0f,1.0f,1.0f);
				
				return 1;
		}
	}

	for(std::vector<Point2d>::iterator it = poarta2.begin(); it != poarta2.end(); it+=2){
		if(collisionCL(o1->points.at(0),sqrt((o1->points[0].x - o1->points[1].x)*(o1->points[0].x - o1->points[1].x) + 
			(o1->points[0].y - o1->points[1].y)*(o1->points[0].y - o1->points[1].y)),*it,*(it+1))){
				WorldDrawer2d::animation = false;
				o1->setcolor(0.0f,0.0f,0.0f);
				return 2;
		}
	}
	return 0;
}

bool oki[6] = {false,false,false,false,false,false};
void WorldDrawer2d::detectC(){

	std::vector<Point2d> collist;

	collist.push_back(Point2d(-12,18));
	collist.push_back(Point2d(-12,-18));
	collist.push_back(Point2d(12,18));
	collist.push_back(Point2d(12,-18));
	collist.push_back(Point2d(-12,18));
	collist.push_back(Point2d(-4,18));
	collist.push_back(Point2d(4,18));
	collist.push_back(Point2d(12,18));
	collist.push_back(Point2d(-12,-18));
	collist.push_back(Point2d(-4,-18));
	collist.push_back(Point2d(4,-18));
	collist.push_back(Point2d(12,-18));
	for(std::vector<Point2d>::iterator it = collist.begin(); it != collist.end(); it+=2){
		if(collisionCL(o1->points.at(0),sqrt((o1->points[0].x - o1->points[1].x)*(o1->points[0].x - o1->points[1].x) + 
			(o1->points[0].y - o1->points[1].y)*(o1->points[0].y - o1->points[1].y)),*it,*(it+1))){
				//coliziune cu marginea stanga
				if((*it).x == Point2d(-12,18).x && (*it).y == Point2d(-12,18).y && (*(it+1)).x == Point2d(-12,-18).x && (*(it+1)).y == Point2d(-12,-18).y){
					
						movex*= -1;
						
					
				}
				//coliziune cu dreapta 
				if((*it).x == Point2d(12,18).x && (*it).y == Point2d(12,18).y && (*(it+1)).x == Point2d(12,-18).x && (*(it+1)).y == Point2d(12,-18).y){
						
			
						
						movex*=-1;
					
				}
				// coliziune cu stanga sus 
				if((*it).x == Point2d(-12,18).x && (*it).y == Point2d(-12,18).y && (*(it+1)).x == Point2d(-4,18).x && (*(it+1)).y ==Point2d(-4,18).y){
						
				
						
						movey*=-1;
				}
				// dreapta sus
				if((*it).x == Point2d(4,18).x && (*it).y == Point2d(4,18).y && (*(it+1)).x == Point2d(12,18).x && (*(it+1)).y == Point2d(12,18).y){
						
						movey*= -1;
						
				}
				// stanga jos
				if((*it).x == Point2d(-12,-18).x && (*it).y == Point2d(-12,-18).y && (*(it+1)).x == Point2d(-4,-18).x && (*(it+1)).y == Point2d(-4,-18).y){
						
						movey*=-1;
						
				}
				//dreapta jos
				if((*it).x == Point2d(4,-18).x && (*it).y == Point2d(4,-18).y && (*(it+1)).x == Point2d(12,-18).x && (*(it+1)).y == Point2d(12,-18).y){
						
						movey*=-1;
						
				}
				
				
		}
	}

}

Object2d *z11,*z21,*z31,*z41,*z12,*z22,*z32,*z42;
Object2d *u1,*u2;
Object2d *d1,*d2,*d11,*d12;
Object2d *t1,*t2,*t3,*t11,*t12,*t13;
Object2d *x1,*x2;

void WorldDrawer2d::MakeZero(float r,float g, float b,Object2d** z1,Object2d** z2, Object2d**  z3,Object2d** z4,int sens){
	
	DrawFour(0.25f,3.0f,z1,r,g,b);
	DrawFour(0.25f,3.0f,z2,r,g,b);
	DrawFour(1.5f,0.25f,z3,r,g,b);
	DrawFour(1.5f,0.25f,z4,r,g,b);
	(*z1)->translate(14.5f,sens * 6.0f);
	(*z2)->translate(17.5f,sens * 6.0f);
	(*z3)->translate(16.0f,sens* 3.25f);
	(*z4)->translate(16.0f,sens* 8.75f);
}

void WorldDrawer2d::MakeUnu(float r,float g, float b,Object2d** z1,int sens){
	DrawFour(0.25f,3.0f,z1,r,g,b);
	(*z1)->translate(16.0f,sens * 6.0f);
}
void WorldDrawer2d::MakeX(float r,float g, float b,Object2d* z1,Object2d* z2,int sens){
	DrawFour(0.25f,2.0f,&z1,r,g,b);
	DrawFour(0.25,2.0f,&z2,r,g,b);
	(z1)->rotateRelativeToPoint(Point2d(0.0f,0.0f),3.1415f/4);
	(z1)->translate(16.0f,0.0f);
	(z2)->rotateRelativeToPoint(Point2d(0.0f,0.0f),-3.1415f/4);
	(z2)->translate(16.0f,0.0f);

}

void WorldDrawer2d::MakeDoi(float r,float g, float b,Object2d** z1,Object2d** z2,int sens){
	DrawFour(0.25f,2.0f,z1,r,g,b);
	DrawFour(0.25,2.0f,z2,r,g,b);
	(*z1)->translate(15.5f,sens*6.0f);
	(*z2)->translate(16.5f,sens*6.0f);
}

void WorldDrawer2d::MakeTrei(float r,float g, float b,Object2d** z1,Object2d** z2,Object2d** z3,int sens){
	DrawFour(0.25f,2.0f,z1,r,g,b);
	DrawFour(0.25,2.0f,z2,r,g,b);
	DrawFour(0.25,2.0f,z3,r,g,b);
	(*z1)->translate(15.0f,sens*6.0f);
	(*z2)->translate(16.0f,sens*6.0f);
	(*z3)->translate(17.0f,sens*6.0f);
}

bool ok11=false,ok12=false,ok21=false,ok22=false,ok01=false,ok02=false,ok31 = false,ok32 = false;

void WorldDrawer2d::DrawScore(float r1, float g1, float a1,float r2,float g2,float a2){
	
	MakeX(1.0f,1.0f,1.0f,x1,x2,1);
	if(scor.x == 0 && !ok01){
		if(ok31){
			
			cs1->objectRemove(t1);
			cs1->objectRemove(t2);
			cs1->objectRemove(t3);
		}
		if(ok11){
			cs1->objectRemove(u1);
		}
		if(ok21){
			cs1->objectRemove(d1);
			cs1->objectRemove(d2);
		}
		ok01=true;
		MakeZero(r1,g1,a1,&z11,&z21,&z31,&z41,1);
	}else if(scor.x == 1 && !ok11){
		ok11 = true;
		ok01 = false;
		cs1->objectRemove(z11);
		cs1->objectRemove(z21);
		cs1->objectRemove(z31);
		cs1->objectRemove(z41);

		MakeUnu(r1,g1,a1,&u1,1);
	}else if(scor.x == 2 && ! ok21){
		ok21 = true;
		ok11 = false;
		cs1->objectRemove(u1);
		MakeDoi(r1,g1,a1,&d1,&d2,1);
	}else if(scor.x == 3 ){
		ok31 = true;
		ok21 = false;
		cs1->objectRemove(d1);
		cs1->objectRemove(d2);
		MakeTrei(r1,g1,a1,&t1,&t2,&t3,1);

	}

	if(scor.y == 0 && !ok02){
		if(ok32 == true){
			cs1->objectRemove(t11);
			cs1->objectRemove(t12);
			cs1->objectRemove(t13);
		}
		if(ok12){
			cs1->objectRemove(u2);
		}
		if(ok22){
			cs1->objectRemove(d11);
			cs1->objectRemove(d12);
		}

		ok02 = true;
		MakeZero(r2,g2,a2,&z12,&z22,&z32,&z42,-1);
	}else if(scor.y == 1 && !ok12){
		ok12 = true;
		ok02 = false;
		cs1->objectRemove(z12);
		cs1->objectRemove(z22);
		cs1->objectRemove(z32);
		cs1->objectRemove(z42);

		MakeUnu(r2,g2,a2,&u2,-1);
	}else if(scor.y == 2 && !ok22){
		ok22 = true;
		ok12 = false;
		cs1->objectRemove(u2);
		MakeDoi(r2,g2,a2,&d11,&d12,-1);
	}else if(scor.y == 3){
		ok22 = false;
		ok32 = true;
		cs1->objectRemove(d11);
		cs1->objectRemove(d12);
		MakeTrei(r2,g2,a2,&t11,&t12,&t13,-1);
	
	}

}


int main(int argc, char** argv){
	WorldDrawer2d wd2d(argc,argv,500,500,200,100,std::string("Fotbal"));
	wd2d.init();
	wd2d.run();
	return 0;
}