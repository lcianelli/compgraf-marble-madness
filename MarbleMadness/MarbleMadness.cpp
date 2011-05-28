// MarbleMadness.cpp : Defines the entry point for the console application.
//


#include "Juego.h"


int main(int argc, char* argv[])
{
	Juego::inst()->inicializar(800,600);

		printf("Estoy iniciando\n");


	Juego::inst()->iniciar();


	return 0;
}

