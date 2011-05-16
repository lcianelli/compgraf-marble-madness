#include "Escenario.h"

Escenario::Escenario(void)
{
	for (int i = 0; i < MATRIZ_SUELO_W; i++) {
		for (int j = 0; j < MATRIZ_SUELO_H; j++) {
			this->grilla[i][j] = NULL;
		}
	}
	Ambiente::init();
}


void Escenario::actualizarFisica(int tiempo) {
	list<ObjetoDinamico*>::iterator it;
	for (it = objsDinamicos.begin(); it != objsDinamicos.end(); it++) {
		(*it)->actualizado = false;
	}
	for (it = objsDinamicos.begin(); it != objsDinamicos.end(); it++) {
		if (!(*it)->actualizado) {
			(*it)->actualizarFisica(tiempo);
		}
	}

}

void Escenario::dondeEstoy(float x, float z, int &t, int &s){
	t=x/ANCHO_CELDA_GRILLA;
	s=z/ANCHO_CELDA_GRILLA;
}

ObjetoJuego* Escenario::obtenerObjeto(int t, int s){
	return this->grilla[t][s];
}

void Escenario::agregarObjeto(ObjetoJuego* obj) {
	if (obj->esEstatico())  {
		this->objsEstaticos.push_back(dynamic_cast<ObjetoEstatico*>(obj));
	} else {
		this->objsDinamicos.push_back(dynamic_cast<ObjetoDinamico*>(obj));
	}
}


Escenario::~Escenario(void)
{

	
}

void Escenario::dibujar() {
	//TODO: dibujar cosas del escenario, en caso de que las tenga, luces, decorados, etc.

	//Dibujo cada objeto que forma parte de la escena
	list<ObjetoDinamico*>::iterator itDin;
	for (itDin = this->objsDinamicos.begin(); itDin != this->objsDinamicos.end(); itDin++) {
		(*itDin)->dibujar();
	}

	list<ObjetoEstatico*>::iterator itEst;
	for (itEst = this->objsEstaticos.begin(); itEst != this->objsEstaticos.end(); itEst++) {
		(*itEst)->dibujar();
	}
}

void Escenario::actualizar(int tiempo) {
	//TODO: actualizar cosas del escenario, en caso de que las tenga, luces, decorados, etc.

	//Actualizo cada objeto que forma parte de la escena
	list<ObjetoDinamico*>::iterator itDin;
	for (itDin = this->objsDinamicos.begin(); itDin != this->objsDinamicos.end(); itDin++) {
		(*itDin)->actualizar(tiempo);
	}

	list<ObjetoEstatico*>::iterator itEst;
	for (itEst = this->objsEstaticos.begin(); itEst != this->objsEstaticos.end(); itEst++) {
		(*itEst)->actualizar(tiempo);
	}
	

}

