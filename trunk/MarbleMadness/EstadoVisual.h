#pragma once
#ifndef ESTADO_VISUAL_H
#define ESTADO_VISUAL_H

#include <SDL.h>

class EstadoVisual {
public:
	 
	static const int FPS_30 = 30;
	static const int FPS_60 = 60;

protected:
	Uint32 ticksIni, ticksFin;
	int refreshFreq;
	bool loop;
	bool pausa;
	virtual void dibujar() = 0;
	virtual void actualizar(int tiempo) = 0;
	virtual void procesarEventos() = 0;
	
	
public:
	virtual void inicializar() = 0;
	virtual void cambiarNivel() = 0;
	void correr();
	void detener();
	virtual ~EstadoVisual(void);
};

#endif ESTADO_VISUAL_H;
