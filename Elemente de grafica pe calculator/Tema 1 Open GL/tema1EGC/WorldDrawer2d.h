#pragma once
#include "HeadersAndDefines.h"
#include "Support2d.h"


//-----------------------------------------------------------------------------------------------------
//	WorldDrawer2d
//	ca un obiect sa fie desenat trebuie sa fie atasat ori la cs_basis ori la un sistem de coordonate
//	din lista cs_used.
//-----------------------------------------------------------------------------------------------------
class WorldDrawer2d{
	public:
		//implemented in worldDrawer2d_gl .. not for lab1
		WorldDrawer2d(int argc, char **argv, int windowWidth, int windowHeight, int windowStartX, int windowStartY, std::string windowName);
		~WorldDrawer2d();
		static void run();	
		static void displayCallbackFunction();
		static void reshapeCallbackFunction(int width, int height);
		static void idleCallbackFunction();
		static void keyboardCallbackFunction(unsigned char key, int x, int y);
		static void keyboardSpecialCallbackFunction(int key, int x, int y);


		//implemented in worldDrawer2d_logic .. for lab1
		static void init();
		static void onIdle();
		static void onKey(unsigned char key);

	public:
		static void DrawCircle(Object2d** o1,float r,float g, float b);
		static void DrawField(float lung, float lat);
		static void DrawFour(float lung,float lat,Object2d ** o3,float r,float g,float a);
		static void DrawPlayers(std::vector<Object2d*>* vector,float r, float g, float b);
		static void putBall();
		static bool collisionCL(Point2d x, float raza, Point2d p1, Point2d p2);
		static void detectCB();
		static void detectC();
		static int detectGol();
		static void detectCP();
		static void giveBall(int team);
		static void MakeZero(float r,float g, float b,Object2d** z1,Object2d** z2, Object2d**  z3,Object2d** z4,int sens);
		static void MakeDoi(float r,float g, float b,Object2d** z3,Object2d** z4,int sens);
		static void MakeTrei(float r,float g, float b,Object2d** z1,Object2d**z2, Object2d** z3,int sens);
		static void MakeUnu(float r,float g, float b,Object2d** z4,int sens);
		static void MakeX(float r,float g, float b,Object2d* z4,Object2d* z5,int sens);
		static void DrawScore(float r1, float g1, float a1,float r2,float g2,float a2);
		static bool animation;
		static void DrawTribune(std::vector<Object2d*> * sp);
		static void Succes(int i);
		static std::vector<Object2d*> zero;
		static std::vector<Object2d*> unu;
		static std::vector<Object2d*> doi;
		static std::vector<Object2d*> trei;
		static std::vector<Object2d*> xx;
		static CoordinateSystem2d cs_basis;
		static std::vector<CoordinateSystem2d*> cs_used;
};