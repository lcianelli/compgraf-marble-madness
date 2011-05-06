#pragma once
#ifndef MARBLE_JUEGO_H
#define MARBLE_JUEGO_H

#include "EstadoVisual.h"
#include "PantallaNivel.h"
#include <string>
#include <map>
#include <SDL.h>
#include <SDL_opengl.h>


using namespace std;


class Juego
{
private:
	static Juego* instancia;
	int w, h;
	SDL_Surface* pantalla;
	EstadoVisual* estadoActual;
	//map<string, EstadoVisual*> estados;
	Juego(void);
	
	void cargarEstados();
	
public:
	static Juego* inst() {
		if (!instancia) {
			instancia = new Juego();
		}
		return instancia;
	}
	void setEstadoActual(EstadoVisual* estado);
	/*
	incialia la ventana sdl con ancho w y alto h, fullscreen, y habilitada para opengl
	*/
	void inicializar(int w, int h);
	void iniciar();
	~Juego(void);
};

#endif

