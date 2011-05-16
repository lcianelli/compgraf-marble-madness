#pragma once
#ifndef OBJETO_DINAMICO_H
#define OBJETO_DINAMICO_H

#include "ObjetoJuego.h"
#include "ObjetoEstatico.h"

class ObjetoDinamico :
	public ObjetoJuego
{
protected:
	
	
	
public:	
	ObjetoEstatico* piso;
	bool actualizado;
	bool esEstatico();

	/**
		Retorna el vector unitario de direccion y sentido de la fuerza que aplica este objeto sobre "obj"; el modulo real de la fuerza se retorna en "modulo"
	*/
	virtual float* getFuerzaAplicada(ObjetoJuego* obj, float &modulo) = 0;

	virtual ObjetoEstatico* dondeEstoy() = 0;
	virtual ~ObjetoDinamico(void);
};

#endif
