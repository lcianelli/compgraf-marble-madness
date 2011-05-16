#include "Prisma.h"


Prisma::Prisma(void)
{
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

void Prisma::interactuar(list<ObjetoJuego*>* interactores) {

}


float* Prisma::getFuerzaAplicada(ObjetoJuego* obj, float &modulo) {
	float* fuerzaAplicada = new float[3];
	float* reaccion = getNormalInteraccion(obj);
	
	
	modulo = obj->modfuerza;
	return fuerza;
}


float* Prisma::getNormalInteraccion(ObjetoJuego* obj) {
	float * normal = new float[3];

	//TODO: almacenar en "normal" los datos de la normal a la cara con la que obj interactua, en la misma direccion desde la que obj "golpea"

	normalizar(normal, 3);
	return normal;	
}

