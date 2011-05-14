#include "ObjetoJuego.h"
#include <math.h>

ObjetoJuego::~ObjetoJuego(void)
{
}

void ObjetoJuego::normalizar(float* vector, int largov) {
	
	float norm = modulo(vector, largov);
	for (int i = 0; i < largov; i++) {
		vector[i] = vector[i]/norm;
	}

}

float ObjetoJuego::modulo(float* vector, int largov) {
	float normsqr = 0.f;
	for (int i = 0; i < largov; i++) {
		normsqr += vector[i]*vector[i];
	}
	float norm = sqrt(normsqr);
	return norm;

}

