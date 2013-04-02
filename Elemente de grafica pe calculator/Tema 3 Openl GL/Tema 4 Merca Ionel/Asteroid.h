#include "Vector3D.h"
#include <ctime>
#include <iostream>

class Asteroid{

	public:
		Asteroid(int seed);
		Asteroid(Vector3D poz,int size, Vector3D color);
		~Asteroid();
		void Render();
		void init(int seed);
		void move();
		Vector3D pozitie,culoare;
		float size,speed;
		bool alive;
		int seed;
	private:
		float MAXX,MINX,MAXY,MINY,MAXZ,MINZ,MAXSIZE,MINSIZE,MINSPEED,MAXSPEED;
};