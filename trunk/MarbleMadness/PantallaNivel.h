#pragma once
#ifndef PANTALLA_NIVEL_H
#define PANTALLA_NIVEL_H

#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GL.h>
#include <gl\GLU.h>

#include <iostream>

#include "Juego.h"
#include "EstadoVisual.h"
#include "Nivel.h"


class PantallaNivel : public EstadoVisual
{
protected:
	Nivel* nivelActual;
	int idNivel;
	void dibujar();
	void actualizar();
	void procesarEventos();
	void handleKeyDown(SDL_keysym* keysym);
	void handleKeyUp(SDL_keysym* keysym);
	//no se si esto va aca
	void cambiarNivel();
public:
	void inicializar();
	PantallaNivel();
	~PantallaNivel(void);
	
};

#endif
