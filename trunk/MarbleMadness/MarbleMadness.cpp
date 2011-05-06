// MarbleMadness.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Juego.h"


int _tmain(int argc, _TCHAR* argv[])
{
	Juego::inst()->inicializar(1280,800);
	Juego::inst()->iniciar();


	return 0;
}

