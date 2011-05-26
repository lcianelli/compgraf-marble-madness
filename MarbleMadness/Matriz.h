#pragma once
#ifndef MATRIZ_H
#define MATRIZ_H

#include "Mathex.h"

class Vector;

class Matriz
{
private:
	float _Mx[4][4];

public:
	Matriz();
	
	//1 es segun el eje x, 2 segun el eje y y 3 segun el eje z
	Matriz(float phi, int xyz);
	Matriz(float mx00, float mx01, float mx02, float mx03, 
				float mx10, float mx11, float mx12, float mx13, 
					float mx20, float mx21, float mx22, float mx23,
						float mx30, float mx31, float mx32, float mx33);


	//Retorna la matriz de traslacion
	Matriz(float* trasl);

	//Genera la matriz de reflexion respecto al plano indicado. si plano==1 XY, plano==2 XZ plano==3 YZ
	Matriz(int plano);

	//Retorna la matriz en forma de vector, por columnas.
	float* getMatrizVector();

	//float operator()(int row, int col) const { return _Mx[row][col];}
	//float &operator()(int row, int col) {return _Mx[row][col];}

	//métodos aritméticos optimizados

	static Matriz &suma(const Matriz &m1, const Matriz &m2, Matriz &res);
	static Matriz &resta(const Matriz &m1, const Matriz &m2, Matriz &res);

	Matriz multiplicar(Matriz m2);
	Matriz multiplicar(float escala);

	//Multiplica la matriz por el vector v. Asume la 4ta componente del vector=1. Retorna un vector de 4 elementos
	float* multiplicar(Vector v);


	//aritmética de matrices

	Matriz &operator+=(const Matriz &m) { return suma(*this, m, *this);}
	Matriz &operator-=(const Matriz &m) { return resta(*this, m, *this);}

	Matriz &operator+(const Matriz &m) const { Matriz tm; return suma(*this, m, tm);}
	Matriz &operator-(const Matriz &m) const { Matriz tm; return resta(*this, m, tm);}


	//determinante
	float determinante();

	//trasposicion
	Matriz &trasponer();
	static Matriz &trasponer(const Matriz &m, Matriz &res) { res = m; return res.trasponer(); }
	static Matriz trasponer(const Matriz &m) { return Matriz(m).trasponer();}

	//inversa
	Matriz inversa();

	
	~Matriz(void);
};

#endif MATRIZ_H;
