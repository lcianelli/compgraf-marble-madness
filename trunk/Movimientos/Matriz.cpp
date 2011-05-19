#include "Matriz.h"
#include "Vector.h"

Matriz::Matriz(void) {
	_Mx[0][0] = 1.f; _Mx[0][1] = 0.f; _Mx[0][2] = 0.f;
	_Mx[1][0] = 0.f; _Mx[1][1] = 1.f; _Mx[1][2] = 0.f;
	_Mx[2][0] = 0.f; _Mx[2][1] = 0.f; _Mx[2][2] = 1.f;
}

Matriz::Matriz(float phi, float theta, float psi) {
	float c1 = cos(phi), s1 = sin(phi), c2=cos(theta), s2 = sin(theta), c3 = cos(psi), s3 = sin(psi);
	_Mx[0][0]= c2*c3;
	_Mx[0][1]= -c2*s3;
	_Mx[0][2]= s2;
	_Mx[1][0]= s1*s2*c3+c1*s3;
	_Mx[1][1]= s1*s2*c3+c1*c3;
	_Mx[1][2]= s1*c2;
	_Mx[2][0]= c1*s2*c3+s1*s3;
	_Mx[2][1]= c1*s2*s3+s1*c3;
	_Mx[2][2]= c1*c2;
}

Matriz::Matriz(float mx00, float mx01, float mx02, float mx10, float mx11, float mx12, float mx20, float mx21, float mx22){
	_Mx[0][0] = mx00; _Mx[0][1] = mx01; _Mx[0][2] = mx02;
	_Mx[1][0] = mx10; _Mx[1][1] = mx11; _Mx[1][2] = mx12;
	_Mx[2][0] = mx20; _Mx[2][1] = mx21; _Mx[2][2] = mx22;
}

Matriz &Matriz::suma(const Matriz &m1, const Matriz &m2, Matriz &res) {
	res._Mx[0][0] = m1._Mx[0][0] + m2._Mx[0][0];
	res._Mx[0][1] = m1._Mx[0][1] + m2._Mx[0][1];
	res._Mx[0][2] = m1._Mx[0][2] + m2._Mx[0][2];
	res._Mx[1][0] = m1._Mx[1][0] + m2._Mx[1][0];
	res._Mx[1][1] = m1._Mx[1][1] + m2._Mx[1][1];
	res._Mx[1][2] = m1._Mx[1][2] + m2._Mx[1][2];
	res._Mx[2][0] = m1._Mx[2][0] + m2._Mx[2][0];
	res._Mx[2][1] = m1._Mx[2][1] + m2._Mx[2][1];
	res._Mx[2][2] = m1._Mx[2][2] + m2._Mx[2][2];
	return res;
	
}

Matriz &Matriz::resta(const Matriz &m1, const Matriz &m2, Matriz &res) {
	res._Mx[0][0] = m1._Mx[0][0] - m2._Mx[0][0];
	res._Mx[0][1] = m1._Mx[0][1] - m2._Mx[0][1];
	res._Mx[0][2] = m1._Mx[0][2] - m2._Mx[0][2];
	res._Mx[1][0] = m1._Mx[1][0] - m2._Mx[1][0];
	res._Mx[1][1] = m1._Mx[1][1] - m2._Mx[1][1];
	res._Mx[1][2] = m1._Mx[1][2] - m2._Mx[1][2];
	res._Mx[2][0] = m1._Mx[2][0] - m2._Mx[2][0];
	res._Mx[2][1] = m1._Mx[2][1] - m2._Mx[2][1];
	res._Mx[2][2] = m1._Mx[2][2] - m2._Mx[2][2];
	return res;	
}

Matriz &Matriz::multiplicar(const Matriz &m1, const Matriz &m2, Matriz &res) {
	res._Mx[0][0] = m1._Mx[0][0]*m2._Mx[0][0] + m1._Mx[0][1]*m2._Mx[1][0] + m1._Mx[0][2]*m2._Mx[2][0];
	res._Mx[0][1] = m1._Mx[1][0]*m2._Mx[0][0] + m1._Mx[1][1]*m2._Mx[1][0] + m1._Mx[1][2]*m2._Mx[2][0];
	res._Mx[0][2] = m1._Mx[2][0]*m2._Mx[0][0] + m1._Mx[2][1]*m2._Mx[1][0] + m1._Mx[2][2]*m2._Mx[2][0];
	res._Mx[1][0] = m1._Mx[0][0]*m2._Mx[0][1] + m1._Mx[0][1]*m2._Mx[1][1] + m1._Mx[0][2]*m2._Mx[2][1];
	res._Mx[1][1] = m1._Mx[1][0]*m2._Mx[0][1] + m1._Mx[1][1]*m2._Mx[1][1] + m1._Mx[1][2]*m2._Mx[2][1];
	res._Mx[1][2] = m1._Mx[2][0]*m2._Mx[0][1] + m1._Mx[2][1]*m2._Mx[1][1] + m1._Mx[2][2]*m2._Mx[2][1];
	res._Mx[2][0] = m1._Mx[0][0]*m2._Mx[0][2] + m1._Mx[0][1]*m2._Mx[1][2] + m1._Mx[0][2]*m2._Mx[2][2];
	res._Mx[2][1] = m1._Mx[1][0]*m2._Mx[0][2] + m1._Mx[1][1]*m2._Mx[1][2] + m1._Mx[1][2]*m2._Mx[2][2];
	res._Mx[2][2] = m1._Mx[2][0]*m2._Mx[0][2] + m1._Mx[2][1]*m2._Mx[1][2] + m1._Mx[2][2]*m2._Mx[2][2];
	return res;
}

