#include "Complex.h"

Complex::Complex(){
	this->real = 0;
	this->imag = 0;
}

Complex::Complex(double  real, double  imag){
	this->real = real;
	this->imag = imag;
}

Complex::~Complex(){

}

double  Complex::modul(){

	return this->real*this->real + this->imag*this->imag;	
	
}


void Complex::inmultire( Complex* y){
	
	double  pr = this->real*y->real - this->imag*y->imag;
	double  ald = this->real*y->imag + this->imag*y->real;
	this->real = pr;
	this->imag = ald;
	
}

void Complex::toString(){
	cout<<this->real<<"  "<<this->imag<<"\n";
}

void Complex::plus(Complex *y){
	double pr = this->real+y->real;
	double ald = this->imag+y->imag;
	this->real = pr;
	this->imag = ald;
	
}
