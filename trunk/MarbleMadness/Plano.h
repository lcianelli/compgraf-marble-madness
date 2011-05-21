#pragma once
#ifndef PLANO_H
#define PLANO_H

#include "Vector.h"
#include "Rayo.h"

class Plano
{
protected:
	Vector posicion;
	Vector normal;

public:

	//construye un plano por defecto
	Plano() { posicion = Vector(); normal = Vector();};
	//construye un plano a partir de un punto del mismo y su normal
	Plano(const Vector &pos, const Vector &norm) : posicion(pos) {
		normal = Vector(norm).unitario();
	}
	//construye un plano con tres puntos del mismo
	Plano(const Vector &p1, const Vector &p2, const Vector &p3) : posicion(p1) {
		normal = Vector((p2-p1)*(p3-p1)).unitario();
	} 

	//devuelve 1 si el rayo se interseca con este plano. en lambda devuelve la distancia entre el plano y el rayo, y en pNormal la normal al plano.
	//devuelve 0 si el rayo no interseca al plano
	//devuelve -1 si lo interseca "por detras"
	int probarInterseccion(const Rayo &r, float &lambda, Vector &pNormal);
	int probarInterseccion(const Vector &posicion, const Vector& direccion, float &lambda, Vector &pNormal);

	Vector Normal() const { return normal;}
	Vector Posicion() const { return posicion;}


	~Plano(void);
};

#endif

