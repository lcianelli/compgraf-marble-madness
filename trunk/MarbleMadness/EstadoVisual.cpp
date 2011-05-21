#include "EstadoVisual.h"

#include <SDL.h>
#include <SDL_opengl.h>


EstadoVisual::~EstadoVisual(void)
{
	this->loop = false;

}

void EstadoVisual::correr() {
	glTranslatef(0.f,0.f, -10.f);
	while (loop) {
			//printf("voy a procesar eventos\n");
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
