#include "Ambiente.h"
float* Ambiente::gravedad = new float[3];
float Ambiente::modFuerzaExterna = 1.f;
bool Ambiente::aplicarG = false;

void Ambiente::init() {
	gravedad[0] = 0.f;
	gravedad[1] = 0.f;//-0.000098f;
	gravedad[2] = 0.f;
}

void Ambiente::aplicarGravedad(bool aplicar) {
	gravedad[1] = (aplicarG = aplicar) ? -0.000098f : 0.f;
}

Ambiente::Ambiente(void)
{
	

}


Ambiente::~Ambiente(void)
{
}
