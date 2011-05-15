#include "Nivel.h"

Nivel::Nivel(int num)
{
	this->numero = num;
	this->puntaje = 0;
	this->estado=no_iniciado;
	this->escenario= new Escenario();
	this->personaje=NULL;
	this->inicioNivel=NULL;
	this->finNivel=NULL;

	char* nomArch=new char[12];
	strcpy(nomArch,"nivel");
	char* nuevo=new char[2];
	nuevo=itoa(this->numero,nuevo,10);
	strcat(nomArch,nuevo);
	strcat(nomArch,".xml");
	cargar(nomArch);
}

void Nivel::cargar(char* nomArch)
{

}

Nivel::~Nivel(void)
{
}
