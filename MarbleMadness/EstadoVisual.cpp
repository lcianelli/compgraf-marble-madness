#include "EstadoVisual.h"

EstadoVisual::~EstadoVisual(void)
{
	this->loop = false;	
}

void EstadoVisual::correr() {
	while (loop) {
		this->ticksIni = SDL_GetTicks();
		procesarEventos();
		actualizar(this->ticksIni-this->ticksFin);
		dibujar();
		this->ticksFin = this->ticksIni;
	}
}

void EstadoVisual::detener() {
	this->loop = false;
}
