#include <cstdlib>
#include "dependente\freeglut.h"


class Cube{
	public:
		enum Layer{
			L_F1, 
			L_F2,
			L_F3,
			L_L1,
			L_L2,
			L_L3,
			L_D1,
			L_D2,
			L_D3 ,
			NONE
		};
		static int retnrLayer(Layer l);
		Layer layer1,layer2,layer3;
		GLfloat trax,tray,traz;
		Cube(Layer layer1,Layer layer2,Layer layer3,GLfloat trax,GLfloat tray,GLfloat traz);
		
		~Cube();
		int face;
		void Rubik(GLfloat size);
		void Draw(GLfloat size,int type);

		void DrawCube(GLfloat size);
		void DrawCubeT(GLfloat size);


};