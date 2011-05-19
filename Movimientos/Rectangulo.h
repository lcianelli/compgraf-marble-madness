#pragma once
#ifndef RECTANGULO_H
#define RECTANGULO_H

#include "Plano.h"

//un rectangulo es un plano tal que tiene dimensiones definidas, las cuales se toman desde el punto posicion del plano
//llegando al punto posOpuesto,que es el punto opuesto sobre el mismo lado que tiene largo "h"
class Rectangulo : public Plano
{
protected:
	float _w, _h;
	Vector posOpuesto;
	Vector p1, p2, p3, p4;
public:
	Rectangulo() : Plano() {
		_w = 0.f;
		_h = 0.f;
	}

	Rectangulo(const Vector &punto, const Vector &normal, const Vector& opuesto, float w, float h) : Plano(punto, normal) {
		posOpuesto = Vector(opuesto).unitario();
		_w = w;
		_h = h;
		p1 = Posicion();
		p2= posOpuesto*w + Posicion();
		p3 = (Normal()*(p2-p1)).unitario()*h + p1;
		p4 = p3+(p2-p1);
	}

	Rectangulo(const Plano &p, const Vector& opuesto, float w, float h) {
		posicion = p.Posicion();
		normal = p.Normal();
		posOpuesto = Vector(opuesto).unitario();
		_w = w;
		_h = h;
		p1 = Posicion();
		p2= posOpuesto*w + Posicion();
		p3 = (Normal()*(p2-p1)).unitario()*h + p1;
		p4 = p3+(p2-p1);
	}

	//Rectangulo(const Plano &p, const Vector& opuesto);

	float W() const {return _w;}
	float H() const {return _h;}
	Vector P1() { return p1; }
	Vector P2() { return p2; }
	Vector P3() { return p3; }
	Vector P4() { return p4; }

	Vector opuesto() { return posOpuesto; }
	virtual float probarInterseccion(const Rayo r, float &distancia, Vector &pNormal, Vector &interseccion);

	

	~Rectangulo(void);
};


#endif

