#pragma once
#ifndef OBJETO_DINAMICO_H
#define OBJETO_DINAMICO_H

#include "ObjetoJuego.h"
#include "ObjetoEstatico.h"

#include "Matriz.h"


class ObjetoDinamico :
	public ObjetoJuego
{
protected:
	float* velocidad;
	float* posicion; // posicion respecto a sus coordenadas locales

	float* escalado;

	float salto;
	bool colisione;
	ObjetoEstatico* piso;

	float cantSalto;
//	float salto;
	float AnguloGiroAnteriorEjeY;

	Matriz matrizTransformacion;

public:	

	//** Funciones para el manejo de la matriz de transformacion **//
	Matriz getMatriz();
	void multMatriz(Matriz matriz);

	//TODO: ver si se usa
	bool getColisione();
	void setColisione(bool colisiono);

	float* getescalado();
	void setescalado(float* scale);

	bool actualizado;
	bool esEstatico();

	float* getPosicion();
	void setPosicion(float* pos);

	float* getVelocidad();
	void setVelocidad(float* vel);

	float getSalto();
	void setSalto(float sal);

	float getCantSalto();
	void setCantSalto(float cantSal);

	float getAnguloGiroAnteriorEjeY();

	ObjetoEstatico* getPiso();
	void setPiso(ObjetoEstatico* obj);

	//** Funciones para simular el movimiento correcto de la bola sobre el escenario **//
	void subeRampa(float anguloGiroZ, float* ptoSubidaCaida);
	void CambioDireccion(float* ptoCambioDiraccion, float anguloGiroY);
	void Saltar();
	void Colision(float anguloRotarNormalZ, float anguloRotarNormalY, float* ptoPlano);

	virtual void setRotacion(float ax, float ay, float az)  = 0;

	virtual void dibujar()=0;

	virtual ObjetoEstatico* dondeEstoy() = 0;

	virtual ~ObjetoDinamico(void);
};

#endif
