#include "stdafx.h"
#include "Matriz.h"
#include "Vector.h"

Matriz::Matriz(void) {
	_Mx[0][0] = 1.f; _Mx[0][1] = 0.f; _Mx[0][2] = 0.f; _Mx[0][3] = 0.f;
	_Mx[1][0] = 0.f; _Mx[1][1] = 1.f; _Mx[1][2] = 0.f; _Mx[1][3] = 0.f;
	_Mx[2][0] = 0.f; _Mx[2][1] = 0.f; _Mx[2][2] = 1.f; _Mx[2][3] = 0.f;
	_Mx[3][0] = 0.f; _Mx[3][1] = 0.f; _Mx[3][2] = 0.f; _Mx[3][3] = 1.f;
}

//1 es segun el eje x, 2 segun el eje y y 3 segun el eje z
Matriz::Matriz(float phi,int xyz) {
	float c1 = cos(phi);
	float s1 = sin(phi);	
	
	if(xyz==1) //Matriz de rotacion respecto al eje x
	{
	_Mx[0][0]= 1.f;
	_Mx[0][1]= 0.f;
	_Mx[0][2]= 0.f;
	_Mx[0][3]= 0.f;
	_Mx[1][0]= 0.0;
	_Mx[1][1]= c1;
	_Mx[1][2]= -s1;
	_Mx[1][3]= 0.f;
	_Mx[2][0]= 0.f;
	_Mx[2][1]= s1;
	_Mx[2][2]= c1;
	_Mx[2][3]= 0.f;
	_Mx[3][0]= 0.f;
	_Mx[3][1]= 0.f;
	_Mx[3][2]= 0.f;
	_Mx[3][3]= 1.f;
	}
	else if(xyz==2) //Matriz de rotacion respecto al eje y
	{
	_Mx[0][0]= c1;
	_Mx[0][1]= 0.f;
	_Mx[0][2]= s1;
	_Mx[0][3]= 0.f;
	_Mx[1][0]= 0.f;
	_Mx[1][1]= 1.f;
	_Mx[1][2]= 0.f;
	_Mx[1][3]= 0.f;
	_Mx[2][0]= -s1;
	_Mx[2][1]= 0.f;
	_Mx[2][2]= c1;
	_Mx[2][3]= 0.f;
	_Mx[3][0]= 0.f;
	_Mx[3][1]= 0.f;
	_Mx[3][2]= 0.f;
	_Mx[3][3]= 1.f;
	}
	else //Matriz de rotacion respecto al eje z
	{
	_Mx[0][0]= c1;
	_Mx[0][1]= -s1;
	_Mx[0][2]= 0.f;
	_Mx[0][3]= 0.f;
	_Mx[1][0]= s1;
	_Mx[1][1]= c1;
	_Mx[1][2]= 0.f;
	_Mx[1][3]= 0.f;
	_Mx[2][0]= 0.f;
	_Mx[2][1]= 0.f;
	_Mx[2][2]= 1.f;
	_Mx[2][3]= 0.f;
	_Mx[3][0]= 0.f;
	_Mx[3][1]= 0.f;
	_Mx[3][2]= 0.f;
	_Mx[3][3]= 1.f;	
	}
	
}

Matriz::Matriz(float mx00, float mx01, float mx02, float mx03, 
				float mx10, float mx11, float mx12, float mx13, 
					float mx20, float mx21, float mx22, float mx23,
						float mx30, float mx31, float mx32, float mx33){
	_Mx[0][0] = mx00; _Mx[0][1] = mx01; _Mx[0][2] = mx02; _Mx[0][3] = mx03;
	_Mx[1][0] = mx10; _Mx[1][1] = mx11; _Mx[1][2] = mx12; _Mx[1][3] = mx13;
	_Mx[2][0] = mx20; _Mx[2][1] = mx21; _Mx[2][2] = mx22; _Mx[2][3] = mx23;
	_Mx[3][0] = mx30; _Mx[3][1] = mx31; _Mx[3][2] = mx32; _Mx[3][3] = mx33;
	

}

