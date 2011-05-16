#pragma once
#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "Bola.h"

class Personaje :
	public Bola
{
public:
	Personaje(void);
	~Personaje(void);

	void moverArriba();
	void moverAbajo();
	void moverDerecha();
	void moverIquierda();
	void detenerArriba();
	void detenerAbajo();
	void detenerDerecha();
	void detenerIquierda();
};

#endif

