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

protected:
	Nivel* nivelActual;
	HUD* hud;

	void dibujar();
	void actualizar(int tiempo);
	void procesarEventos();
public:

	inline void setNivel(Nivel* nivel) { this->nivelActual = nivel; }
	inline void setHud(HUD* hud) { this->hud = hud;}
	void inicializar();

	void cambiarNivel();

	PantallaPausa(void);
	~PantallaPausa(void);
};


#endif PANTALLA_PAUSA_H;