float* Matriz::getMatrizVector()
{
	float* mVector= new float[16];
		mVector[0]=this->_Mx[0][0];
		mVector[1]=this->_Mx[1][0];
		mVector[2]=this->_Mx[2][0];
		mVector[3]=this->_Mx[3][0];
		mVector[4]=this->_Mx[0][1];
		mVector[5]=this->_Mx[1][1];
		mVector[6]=this->_Mx[2][1];
		mVector[7]=this->_Mx[3][1];
		mVector[8]=this->_Mx[0][2];
		mVector[9]=this->_Mx[1][2];
		mVector[10]=this->_Mx[2][2];
		mVector[11]=this->_Mx[3][2];
		mVector[12]=this->_Mx[0][3];
		mVector[13]=this->_Mx[1][3];
		mVector[14]=this->_Mx[2][3];
		mVector[15]=this->_Mx[3][3];
	return mVector;
}



Matriz &Matriz::suma(const Matriz &m1, const Matriz &m2, Matriz &res) {
	res._Mx[0][0] = m1._Mx[0][0] + m2._Mx[0][0];
	res._Mx[0][1] = m1._Mx[0][1] + m2._Mx[0][1];
	res._Mx[0][2] = m1._Mx[0][2] + m2._Mx[0][2];
	res._Mx[0][3] = m1._Mx[0][3] + m2._Mx[0][3];
	res._Mx[1][0] = m1._Mx[1][0] + m2._Mx[1][0];
	res._Mx[1][1] = m1._Mx[1][1] + m2._Mx[1][1];
	res._Mx[1][2] = m1._Mx[1][2] + m2._Mx[1][2];
	res._Mx[1][3] = m1._Mx[1][3] + m2._Mx[1][3];
	res._Mx[2][0] = m1._Mx[2][0] + m2._Mx[2][0];
	res._Mx[2][1] = m1._Mx[2][1] + m2._Mx[2][1];
	res._Mx[2][2] = m1._Mx[2][2] + m2._Mx[2][2];
	res._Mx[2][3] = m1._Mx[2][3] + m2._Mx[2][3];
	res._Mx[3][0] = m1._Mx[3][0] + m2._Mx[3][0];
	res._Mx[3][1] = m1._Mx[3][1] + m2._Mx[3][1];
	res._Mx[3][2] = m1._Mx[3][2] + m2._Mx[3][2];
	res._Mx[3][3] = m1._Mx[3][3] + m2._Mx[3][3];

	return res;
	
}

Matriz &Matriz::resta(const Matriz &m1, const Matriz &m2, Matriz &res) {
	res._Mx[0][0] = m1._Mx[0][0] - m2._Mx[0][0];
	res._Mx[0][1] = m1._Mx[0][1] - m2._Mx[0][1];
	res._Mx[0][2] = m1._Mx[0][2] - m2._Mx[0][2];
	res._Mx[0][3] = m1._Mx[0][3] - m2._Mx[0][3];
	res._Mx[1][0] = m1._Mx[1][0] - m2._Mx[1][0];
	res._Mx[1][1] = m1._Mx[1][1] - m2._Mx[1][1];
	res._Mx[1][2] = m1._Mx[1][2] - m2._Mx[1][2];
	res._Mx[1][3] = m1._Mx[1][3] - m2._Mx[1][3];
	res._Mx[2][0] = m1._Mx[2][0] - m2._Mx[2][0];
	res._Mx[2][1] = m1._Mx[2][1] - m2._Mx[2][1];
	res._Mx[2][2] = m1._Mx[2][2] - m2._Mx[2][2];
	res._Mx[2][3] = m1._Mx[2][3] - m2._Mx[2][3];
	res._Mx[3][0] = m1._Mx[3][0] - m2._Mx[3][0];
	res._Mx[3][1] = m1._Mx[3][1] - m2._Mx[3][1];
	res._Mx[3][2] = m1._Mx[3][2] - m2._Mx[3][2];
	res._Mx[3][3] = m1._Mx[3][3] - m2._Mx[3][3];
	return res;	
}

