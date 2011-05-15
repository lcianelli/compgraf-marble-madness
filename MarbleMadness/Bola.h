#pragma once
#ifndef MARBLE_BOLA_H
#define MARBLE_BOLA_H

#include "ObjetoDinamico.h"
#include "ObjetoJuego.h"

class ObjetoJuego;
class ObjetoDinamico;

class Bola : public ObjetoDinamico
{
protected:
	void interactuar(list<ObjetoJuego*> interactores);
	/**
		Retorna el vector unitario de direccion y sentido de la fuerza que aplica este objeto sobre "obj"; el modulo real de la fuerza se retorna en "modulo"
	*/
	float* getFuerzaAplicada(ObjetoJuego* obj, float &modulo);

	float* getNormalInteraccion(ObjetoJuego* obj);
public:
	float r;
	float* centro;
	void dibujar();
	void actualizar(int tiempo);//tiempo = tiempo transcurrido desde ultimo update
	void actualizarFisica(int tiempo); //tiempo = tiempo transcurrido desde ultimo update

	ObjetoEstatico* dondeEstoy();
	Bola(void);
	~Bola(void);
};

#endif

