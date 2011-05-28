#pragma once

#ifndef MARBLE_PRISMA_H
#define MARBLE_PRISMA_H

#include "ObjetoEstatico.h"
#include <list>
#include <SDL_opengl.h>
#include <gl\GL.h>
#include <gl\GLU.h>

#include "Vector.h"

class Prisma : public ObjetoEstatico
{
protected:

	GLMmodel* objeto;

public:
	float l, w, h; //dimensiones del prisma, ancho, alto, y largo
	float *a;
	float froz;

	Prisma(void);
	Vector getNormalInteraccion(float* vectorDireccion, Vector &ptoCara); 	
	void dibujar();
	~Prisma(void);
};

#endif

