#include "Rayo.h"
#include <math.h>
#include "Mathex.h"

Rayo::Rayo(const Vector &punto1, const Vector &punto2) : _P(punto1) {
	_V = (punto2.esUnitario() ? punto2 : Vector::unitario(punto2-punto1));
}

bool Rayo::puntosAdyacentes(const Rayo &rayo, Vector &punto1, Vector &punto2) const {
	if (esValido() && rayo.esValido()) {
		float temp = Vector::escalar(_V, rayo._V);
		float temp2 = 1.0 - sqr(temp);
		Vector tv;
		//Checkeamos rayos paralelos
		if (fabs(temp2) < EPSILON) {
			float mu = Vector::escalar(_V, _P-rayo._P)/temp;
			punto1 = _P;
			Vector::suma(rayo._P, Vector::multiplicar(rayo._V, mu, tv), punto2);
		}else { //no son paralelos
			float a = Vector::escalar(_V, Vector::resta(rayo._P, _P, tv));
			float b = Vector::escalar(rayo._V, Vector::resta(_P, rayo._P, tv));
			float mu = (b + temp*a) / temp2;
			float lambda = (a + temp*b) / temp2;
			Vector::suma(_P, Vector::multiplicar(_V, lambda, tv), punto1);
			Vector::suma(rayo._P, Vector::multiplicar(rayo._V, mu, tv), punto2);
		}
		return true;
	}
	return false;
}

//distancia entre dos rayos
float Rayo::dist(const Rayo &rayo) const {
	Vector punto1, punto2;
	if (puntosAdyacentes(rayo, punto1, punto2)) {
		return punto1.dist(punto2);
	} 
	return 0.f;

}

//distancia entre un rayo y un punto
float Rayo::dist(const Vector &punto) const {
	if (esValido() && punto.esValido()) {
		Vector tv, punto2;
		float lambda = Vector::escalar(_V, punto - _P);
		Vector::suma(_P, Vector::multiplicar(_V, lambda, tv), punto2);
		return punto.dist(punto2);

	}
	return 0.f;
}


