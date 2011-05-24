#pragma once
#ifndef MANEJADOR_TEXTURA_H
#define MANEJADOR_TEXTURA_H

#include <map>
#include <string>
#include "glm.h"


using namespace std;

class ManejadorTextura {
protected:
	map<string, int> texturas;
	static ManejadorTextura* _instancia;
	
	ManejadorTextura();

public:
	static ManejadorTextura* inst() {
		if (_instancia == NULL) {
			_instancia = new ManejadorTextura();
		}
		return _instancia;
	}
	int cargar(const string &archivoTextura);
	int getId(const string &archivoTextura);
	void limpiar();
	static void borrar();
};


#endif MANEJADOR_TEXTURA_H;

