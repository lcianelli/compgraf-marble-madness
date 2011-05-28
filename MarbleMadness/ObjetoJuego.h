#pragma once
#ifndef MARBLE_OBJETO_JUEGO
#define MARBLE_OBJETO_JUEGO

#include <list>
#include "Ambiente.h"
#include "Vector.h"

using namespace std;

class ObjetoJuego
{

public:
	float* velocidad;
	Ambiente* ambiente;
	virtual void dibujar() = 0;
	virtual bool esEstatico() = 0; //Indica si este objeto es o no estatico
	ObjetoJuego(void);
	virtual ~ObjetoJuego(void);
};


#endif
