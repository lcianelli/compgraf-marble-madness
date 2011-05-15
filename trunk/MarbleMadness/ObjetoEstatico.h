#pragma once
#ifndef OBJETO_ESTATICO_H
#define OBJETO_ESTATICO_H

#include "ObjetoJuego.h"

class ObjetoEstatico :
	public ObjetoJuego
{
public:
	bool esEstatico();
	virtual ~ObjetoEstatico(void);
};

#endif 
