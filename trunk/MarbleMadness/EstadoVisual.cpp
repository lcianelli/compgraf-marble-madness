#include "EstadoVisual.h"

EstadoVisual::~EstadoVisual(void)
{
	this->loop = false;	
}

void EstadoVisual::correr() {
	while (loop) {
		procesarEventos();
		dibujar();
		actualizar();
	}
}

void EstadoVisual::detener() {
	this->loop = false;
}
