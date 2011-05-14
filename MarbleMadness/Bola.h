#pragma once
#ifndef MARBLE_BOLA_H
#define MARBLE_BOLA_H

#include "ObjetoJuego.h"



class Bola : public ObjetoJuego
{
protected:
	void interactuar(list<ObjetoJuego*> interactores);
	/**
		Retorna el vector unitario de direccion y sentido de la fuerza que aplica este objeto sobre "obj"; el modulo real de la fuerza se retorna en "modulo"
	*/
	float* getFuerzaAplicada(ObjetoJuego* obj, float &modulo);
public:
	float r;
	float* centro;
	void dibujar();
	void actualizar(int tiempo);//tiempo = tiempo transcurrido desde ultimo update
	void actualizarFisica(int tiempo); //tiempo = tiempo transcurrido desde ultimo update
	Bola(void);
	~Bola(void);
};

#endif

