#include "Plano.h"

int Plano::probarInterseccion(const Rayo &r, float &lambda, Vector &pNormal) {
	float prodEscalar = r.V().escalar(this->normal);
	float l2;
	//determinamos si el rayo es paralelo al plano
	if (prodEscalar < CERO && prodEscalar> -CERO) {
		return 0;//el rayo es paralelo
	}
	l2 = (this->normal.escalar(this->posicion-r.P()))/prodEscalar;
	lambda = l2;
	//el rayo y el plano se intersectan, devolvemos la normal a este plano en pnormal, y la distancia en lambda
	pNormal = this->normal; 
	if (l2 < -CERO) { //la interseccion se da por la parte trasera del plano
		return -1;
	}
	//interseccion correcta
	return 1;
}

int Plano::probarInterseccion(const Vector &posicion, const Vector& direccion, float &lambda, Vector &pNormal) {
	Rayo r(posicion, direccion);
	return probarInterseccion(r, lambda, pNormal);
}

Plano::~Plano(void)
{
}
