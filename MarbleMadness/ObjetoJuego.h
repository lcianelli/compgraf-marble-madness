#pragma once
#ifndef MARBLE_OBJETO_JUEGO
#define MARBLE_OBJETO_JUEGO

#include <list>
#include "Ambiente.h"

using namespace std;

class ObjetoJuego
{
protected: 
	bool estatico;//marca si el objeto es estatico o no, es decir, si al hacerle update tenemos que cambiar su 
	//posicion de acuerdo a su velocidad o no, as� como si tenemos que tener en cuenta su aceleraci�n para el update fisico
	
	/*
		Dada la lista de objetos con las que en un momento dado interactuamos, esto recalcula los par�metros de velocidad y aceleraci�n seg�n 
		la forma de interacci�n con cada objeto
	*/
	virtual void interactuar(list<ObjetoJuego*> interactores) = 0;
	/**
		Retorna el vector unitario de direccion y sentido de la fuerza que aplica este objeto sobre "obj"; el modulo real de la fuerza se retorna en "modulo"
	*/
	virtual float* getFuerzaAplicada(ObjetoJuego* obj, float &modulo) = 0;
public:
	float* direccion;
	float* velocidad;
	float modVelocidad;//modVelocidad == |velocidad|
	float* fuerza;
	float modfuerza;// modfuerza == |fuerza|
	Ambiente* ambiente;
	float* masa;
	/*Normaliza el vector vector de largo largov*/
	void normalizar(float* vector, int largov);
	virtual void dibujar() = 0;
	virtual void actualizar(int tiempo) = 0;//tiempo = tiempo transcurrido desde ultimo update
	virtual void actualizarFisica(int tiempo) = 0; //tiempo = tiempo transcurrido desde ultimo update
	

	virtual ~ObjetoJuego(void);
};


#endif
