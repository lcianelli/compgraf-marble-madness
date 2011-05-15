#include "Escenario.h"

Escenario::Escenario(void)
{
	for (int i = 0; i < MATRIZ_SUELO_W; i++) {
		for (int j = 0; j < MATRIZ_SUELO_H; j++) {
			this->grilla[i][j] = NULL;
		}
	}
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

Escenario::~Escenario(void)
{

	
}
