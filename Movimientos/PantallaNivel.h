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

class PantallaNivel : public EstadoVisual
{
protected:
	void dibujar();
	void actualizar(int tiempo);
	void procesarEventos();
	void handleKeyDown(SDL_keysym* keysym);
	void handleKeyUp(SDL_keysym* keysym);	
public:
	void inicializar();
	void cambiarNivel();
	PantallaNivel();
	~PantallaNivel(void);
	
};

#endif