Matriz Matriz::multiplicar(Matriz m2) {
	Matriz res=Matriz();
	res._Mx[0][0] = this->_Mx[0][0]*m2._Mx[0][0] + this->_Mx[0][1]*m2._Mx[1][0] + this->_Mx[0][2]*m2._Mx[2][0]+ this->_Mx[0][3]*m2._Mx[3][0];
	res._Mx[1][0] = this->_Mx[1][0]*m2._Mx[0][0] + this->_Mx[1][1]*m2._Mx[1][0] + this->_Mx[1][2]*m2._Mx[2][0]+ this->_Mx[1][3]*m2._Mx[3][0];
	res._Mx[2][0] = this->_Mx[2][0]*m2._Mx[0][0] + this->_Mx[2][1]*m2._Mx[1][0] + this->_Mx[2][2]*m2._Mx[2][0]+ this->_Mx[2][3]*m2._Mx[3][0];
	res._Mx[3][0] = this->_Mx[3][0]*m2._Mx[0][0] + this->_Mx[3][1]*m2._Mx[1][0] + this->_Mx[3][2]*m2._Mx[2][0]+ this->_Mx[3][3]*m2._Mx[3][0];
	
	res._Mx[0][1] = this->_Mx[0][0]*m2._Mx[0][1] + this->_Mx[0][1]*m2._Mx[1][1] + this->_Mx[0][2]*m2._Mx[2][1] +this->_Mx[0][3]*m2._Mx[3][1];	
	res._Mx[1][1] = this->_Mx[1][0]*m2._Mx[0][1] + this->_Mx[1][1]*m2._Mx[1][1] + this->_Mx[1][2]*m2._Mx[2][1] +this->_Mx[1][3]*m2._Mx[3][1];
	res._Mx[2][1] = this->_Mx[2][0]*m2._Mx[0][1] + this->_Mx[2][1]*m2._Mx[1][1] + this->_Mx[2][2]*m2._Mx[2][1] +this->_Mx[2][3]*m2._Mx[3][1];
	res._Mx[3][1] = this->_Mx[3][0]*m2._Mx[0][1] + this->_Mx[3][1]*m2._Mx[1][1] + this->_Mx[3][2]*m2._Mx[2][1] +this->_Mx[3][3]*m2._Mx[3][1];

	res._Mx[0][2] = this->_Mx[0][0]*m2._Mx[0][2] + this->_Mx[0][1]*m2._Mx[1][2] + this->_Mx[0][2]*m2._Mx[2][2] +this->_Mx[0][3]*m2._Mx[3][2];	
	res._Mx[1][2] = this->_Mx[1][0]*m2._Mx[0][2] + this->_Mx[1][1]*m2._Mx[1][2] + this->_Mx[1][2]*m2._Mx[2][2] +this->_Mx[1][3]*m2._Mx[3][2];
	res._Mx[2][2] = this->_Mx[2][0]*m2._Mx[0][2] + this->_Mx[2][1]*m2._Mx[1][2] + this->_Mx[2][2]*m2._Mx[2][2] +this->_Mx[2][3]*m2._Mx[3][2];
	res._Mx[3][2] = this->_Mx[3][0]*m2._Mx[0][2] + this->_Mx[3][1]*m2._Mx[1][2] + this->_Mx[3][2]*m2._Mx[2][2] +this->_Mx[3][3]*m2._Mx[3][2];

	res._Mx[0][3] = this->_Mx[0][0]*m2._Mx[0][3] + this->_Mx[0][1]*m2._Mx[1][3] + this->_Mx[0][2]*m2._Mx[2][3] +this->_Mx[0][3]*m2._Mx[3][3];	
	res._Mx[1][3] = this->_Mx[1][0]*m2._Mx[0][3] + this->_Mx[1][1]*m2._Mx[1][3] + this->_Mx[1][2]*m2._Mx[2][3] +this->_Mx[1][3]*m2._Mx[3][3];
	res._Mx[2][3] = this->_Mx[2][0]*m2._Mx[0][3] + this->_Mx[2][1]*m2._Mx[1][3] + this->_Mx[2][2]*m2._Mx[2][3] +this->_Mx[2][3]*m2._Mx[3][3];
	res._Mx[3][3] = this->_Mx[3][0]*m2._Mx[0][3] + this->_Mx[3][1]*m2._Mx[1][3] + this->_Mx[3][2]*m2._Mx[2][3] +this->_Mx[3][3]*m2._Mx[3][3];	

	return res;
}

//Multiplica una matriz de 4x4 por el float que se le pasa de parametro y retorna la matriz resultante
Matriz Matriz::multiplicar(float escala) {
	Matriz res=Matriz();
	res._Mx[0][0] = this->_Mx[0][0] * escala;
	res._Mx[0][1] = this->_Mx[0][1] * escala;
	res._Mx[0][2] = this->_Mx[0][2] * escala;
	res._Mx[0][3] = this->_Mx[0][3] * escala;
	res._Mx[1][0] = this->_Mx[1][0] * escala;
	res._Mx[1][1] = this->_Mx[1][1] * escala;
	res._Mx[1][2] = this->_Mx[1][2] * escala;
	res._Mx[1][3] = this->_Mx[1][3] * escala;
	res._Mx[2][0] = this->_Mx[2][0] * escala;
	res._Mx[2][1] = this->_Mx[2][1] * escala;
	res._Mx[2][2] = this->_Mx[2][2] * escala;
	res._Mx[2][3] = this->_Mx[2][3] * escala;
	res._Mx[3][0] = this->_Mx[3][0] * escala;
	res._Mx[3][1] = this->_Mx[3][1] * escala;
	res._Mx[3][2] = this->_Mx[3][2] * escala;
	res._Mx[3][3] = this->_Mx[3][3] * escala;
	return res;	
}

