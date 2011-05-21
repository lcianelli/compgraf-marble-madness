#pragma once

#ifndef MARBLE_Rampa_H
#define MARBLE_Rampa_H

#include "ObjetoEstatico.h"
#include <list>
#include <SDL_opengl.h>
#include <gl\GL.h>
#include <gl\GLU.h>


class Rampa : public ObjetoEstatico
{
protected:
	void interactuar(list<ObjetoJuego*>* interactores);
	/**
		Retorna el vector unitario de direccion y sentido de la fuerza que aplica este objeto sobre "obj"; el modulo real de la fuerza se retorna en "modulo"
	*/
	float* getFuerzaAplicada(ObjetoJuego* obj, float &modulo);
	
	float* getNormalInteraccion(ObjetoJuego* obj);

	GLMmodel* objeto;

public:
	float l, w, h; //dimensiones del Rampa, ancho, alto, y largo
	float *a;
	float froz;

	Rampa(void);
	

	void setAlturaSueloRampa(int nuevaAltura);

	void dibujar();
	void actualizar(int tiempo);//tiempo = tiempo transcurrido desde ultimo update
	void actualizarFisica(int tiempo); //tiempo = tiempo transcurrido desde ultimo update

	~Rampa(void);
};

#endif

