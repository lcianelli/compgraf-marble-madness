#include "ObjetoEstatico.h"

ObjetoEstatico::ObjetoEstatico(void):ObjetoJuego()
{
	this->altura=1;
	this->alturaSuelo=0;
}

bool ObjetoEstatico::esEstatico() {
	return true;
}

int ObjetoEstatico::getAltura(){
	return this->altura;
}

void ObjetoEstatico::setAltura(int nuevaAltura){
	this->altura= nuevaAltura;
}

int ObjetoEstatico::getAlturaSuelo(){
	return this->alturaSuelo;
}

void ObjetoEstatico::setAlturaSuelo(int nuevaAltura){
	this->alturaSuelo= nuevaAltura;
}

ObjetoEstatico::~ObjetoEstatico(void)
{
}