//Multiplica la matriz por el vector v. Asume la 4ta componente del vector=1. Retorna un vector de 4 elementos.
float* Matriz::multiplicar(Vector v) {
	float* result=new float[3];
	result[0]= this->_Mx[0][0]*v.X() + this->_Mx[0][1]*v.Y() + this->_Mx[0][2]*v.Z()+this->_Mx[0][3];
	result[1]= this->_Mx[1][0]*v.X() + this->_Mx[1][1]*v.Y() + this->_Mx[1][2]*v.Z()+this->_Mx[1][3];
	result[2]= this->_Mx[2][0]*v.X() + this->_Mx[2][1]*v.Y() + this->_Mx[2][2]*v.Z()+this->_Mx[2][3];
	result[3]= this->_Mx[3][0]*v.X() + this->_Mx[3][1]*v.Y() + this->_Mx[3][2]*v.Z()+this->_Mx[3][3];
	return result;
}

float Matriz::determinante(){
	float det= this->_Mx[0][0]*(this->_Mx[1][1]*this->_Mx[2][2]*this->_Mx[3][3]+this->_Mx[2][1]*this->_Mx[3][2]*this->_Mx[1][3]+this->_Mx[3][1]*this->_Mx[1][2]*this->_Mx[2][3]-(this->_Mx[2][1]*this->_Mx[1][2]*this->_Mx[3][3]+this->_Mx[1][1]*this->_Mx[3][2]*this->_Mx[2][3] + this->_Mx[3][1]*this->_Mx[2][2]*this->_Mx[1][3]));
	det=det-this->_Mx[1][0]*(this->_Mx[0][1]*this->_Mx[2][2]*this->_Mx[3][3]+this->_Mx[2][1]*this->_Mx[3][2]*this->_Mx[0][3]+this->_Mx[3][1]*this->_Mx[0][2]*this->_Mx[2][3]-(this->_Mx[2][1]*this->_Mx[0][2]*this->_Mx[3][3]+this->_Mx[0][1]*this->_Mx[3][2]*this->_Mx[2][3] + this->_Mx[3][1]*this->_Mx[2][2]*this->_Mx[0][3]));
	det=det+this->_Mx[2][0]*(this->_Mx[0][1]*this->_Mx[1][2]*this->_Mx[3][3]+this->_Mx[1][1]*this->_Mx[3][2]*this->_Mx[0][3]+this->_Mx[3][1]*this->_Mx[0][2]*this->_Mx[1][3]-(this->_Mx[1][1]*this->_Mx[0][2]*this->_Mx[3][3]+this->_Mx[0][1]*this->_Mx[3][2]*this->_Mx[1][3] + this->_Mx[3][1]*this->_Mx[1][2]*this->_Mx[0][3]));
	det=det-this->_Mx[3][0]*(this->_Mx[0][1]*this->_Mx[1][2]*this->_Mx[2][3]+this->_Mx[1][1]*this->_Mx[2][2]*this->_Mx[0][3]+this->_Mx[2][1]*this->_Mx[0][2]*this->_Mx[1][3]-(this->_Mx[1][1]*this->_Mx[0][2]*this->_Mx[2][3]+this->_Mx[0][1]*this->_Mx[2][2]*this->_Mx[1][3] + this->_Mx[2][1]*this->_Mx[1][2]*this->_Mx[0][3]));
	return det;
}

Matriz &Matriz::trasponer() {
	float temp=_Mx[0][1];
	_Mx[0][1]=_Mx[1][0];
	_Mx[1][0]=temp;

	temp=_Mx[0][2];
	_Mx[0][2]=_Mx[2][0];
	_Mx[2][0]=temp;

	temp=_Mx[0][3];
	_Mx[0][3]=_Mx[3][0];
	_Mx[3][0]=temp;

	temp=_Mx[1][2];
	_Mx[1][2]=_Mx[2][1];
	_Mx[2][1]=temp;

	temp=_Mx[1][3];
	_Mx[1][3]=_Mx[3][1];
	_Mx[3][1]=temp;

	temp=_Mx[2][3];
	_Mx[2][3]=_Mx[3][2];
	_Mx[3][2]=temp;

	return *this;
}

