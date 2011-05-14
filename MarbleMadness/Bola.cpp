#include "Bola.h"


Bola::Bola(void)
{
}


Bola::~Bola(void)
{
}

void Bola::dibujar() {
}

void Bola::actualizar(int tiempo) {

}

void Bola::actualizarFisica(int tiempo) {
}

void Bola::interactuar(list<ObjetoJuego*> interactores) {
	float* fuerza = new float[3];
	list<ObjetoJuego*>::iterator it;
	for (it = interactores.begin(); it != interactores.end(); it++) {

	}

	delete[] fuerza;
}

float* Bola::getFuerzaAplicada(ObjetoJuego* obj, float &modulo) {

}

