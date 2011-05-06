#pragma once
#ifndef MARBLE_JUEGO_H
#define MARBLE_JUEGO_H

#include "EstadoVisual.h"
#include <string>
#include <map>

using namespace std;

class Juego
{
private:

	EstadoVisual* estadoActual;
	map<string, EstadoVisual*> estados;
	void cargarEstados();

public:
	Juego(void);
	~Juego(void);
	void setEstadoActual(EstadoVisual* estado);
	void inicializar();
	void iniciar();
};

#endif