Matriz Matriz::inversa() {
	float det = this->determinante();
	Matriz res = Matriz();
	if (fabs(det) < EPSILON){
		return res;
	} else {

		float p1=this->_Mx[0][1]*this->_Mx[1][0];
		float p2=this->_Mx[0][0]*this->_Mx[1][1];
		float p3=this->_Mx[0][0]*this->_Mx[1][2];
		float p4=this->_Mx[0][0]*this->_Mx[1][3];
		float p5=this->_Mx[2][1]*this->_Mx[3][0];
		float p6=this->_Mx[0][3]*this->_Mx[3][2];
		float p7=this->_Mx[2][2]*this->_Mx[3][3];
		float p8=this->_Mx[2][3]*this->_Mx[3][2];
		float p9=this->_Mx[2][1]*this->_Mx[3][3];
		float p10=this->_Mx[2][0]*this->_Mx[3][1];
		float p11=this->_Mx[2][1]*this->_Mx[3][2];
		float p12=this->_Mx[2][2]*this->_Mx[3][1];
		float p13=this->_Mx[0][1]*this->_Mx[1][2];
		float p14=this->_Mx[0][1]*this->_Mx[1][3];

		//revisado
		res._Mx[0][0] = this->_Mx[1][1]*p7+this->_Mx[1][2]*p8 + this->_Mx[1][3]*p11;
		res._Mx[0][0]-=(this->_Mx[1][1]*p8+this->_Mx[1][2]*p9+this->_Mx[1][3]*p12);

		//revisado
		res._Mx[0][1] = this->_Mx[0][1]*p8+this->_Mx[0][2]*p9 + p6*this->_Mx[2][2];
		res._Mx[0][1]-=(this->_Mx[0][1]*p7+this->_Mx[0][2]*this->_Mx[2][3]*this->_Mx[3][1]+p6*this->_Mx[2][1]);
		
		//revisado
		res._Mx[0][2] =p13*this->_Mx[3][3]+this->_Mx[0][2]*this->_Mx[1][3]*this->_Mx[3][1] + p6*this->_Mx[1][1];
		res._Mx[0][2]-=(p14*this->_Mx[3][2]+this->_Mx[0][2]*this->_Mx[1][1]*this->_Mx[3][3]+p6*this->_Mx[1][2]);
		
		//revisado
		res._Mx[0][3] =p14*this->_Mx[2][2]+this->_Mx[0][2]*this->_Mx[1][1]*this->_Mx[2][3] + this->_Mx[0][3]*this->_Mx[1][2]*this->_Mx[2][1];
		res._Mx[0][3]-=(p13*this->_Mx[2][3]+this->_Mx[0][2]*this->_Mx[1][3]*this->_Mx[2][1]+this->_Mx[0][3]*this->_Mx[1][1]*this->_Mx[2][2]);
		

		res._Mx[1][0] = this->_Mx[1][0]*p8+this->_Mx[1][2]*this->_Mx[2][0]*this->_Mx[3][3] + this->_Mx[1][3]*p12;
		res._Mx[1][0]-=(this->_Mx[1][0]*p7+this->_Mx[1][2]*this->_Mx[2][3]*this->_Mx[3][0]+this->_Mx[1][3]*this->_Mx[2][0]*this->_Mx[3][2]);
		
		res._Mx[1][1] = this->_Mx[0][0]*p7+this->_Mx[0][2]*this->_Mx[2][3]*this->_Mx[3][0] + p6*this->_Mx[2][0];
		res._Mx[1][1]-=(this->_Mx[0][0]*p8+this->_Mx[0][2]*this->_Mx[2][0]*this->_Mx[3][3]+this->_Mx[0][3]*p12);
		
		res._Mx[1][2] =p4*this->_Mx[3][2]+this->_Mx[0][2]*this->_Mx[1][0]*this->_Mx[3][3] + this->_Mx[0][3]*this->_Mx[1][2]*this->_Mx[3][0];
		res._Mx[1][2]-=(p3*this->_Mx[3][3]+this->_Mx[0][2]*this->_Mx[1][3]*this->_Mx[3][1]+p6*this->_Mx[1][0]);
		
		res._Mx[1][3] =p3*this->_Mx[2][3]+this->_Mx[0][2]*this->_Mx[1][3]*this->_Mx[2][0] + this->_Mx[0][3]*this->_Mx[1][0]*this->_Mx[2][2];
		res._Mx[1][3]-=(p4*this->_Mx[2][2]+this->_Mx[0][2]*this->_Mx[1][0]*this->_Mx[2][3]+this->_Mx[0][3]*this->_Mx[1][2]*this->_Mx[2][0]);
		
		res._Mx[2][0] = this->_Mx[1][0]*p9+this->_Mx[1][1]*this->_Mx[2][3]*this->_Mx[3][0] + this->_Mx[1][3]*p10;
		res._Mx[2][0]-=(this->_Mx[1][0]*this->_Mx[2][3]*this->_Mx[3][1]+this->_Mx[1][1]*this->_Mx[2][0]*this->_Mx[3][3]+this->_Mx[1][3]*p5);
		
		res._Mx[2][1] = this->_Mx[0][0]*this->_Mx[2][3]*this->_Mx[3][1]+this->_Mx[0][1]*this->_Mx[2][0]*this->_Mx[3][3] + this->_Mx[0][3]*p5;
		res._Mx[2][1]-=(this->_Mx[0][0]*p9+this->_Mx[0][1]*this->_Mx[2][3]*this->_Mx[3][0]+this->_Mx[0][3]*p10);
		
		res._Mx[2][2] =p2*this->_Mx[3][3]+p14*this->_Mx[3][0] + this->_Mx[0][3]*this->_Mx[1][0]*this->_Mx[3][1];
		res._Mx[2][2]-=(p4*this->_Mx[3][1]+p1*this->_Mx[3][3]+this->_Mx[0][3]*this->_Mx[1][0]*this->_Mx[3][0]);
		
		res._Mx[2][3] =p4*this->_Mx[2][1]+p1*this->_Mx[2][3] + this->_Mx[0][3]*this->_Mx[1][1]*this->_Mx[2][0];
		res._Mx[2][3] -=(p2*this->_Mx[2][3]+p14*this->_Mx[2][0]+this->_Mx[0][3]*this->_Mx[1][0]*this->_Mx[2][1]);
		
		res._Mx[3][0] = this->_Mx[1][0]*p12+this->_Mx[1][1]*this->_Mx[2][0]*this->_Mx[3][2] + this->_Mx[1][2]*p5;
		res._Mx[3][0] -=(this->_Mx[1][0]*p11+this->_Mx[1][1]*this->_Mx[2][2]*this->_Mx[3][0]+this->_Mx[1][2]*p10);
		
		res._Mx[3][1] = this->_Mx[0][0]*p11+this->_Mx[0][1]*this->_Mx[2][2]*this->_Mx[3][0] + this->_Mx[0][2]*p10;
		res._Mx[3][1] -=(this->_Mx[0][0]*p12+this->_Mx[0][1]*this->_Mx[2][0]*this->_Mx[3][2]+this->_Mx[0][2]*p5);

		res._Mx[3][2] =p3*this->_Mx[3][1]+p1*this->_Mx[3][2] + this->_Mx[0][2]*this->_Mx[1][1]*this->_Mx[3][0];
		res._Mx[3][2] -=(p2*this->_Mx[3][2]+p13*this->_Mx[3][0]+this->_Mx[0][2]*this->_Mx[1][0]*this->_Mx[3][1]);
		
		res._Mx[3][3] =p2*this->_Mx[2][2]+p13*this->_Mx[2][0] + this->_Mx[0][2]*this->_Mx[1][0]*this->_Mx[2][1];
		res._Mx[3][3]-=(p3*this->_Mx[2][1]+p1*this->_Mx[2][2]+this->_Mx[0][2]*this->_Mx[1][1]*this->_Mx[2][0]);

		return res.multiplicar(1.f/det);
	}

}



Matriz::~Matriz(void)
{
}

//Matriz &Matriz::trasladar(const Vector &vt) {
//	Matriz res(vt.X(), 0.f, 0.f, 0.f, vt.Y(), 0.f, 0.f, 0.f, vt.Z());
//	return multiplicar(*this, res, res);
//}
//
//Matriz &Matriz::rotar(const Vector &eje, float angulo) {
//	Matriz res(eje, angulo);
//	return multiplicar(*this, res, res);
//}

