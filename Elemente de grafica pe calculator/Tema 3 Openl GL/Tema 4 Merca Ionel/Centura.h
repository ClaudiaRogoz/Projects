#include "Vector3D.h"
#include "Asteroid.h"
#include <vector>

using namespace std;

class Centura{

	public:
		Centura();
		Centura(Vector3D poz,int size, Vector3D color);
		~Centura();
		void Render();
		void init();
		vector<Asteroid *> asteroizi;
		int size;
};