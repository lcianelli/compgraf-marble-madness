#pragma once
#ifndef PANTALLA_OPCIONES_H
#define PANTALLA_OPCIONES_H

#include "EstadoVisual.h"
#include "Juego.h"
#include "Vector.h"
#include "BotonGUI.h"
#include "CheckboxGUI.h"
#include "MenuGUI.h"
#include "Nivel.h"
#include "HUD.h"
#include "ManejadorTextura.h" 
#include "SlidebarGUI.h"

using namespace mmgui;

class PantallaOpciones : public EstadoVisual
{
private:
	BotonGUI* aceptarBtn;
	CheckboxGUI *wireframe, *interpolado, *texturas;
	CheckboxGUI* dirluz[4];
	SlidebarGUI *velBar, *rBar, *gBar, *bBar;
	MenuGUI* menuOpciones;
	bool mouseDown;
	SDL_Surface* s;
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
	PantallaOpciones(void);
	~PantallaOpciones(void);
};

#endif PANTALLA_OPCIONES_H;

