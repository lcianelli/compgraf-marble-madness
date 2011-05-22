#pragma once

#include <SDL.h>
#include <SDL_opengl.h>
#include "FreeType.h"

using namespace freetype;

class HUD
{
private:
	int puntaje;
	int tiempo;
	int nivel;
	int tiempoInicial;

	//fuentes
	font_data fuenteHudMain;

public:
	//tiempoTotal se expresa en milisegundos. 
	//nivel y puntaje inicial no deberian ser negativos.
	HUD(int puntajeInicial, int tiempoTotal, int nivel);
	
	inline void cambiarNivel(int id) { this->nivel = id;}
	inline void setTiempo(int tiempoTotal) { this->tiempoInicial = this->tiempo = tiempoTotal; }
	inline void setPuntaje(int puntajeInicial) {this->puntaje = puntajeInicial;}

	//hace que el hud actualize sus propiedades respecto del tiempo transcurrido desde la ultima actualizacion "tiempoTranscurrido"
	void actualizar(int tiempoTranscurrido);

	void dibujarHud();

	inline bool finTiempo() {return tiempo == 0;}
	~HUD(void);

};

