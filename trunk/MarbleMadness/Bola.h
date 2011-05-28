#pragma once
#ifndef MARBLE_BOLA_H
#define MARBLE_BOLA_H

#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GL.h>
#include <gl\GLU.h>

#include "ObjetoDinamico.h"
#include "ObjetoJuego.h"
#include <iostream>
#include "Ambiente.h"
#include "Vector.h"
#include "Rayo.h"
#include "Rectangulo.h"
#include "Plano.h"
//#include "Nivel.h"

//class Nivel;

#define BOLA_VEL_MAX 1.f

class Bola : public ObjetoDinamico
{

public:

	float* centro;
	float* rotacion;
	void dibujar();
	void setCentro(float cx, float cy, float cz);
	void setRotacion(float ax, float ay, float az);
	ObjetoEstatico* dondeEstoy();
	void setPiso(ObjetoEstatico* obj);
	Bola(void);
	~Bola(void);
};

#endif MARBLE_BOLA_H;

