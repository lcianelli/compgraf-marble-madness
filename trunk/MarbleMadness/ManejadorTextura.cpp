#include "ManejadorTextura.h"


ManejadorTextura* ManejadorTextura::_instancia = 0;


ManejadorTextura::ManejadorTextura() {

}

int ManejadorTextura::cargar(const string &archivoTextura) {
	if (texturas.find(archivoTextura) != texturas.end()) {
		//la textura ya fue cargada
		return texturas.find(archivoTextura)->second;
	}
	int texId;
	texturas[archivoTextura] = (texId = glmLoadTexture(archivoTextura.c_str()));
	return texId;


}

int ManejadorTextura::getId(const string &archivoTextura) {
	if (texturas.find(archivoTextura) != texturas.end()) {
		//la textura ya fue cargada
		return texturas.find(archivoTextura)->second;
	}
	return -1;
}

void ManejadorTextura::limpiar() {
	this->texturas.clear();

}


void ManejadorTextura::borrar() {
	_instancia->limpiar();
	delete _instancia;
	_instancia = 0;
	
}