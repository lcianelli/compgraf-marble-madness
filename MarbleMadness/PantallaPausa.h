#pragma once
#ifndef PANTALLA_PAUSA_H
#define PANTALLA_PAUSA_H

#include "Juego.h"
#include "EstadoVisual.h"
#include "Nivel.h"
#include "HUD.h"
#include "BotonGUI.h"
#include "MenuGUI.h"
#include "ManejadorTextura.h"

using namespace mmgui;

class PantallaPausa :
	public EstadoVisual
{
private:
	bool mouseDown;
	SDL_Surface* s;
	BotonGUI* resumeBtn;
	BotonGUI* opcionesBtn;
	BotonGUI* salirBtn;
	BotonGUI* reiniciarBtn;
	MenuGUI* menuPausa;
protected:
	Nivel* nivelActual;
	HUD* hud;

	void dibujar();
	void actualizar(int tiempo);
	void procesarEventos();
	void handleKeyDown(SDL_keysym* keysym);
	void handleMouseDown(const SDL_MouseButtonEvent &ev);
	void handleMouseMoved(const SDL_MouseMotionEvent &ev);
	void handleMouseUp(const SDL_MouseButtonEvent &ev);
public:

	inline void setNivel(Nivel* nivel) { this->nivelActual = nivel; }
	inline void setHud(HUD* hud) { this->hud = hud;}
	void inicializar();

	void cambiarNivel();
	void resumir();
	PantallaPausa(void);
	~PantallaPausa(void);

	

};


#endif PANTALLA_PAUSA_H;