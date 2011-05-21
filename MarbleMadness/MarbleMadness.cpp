// MarbleMadness.cpp : Defines the entry point for the console application.
//


#include "Juego.h"


int main(int argc, char* argv[])
{
	Juego::inst()->inicializar(600,480);

		printf("Estoy iniciando\n");


	Juego::inst()->iniciar();


	return 0;
}

