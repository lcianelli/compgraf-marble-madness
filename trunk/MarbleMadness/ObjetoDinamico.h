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
	
	
public:	
	bool actualizado;
	bool esEstatico();

	virtual ObjetoEstatico* dondeEstoy() = 0;
	virtual ~ObjetoDinamico(void);
};

#endif
