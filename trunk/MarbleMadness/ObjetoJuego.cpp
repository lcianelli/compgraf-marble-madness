#include "ObjetoJuego.h"
#include <math.h>

ObjetoJuego::~ObjetoJuego(void)
{
}

void ObjetoJuego::normalizar(float* vector, int largov) {
	float normsqr = 0.f;
	for (int i = 0; i < largov; i++) {
		normsqr += vector[i]*vector[i];
	}
	float norm = sqrt(normsqr);
	for (int i = 0; i < largov; i++) {
		vector[i] = vector[i]/norm;
	}

}

