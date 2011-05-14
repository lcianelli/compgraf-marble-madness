#include "Prisma.h"


Prisma::Prisma(void)
{
	this->estatico = true;
}


Prisma::~Prisma(void)
{
}

void Prisma::dibujar() {

}

void Prisma::actualizar(int tiempo) {

}

void Prisma::actualizarFisica(int tiempo) {
	//nada...
}

void Prisma::interactuar(list<ObjetoJuego*> interactores) {

}


float* Prisma::getFuerzaAplicada(ObjetoJuego* obj, float &modulo) {
	float* fuerzaAplicada = new float[3];
	fuerzaAplicada[0] = -1.f*obj->fuerza[0];
	fuerzaAplicada[1] = -1.f*obj->fuerza[1];
	fuerzaAplicada[2] = -1.f*obj->fuerza[2];
	modulo = obj->modfuerza;
	return fuerza;
}
