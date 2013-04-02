#include <string>
#include "LoadOFF.h"

using namespace std;

class Nava{
	public:
		Nava();
		~Nava();
		void render(Vector3D * mypos,int deseneaza);
		LoadOFF* nava;
		float trans;
		int health;

};