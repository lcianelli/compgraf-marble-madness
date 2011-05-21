#include "ObjetoJuego.h"
#include <math.h>

ObjetoJuego::ObjetoJuego(void)
{
	this->direccion= new float[3];
	this->velocidad=new float[3];
	this->modVelocidad=0.0;//modVelocidad == |velocidad|
	this->fuerza=new float[3];
	this->modfuerza=0.0;// modfuerza == |fuerza|
	this->ambiente=0;
	this->masa=0.0;
	this->absorcionEnergia=0.0;
	this->ambiente = new Ambiente();
}

ObjetoJuego::~ObjetoJuego(void)
{
}

void ObjetoJuego::normalizar(float* vector, int largov) {
	
	float norm = modulo(vector, largov);
	if (norm != 0) {

		for (int i = 0; i < largov; i++) {
			vector[i] = vector[i]/norm;
		}
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

