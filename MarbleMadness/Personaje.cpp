#include "Personaje.h"

Personaje::Personaje(void) : Bola()
{
	this->r = 0.5f;
	this->masa = 0.2f;
	
}

Personaje::~Personaje(void)
{
}

void Personaje::moverArriba() {
	
	detenerAbajo();
	this->acelerar = !(this->modVelocidad >= BOLA_VEL_MAX);
	this->fuerza[2] = -1.f;
	normalizar(this->fuerza, 3);
}

void Personaje::moverAbajo() {
	detenerArriba();
	this->acelerar = !(this->modVelocidad >= BOLA_VEL_MAX);
	this->fuerza[2] = 1.f;
	normalizar(this->fuerza, 3);
}

void Personaje::moverDerecha() {
	detenerIquierda();
	this->acelerar = !(this->modVelocidad >= BOLA_VEL_MAX);
	this->fuerza[0] = 1.f;
	normalizar(this->fuerza, 3);
}

void Personaje::moverIquierda() {
	detenerDerecha();
	this->acelerar = !(this->modVelocidad >= BOLA_VEL_MAX);
	this->fuerza[0] = -1.f;
	normalizar(this->fuerza, 3);
}

void Personaje::detenerArriba() {
	this->acelerar = false;
	this->fuerza[2] = 0.f;
	normalizar(this->fuerza, 3);
}

void Personaje::detenerAbajo() {
	this->acelerar = false;
	this->fuerza[2] = 0.f;
	normalizar(this->fuerza, 3);
}

void Personaje::detenerDerecha() {
	this->acelerar = false;
	this->fuerza[0] = 0.f;
	normalizar(this->fuerza, 3);
	
}

void Personaje::detenerIquierda() {
	this->acelerar = false;
	this->fuerza[0] = 0.f;
	normalizar(this->fuerza, 3);
}


