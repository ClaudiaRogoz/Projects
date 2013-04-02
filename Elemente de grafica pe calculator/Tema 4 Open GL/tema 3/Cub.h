//glut and glew
#pragma once
#include "glut.h"
#include "TargaImage.h"
#include "Vector3D.h"



class Cub{
	public:
		
		Cub(GLfloat trax,GLfloat tray,GLfloat traz,float size,int ind);
		~Cub();
		Vector3D C1();
		Vector3D C2();
		int ind;
		void init();
		void DrawCub();
		void DrawCubU();
		GLfloat trax,tray,traz;
		float size;
	private:
		TargaImage *m_textureOne;

		unsigned int m_textureObjectOne;
		
		
		
		GLuint _textureId;

};