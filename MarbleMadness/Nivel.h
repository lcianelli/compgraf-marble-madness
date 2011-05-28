#pragma once

#ifndef NIVEL_H
#define NIVEL_H

#include "Escenario.h"
#include "FinEscenario.h"
#include "InicioEscenario.h"
#include "Personaje.h"
#include "Configuracion.h"

class Bola;
class Personaje;

class Nivel
{
private:
	enum estadoJuego {ganado,jugando,perdido,no_iniciado};
	enum estadoJuego estado;
	int numero;
	int puntaje;
	list<ObjetoDinamico*> objsDinamicos;
	
	Escenario* escenario;
	int dimensionEscenario;
	ObjetoDinamico* personaje;
	InicioEscenario* inicioNivel;
	FinEscenario* finNivel;

	GLMmodel* entorno;

	bool fin();
public:
	Nivel(int num);
	void cargar(char* archivoNivel);
	void crearObjetoDinamico(float x, float y, float z, TipoObjeto tipo);
	void agregarObjetoDinamico(ObjetoJuego* obj);
	void dibujarObjDinamicos();
	void actualizarObjDinamicos(int tiempo);
	void actualizarFisica(int tiempo);
	void iniciar();
	void pausar();
	void terminar();
	void dibujar();
	void actualizar(int tiempo);

	void teclaPresionada(SDL_keysym* keysym);
	void teclaLiberada(SDL_keysym* keysym);
	
	void dondeEstoy(float x, float z, int &t, int &s);
	ObjetoJuego* obtenerObjeto(int t, int s);

	~Nivel(void);
};

#endif NIVEL_H;

