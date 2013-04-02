#include "glut.h"

class Sphere{
	public:
		Sphere(float radius, float s1,float s2);
		~Sphere();
		void translateSphere(float trax,float tray,float traz);
		void rotateSphere(float angle,float trax,float tray,float traz);
	private:
		float radius,centerx,centery,centerz,s1,s2;

};