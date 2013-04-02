#include <math.h>
#include <iostream>
using namespace std;

class Complex{

	public: 
		Complex();
		Complex(double  real,double  imag);
		~Complex();
		double  real,imag;
		double  modul();
		void inmultire(Complex* y);
		void plus(Complex* y);
		void toString();
};
