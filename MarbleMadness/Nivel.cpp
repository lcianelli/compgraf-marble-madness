#include "Nivel.h"

Nivel::Nivel(int num){

	this->numero = num;
	this->puntaje = 0;
	this->escenario=new Escenario();
	this->personaje=NULL;
	this->inicioNivel=NULL;
	this->finNivel=NULL;
	this->estado=no_iniciado;
}

void Nivel::iniciar(){

}

Nivel::~Nivel(void)
{
}
