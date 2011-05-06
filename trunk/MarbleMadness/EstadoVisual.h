#pragma once
#ifndef ESTADO_VISUAL_H
#define ESTADO_VISUAL_H


class EstadoVisual {
public:
	 
	static const int FPS_30 = 30;
	static const int FPS_60 = 60;

protected:
	int refreshFreq;
	bool loop;
	virtual void dibujar() = 0;
	virtual void actualizar() = 0;
	virtual void procesarEventos() = 0;
	
	
public:
	virtual void inicializar() = 0;
	void correr();
	void detener();
	virtual ~EstadoVisual(void);
};

#endif
