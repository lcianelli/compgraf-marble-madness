#include "Juego.h"


int main(int argc, char* argv[])
{
	Juego::inst()->inicializar(1280,800);
	Juego::inst()->iniciar();


	return 0;
}

