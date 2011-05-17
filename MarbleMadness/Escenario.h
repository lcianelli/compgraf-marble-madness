#pragma once

#ifndef ESCENARIO_H
#define ESCENARIO_H


#include <list>
#include "ObjetoJuego.h"
#include "ObjetoDinamico.h"
#include "ObjetoEstatico.h"
#include "TipoObjeto.h"


using namespace std;

#define MATRIZ_SUELO_H 10
#define MATRIZ_SUELO_W 10

#define ANCHO_CELDA_GRILLA 1.f

class Escenario
{
private:
	
	list<ObjetoEstatico*> objsEstaticos;
	ObjetoJuego* grilla [MATRIZ_SUELO_W][MATRIZ_SUELO_H];	

public:
	Escenario(void);

	void cargarObjeto(int t, int s, float objH, TipoObjeto tipo);
	void dondeEstoy(float x, float z, int &t, int &s);
	ObjetoJuego* obtenerObjeto(int t, int s);
	void agregarObjeto(ObjetoJuego* obj);


	void dibujar();
	void actualizar(int tiempo);


	~Escenario(void);
};

#endif
