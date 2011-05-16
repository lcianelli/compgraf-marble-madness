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


#define BOLA_VEL_MAX 1.f

class Bola : public ObjetoDinamico
{
protected:
	bool acelerar;
	void interactuar(list<ObjetoJuego*>* interactores);
	/**
		Retorna el vector unitario de direccion y sentido de la fuerza que aplica este objeto sobre "obj"; el modulo real de la fuerza se retorna en "modulo"
	*/
	float* getFuerzaAplicada(ObjetoJuego* obj, float &modulo);

	float* getNormalInteraccion(ObjetoJuego* obj);
public:

	

	float r;
	float* centro;
	float* rotacion;
	void dibujar();
	void actualizar(int tiempo);//tiempo = tiempo transcurrido desde ultimo update
	void actualizarFisica(int tiempo); //tiempo = tiempo transcurrido desde ultimo update
	void setCentro(float cx, float cy, float cz);
	void setRotacion(float ax, float ay, float az);
	ObjetoEstatico* dondeEstoy();
	Bola(void);
	~Bola(void);
};

#endif

