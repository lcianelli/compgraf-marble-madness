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

Escenario::~Escenario(void)
{

	
}
