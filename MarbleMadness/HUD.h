#pragma once

#include <SDL.h>
#include <SDL_opengl.h>

class HUD
{
public:
	HUD(void);
	void actualizarPuntaje();
	void actualizarTiempo();
	void cambiarNivel(int id);
	void dibujarHud();
	~HUD(void);
private:
	int puntaje;
	int tiempo;
	int nivel;
};

