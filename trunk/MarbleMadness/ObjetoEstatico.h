#pragma once
#ifndef OBJETO_ESTATICO_H
#define OBJETO_ESTATICO_H

#include "ObjetoJuego.h"

#include "glm.h"


class ObjetoEstatico :
	public ObjetoJuego
{
private:
	int altura;
	int alturaSuelo;
public:
	ObjetoEstatico(void);
	bool esEstatico();
	int getAltura();
	void setAltura(int nuevaAltura);
	int getAlturaSuelo();
	void setAlturaSuelo(int nuevaAltura);
	virtual ~ObjetoEstatico(void);
};

#endif 
