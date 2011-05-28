#pragma once

#ifndef MARBLE_Rampa_H
#define MARBLE_Rampa_H

#include "ObjetoEstatico.h"
#include <list>
#include <SDL_opengl.h>
#include <gl\GL.h>
#include <gl\GLU.h>

#include "Vector.h"


class Rampa : public ObjetoEstatico
{
protected:
	GLMmodel* objeto;

public:
	float l, w, h; //dimensiones del Rampa, ancho, alto, y largo
	float *a;
	float froz;

	Rampa(void);
	
	void setAlturaSueloRampa(int nuevaAltura);
	Vector getNormalInteraccion(float* vectorDireccion, Vector &ptoCara);

	void dibujar();

	~Rampa(void);
};

#endif

