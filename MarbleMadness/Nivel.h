#pragma once
#ifndef NIVEL_H
#define NIVEL_H


#include "Escenario.h";
#include "FinEscenario.h";
#include "InicioEscenario.h";
#include "Personaje.h"

class Nivel
{
private:
	enum estadoJuego {ganaste,perdiste,jugando,no_iniciado};
	enum estadoJuego estado;
	int numero;
	int puntaje;		
	
	Escenario* escenario;
	Personaje* personaje;
	InicioEscenario* inicioNivel;
	FinEscenario* finNivel;

	bool fin();
public:
	Nivel(int num);
	void cargar(char* archivoNivel);
	void iniciar();
	void pausar();
	void terminar();
	void dibujar();

	~Nivel(void);
};

#endif

