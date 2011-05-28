#pragma once
#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>
#include "Mathex.h"


class Rayo;

class Vector
{
public:
	enum TStatus { INVALID, DEFAULT, UNIT };

private:
	
	float _x, _y, _z;
	TStatus _status;
	Vector(float x, float y, float z, TStatus status) : _x(x), _y(y), _z(z), _status(status) {}
	

public:
	Vector(const Vector& v) : _x(v._x), _y(v._y), _z(v._z), _status(v._status) {}
	Vector() : _x(0.f), _y(0.f), _z(0.f), _status(INVALID) {}
	Vector(float x, float y, float z) : _x(x), _y(y), _z(z), _status(DEFAULT) {}
	Vector(float* floatv) : _x(floatv[0]), _y(floatv[1]), _z(floatv[2]), _status(DEFAULT) {}

	//creo el vector en el pto medio de dos lineas
	Vector(const Rayo &linea1, const Rayo &linea2);

	float X() const {return _x;}
	float Y() const  {return _y;}
	float Z() const {return _z;}

	bool esUnitario() const { return _status == UNIT; } 
	bool esDefecto() const {return _status == DEFAULT; }
	bool esValido() const { return _status != INVALID; }

	Vector &unitario();
	static Vector unitario(const Vector &v, Vector &resultado) {resultado = v; return resultado.unitario();}
	static Vector unitario(const Vector &v) {return Vector(v).unitario();}

	Vector &defecto();
	static Vector defecto(const Vector &v, Vector &resultado) {resultado = v; return resultado.defecto();}
	static Vector defecto(const Vector &v) {return Vector(v).defecto();}

	float norma() const { return ( sqrt(sqr(X())+sqr(Y())+sqr(Z())));}
	float norma2() const {return (esValido() ? (esUnitario() ? 1.f : (sqr(X())+sqr(Y())+sqr(Z()))) : 0.f);}
	
	//cambio isabela!!!
	//float escalar(const Vector &v) const { return ( (esValido() && v.esValido()) ? (X()*v.X() + Y()*v.Y() + Z()*v.Z()) : 0.f  ); }

	float escalar(const Vector &v) const { return ( (X()*v.X() + Y()*v.Y() + Z()*v.Z()) ); }

	static float escalar(const Vector &v1, const Vector &v2) { return v1.escalar(v2);}

	static Vector &suma(const Vector &v1, const Vector &v2, Vector &res);
	static Vector &resta(const Vector &v1, const Vector &v2, Vector &res);
	static Vector &prodCruzado(const Vector &v1, const Vector &v2, Vector &res);
	static Vector &invertir(const Vector &v, Vector &res);
	static Vector &multiplicar(const Vector &v, const float escala, Vector &res);

	Vector operator-() const {return invertir(*this, Vector());}
	Vector &operator+=(const Vector &v) {return suma(*this, v, *this);}
	Vector &operator-=(const Vector &v) {return resta(*this, v, *this);}
	Vector &operator*=(const Vector &v) {Vector vAux(*this); return prodCruzado(vAux, v, *this);}
	Vector &operator*=(const float escala) { return multiplicar(*this, escala, *this);}
	Vector operator+(const Vector &v) const { Vector ret; return suma(*this, v, ret);}
	Vector operator-(const Vector &v) const { Vector ret; return resta(*this, v, ret);}
	Vector operator*(const Vector &v) const { Vector ret; return prodCruzado(*this, v, ret);}
	Vector operator*(const float escala) const { Vector ret; return multiplicar(*this, escala, ret);}

	float dist(const Vector &v) const { return (*this-v).norma();}
	float distCuad(const Vector &v) const {return (*this-v).norma2();}
	
	float* floatArr() const { float* arr = new float[3];arr[0] = _x; arr[1] = _y; arr[2] = _z; return arr;}

	//agregamos 23/5/2011
	bool igual(const Vector &v){ return ((X()==v.X())&&(Y()==v.Y())&&(Z()==v.Z()));}

	void imprimir();

	~Vector(void);
};

#endif



