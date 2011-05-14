#pragma once
#ifndef OBJETO_DINAMICO_H
#define OBJETO_DINAMICO_H

#include "ObjetoJuego.h"
#include "ObjetoEstatico.h"

class ObjetoDinamico :
	public ObjetoJuego
{
protected:
	ObjetoEstatico* piso;
	/*
		Dada la lista de objetos con las que en un momento dado interactuamos, esto recalcula los parámetros de velocidad y aceleración según 
		la forma de interacción con cada objeto
	*/
	virtual void interactuar(list<ObjetoJuego*> interactores) = 0;
	/**
		Retorna el vector unitario de direccion y sentido de la fuerza que aplica este objeto sobre "obj"; el modulo real de la fuerza se retorna en "modulo"
	*/
	virtual float* getFuerzaAplicada(ObjetoJuego* obj, float &modulo) = 0;

	/**
		Retorna un vector unitario que representa la normal del objeto actual respecto de obj (es decir, la normal a la cara con la que obj "interactua"
	*/
	virtual float* getNormalInteraccion(ObjetoJuego* obj) = 0;
public:	
	virtual ~ObjetoDinamico(void);
};

#endif