Matriz &Matriz::multiplicar(const Matriz &m1, const float &escala, Matriz &res) {
	res._Mx[0][0] = m1._Mx[0][0] * escala;
	res._Mx[0][1] = m1._Mx[0][1] * escala;
	res._Mx[0][2] = m1._Mx[0][2] * escala;
	res._Mx[1][0] = m1._Mx[1][0] * escala;
	res._Mx[1][1] = m1._Mx[1][1] * escala;
	res._Mx[1][2] = m1._Mx[1][2] * escala;
	res._Mx[2][0] = m1._Mx[2][0] * escala;
	res._Mx[2][1] = m1._Mx[2][1] * escala;
	res._Mx[2][2] = m1._Mx[2][2] * escala;
	return res;	
}

Vector &Matriz::multiplicar(const Matriz &m1, const Vector &v, Vector &result) {
	result = Vector(m1._Mx[0][0]*v.X() + m1._Mx[0][1]*v.Y() + m1._Mx[0][2]*v.Z(),
						m1._Mx[1][0]*v.X() + m1._Mx[1][1]*v.Y() + m1._Mx[1][2]*v.Z(),
						m1._Mx[2][0]*v.X() + m1._Mx[2][1]*v.Y() + m1._Mx[2][2]*v.Z());
	return result;
}

float Matriz::determinante() const {
	return _Mx[0][0]*(_Mx[1][1]*_Mx[2][2]-_Mx[1][2]*_Mx[2][1]) 
		- _Mx[0][1]*(_Mx[1][0]*_Mx[2][2]-_Mx[1][2]*_Mx[2][0])
		+ _Mx[0][2]*(_Mx[1][0]*_Mx[2][1]-_Mx[1][1]*_Mx[2][0]);
}

Matriz &Matriz::trasponer() {
	float t = _Mx[0][2]; _Mx[0][2] = _Mx[2][0]; _Mx[2][0] = t;
	t = _Mx[0][1]; _Mx[0][1] = _Mx[1][0]; _Mx[1][0] = t;
	t = _Mx[1][2]; _Mx[1][2] = _Mx[2][1]; _Mx[2][1] = t;
	return *this;
}

Matriz &Matriz::inversa(const Matriz &m1, Matriz &res) {
	float det = m1.determinante();
	if (fabs(det) < EPSILON){
		res = Matriz();
		return res;
	} else {
		res._Mx[0][0] = m1._Mx[1][1]*m1._Mx[2][2] - m1._Mx[1][2]*m1._Mx[2][1];
		res._Mx[0][1] = m1._Mx[2][1]*m1._Mx[0][2] - m1._Mx[2][2]*m1._Mx[0][1];
		res._Mx[0][2] = m1._Mx[0][1]*m1._Mx[1][2] - m1._Mx[0][2]*m1._Mx[1][1];
		res._Mx[1][0] = m1._Mx[1][2]*m1._Mx[2][0] - m1._Mx[1][0]*m1._Mx[2][2];
		res._Mx[1][1] = m1._Mx[2][2]*m1._Mx[0][0] - m1._Mx[2][0]*m1._Mx[0][2];
		res._Mx[1][2] = m1._Mx[0][2]*m1._Mx[1][0] - m1._Mx[0][0]*m1._Mx[1][2];
		res._Mx[2][0] = m1._Mx[1][0]*m1._Mx[2][1] - m1._Mx[1][1]*m1._Mx[2][0];
		res._Mx[2][1] = m1._Mx[2][0]*m1._Mx[0][1] - m1._Mx[2][1]*m1._Mx[0][0];
		res._Mx[2][2] = m1._Mx[0][0]*m1._Mx[1][1] - m1._Mx[0][1]*m1._Mx[1][0];
		return multiplicar(res, 1.f/det, res);
	}

}

Vector Matriz::operator*(const Vector &v) const {
	Vector tv;
	return multiplicar(*this, v, tv);
}

Matriz::~Matriz(void)
{
}

