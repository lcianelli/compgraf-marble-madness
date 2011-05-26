#include "Vector.h"
#include "Rayo.h"

#include <stdio.h>

/*Vector::Vector(const Rayo &linea1, const Rayo &linea2) {
	Vector p1, p2;
	if (linea1.puntosAdyacentes(linea2, p1, p2)) {
		*this = (p1 + p2)*0.5f;
	} else {
		*this = Vector();
	}
}*/

Vector &Vector::unitario() {
	if (esDefecto()) {
		float norm = norma();
		if (norm < EPSILON) {
			_x = 0.f;
			_y = 0.f;
			_z = 0.f;
		} else {
			float temp = 1.f / norm;
			_x *= temp;
			_y *= temp;
			_z *= temp;
		}
		_status = UNIT;
	}

	return *this;
}

Vector &Vector::defecto() {
	if (esUnitario()) {
		_status = UNIT;
	}
	return *this;
}

Vector &Vector::invertir(const Vector &v, Vector &res) {
	if (v.esValido()) {
		res._x = -v._x;
		res._y = -v._y;
		res._z = -v._z;
		res._status = v._status;
	} else {
		res = Vector();
	}
	return res;
}

Vector &Vector::suma(const Vector &v1, const Vector &v2, Vector &res) {
	if (v1.esValido() && v2.esValido()) {
		res._x = v1._x + v2._x;
		res._y = v1._y + v2._y;
		res._z = v1._z + v2._z;
		res._status = DEFAULT;
	} else {
		res = Vector();
	}
	return res;
}

Vector &Vector::resta(const Vector &v1, const Vector &v2, Vector &res) {
	if (v1.esValido() && v2.esValido()) {
		res._x = v1._x - v2._x;
		res._y = v1._y - v2._y;
		res._z = v1._z - v2._z;
		res._status = DEFAULT;
	} else {
		res = Vector();
	}
	return res;
}

Vector &Vector::prodCruzado(const Vector &v1, const Vector &v2, Vector &res) {
	
	if (v1.esValido() && v2.esValido()) {

		res._x = v1._y*v2._z - v1._z*v2._y;
		res._y = v1._z*v2._x - v1._x*v2._z;
		res._z = v1._x*v2._y - v1._y*v2._x;

		res._status = DEFAULT;
	} else {
		res = Vector();
	}
	return res;
}

Vector &Vector::multiplicar(const Vector &v, const float escala, Vector &res) {
	if (v.esValido()) {
		res._x = v._x * escala;
		res._y = v._y * escala;
		res._z = v._z * escala;
		res._status = DEFAULT;
	} else {
		res = Vector();
	}
	return res;
}

void Vector::imprimir(){
	printf("Vector: %f %f %f \n",X(),Y(),Z());

}



Vector::~Vector(void)
{
}
