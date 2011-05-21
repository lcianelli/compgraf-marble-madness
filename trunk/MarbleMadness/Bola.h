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
#include "Nivel.h"



#define BOLA_VEL_MAX 1.f

class Bola : public ObjetoDinamico
{
protected:
	bool acelerar;
	float modAceleracion;

	void interactuar(list<ObjetoJuego*>* interactores);
	/**
		Retorna el vector unitario de direccion y sentido de la fuerza que aplica este objeto sobre "obj"; el modulo real de la fuerza se retorna en "modulo"
	*/
	float* getFuerzaAplicada(ObjetoJuego* obj, float &modulo);

	float* getNormalInteraccion(ObjetoJuego* obj);

	//actualiza parámetros de velocidad y posicion segun el tiempo transcurrido y las caracteristicas del movimiento (acerleracion, velocidad y posiciones previas)
	virtual void actualizarMovimiento(int tiempo);

	//Devuelve el objeto más cercano con el que la bola va a interactuar. 
	//Retorna nulo si no sale del lugar actual en la grilla ni se choca con ningun movil	
	virtual ObjetoJuego* calcularProximaInteraccion(const Rayo &rMovimiento, float &distanciaChoque, Vector &normalChoque, Vector &puntoChoque);


	//Calcula las fuerzas resultantes del choque de la bola con el objeto objChoque, en el punto puntoChoque, dado el vector normal a la superficie de objChoque
	//puede que alguno de los parametros no sea necesario.. veremos.
	virtual void procesarInteraccion(ObjetoJuego* objChoque, float tiempoTranscurrido, float distanciaChoque, Vector &normalChoque, Vector& puntoChoque);

public:

	Nivel* nivel;
	float r;
	float* centro;
	float* rotacion;


	void dibujar();
	void actualizar(int tiempo);//tiempo = tiempo transcurrido desde ultimo update

	//NO SE USA MAS
	void actualizarFisica(int tiempo); //tiempo = tiempo transcurrido desde ultimo update

	
	void setCentro(float cx, float cy, float cz);
	void setRotacion(float ax, float ay, float az);
	ObjetoEstatico* dondeEstoy();
	void setPiso(ObjetoEstatico* obj);
	Bola(void);
	~Bola(void);
};

#endif

