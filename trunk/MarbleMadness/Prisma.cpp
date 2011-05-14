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
	return 0;
}
