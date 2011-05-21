#pragma once
#ifndef RAYO_H
#define RAYO_H

#include "Mathex.h"
#include "Vector.h"

class Rayo
{
private:
	Vector _P;//un punto de la linea/rayo
	Vector _V;//vector de dirección del rayo
public:
	Rayo() {}
	Rayo(const Vector &punto, const Vector &punto2);

	bool puntosAdyacentes(const Rayo &rayo, Vector &punto1, Vector &punto2) const;

	static Rayo &invertir(const Rayo &r, Rayo &resultado) {resultado._P = r._P; Vector::invertir(r._V, resultado._V); return resultado;}

	Rayo operator-() const {return invertir(*this, Rayo());}
	
	Vector V() const {return _V;}
	Vector P() const {return _P;}
	bool esValido() const { return V().esUnitario() && P().esValido(); } 


	float dist(const Rayo &r) const;
	float dist(const Vector &punto) const;

	//~Rayo(void);
};

#endif
