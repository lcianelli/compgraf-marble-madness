#include "Personaje.h"

Personaje::Personaje(void): Bola()
{
	this->centro = new float[3];
	this->rotacion = new float[3];

	this->piso = NULL;
	this->velocidad = new float[3];

	for (int i = 0; i < 3; i++) {
		centro[i] = rotacion[i]  = velocidad[i] = 0.f;
	}

	float cantSalto = 0.1;
	float salto = 0.0;
	float AnguloGiroAnteriorEjeY = 0.0;;
	Matriz matrizTransformacion = Matriz();
}

Personaje::~Personaje(void)
{
}



