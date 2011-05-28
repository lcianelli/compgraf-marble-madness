#pragma once

#ifndef ESCENARIO_H
#define ESCENARIO_H


#include <list>
#include "ObjetoJuego.h"
#include "ObjetoDinamico.h"
#include "ObjetoEstatico.h"
#include "TipoObjeto.h"


using namespace std;

#define MATRIZ_DIMENSION 5

#define ANCHO_CELDA_GRILLA 10.f

class Escenario
{
private:
	
	list<ObjetoEstatico*> objsEstaticos;
	ObjetoEstatico* grilla [MATRIZ_DIMENSION][MATRIZ_DIMENSION];	

public:
	Escenario(void);

	void cargarObjeto(int t, int s, float objH, TipoObjeto tipo, int objH2, int rot);
	void dondeEstoy(float x, float z, int &t, int &s);
	ObjetoJuego* obtenerObjeto(int t, int s);
	void agregarObjeto(ObjetoJuego* obj);
	void dibujar();
	~Escenario(void);
};

#endif

