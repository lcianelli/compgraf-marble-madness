#include "Configuracion.h"

Configuracion* Configuracion::instancia = 0;

Configuracion::Configuracion(void)
{
}


Configuracion::~Configuracion(void)
{
}

void Configuracion::setWireframe(bool w)  {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); esto es para mostrar todo como wireframe
}
