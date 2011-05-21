#pragma once
#ifndef MATRIZ_H
#define MATRIZ_H

#include "Mathex.h"

class Vector;

class Matriz
{
private:
	float _Mx[3][3];

public:
	Matriz();
	Matriz(float phi, float theta, float psi);
	Matriz(float mx00, float mx01, float mx02, float mx10, float mx11, float mx12, float mx20, float mx21, float mx22);

	float operator()(int row, int col) const { return _Mx[row][col];}
	float &operator()(int row, int col) {return _Mx[row][col];}

	//métodos aritméticos optimizados

	static Matriz &suma(const Matriz &m1, const Matriz &m2, Matriz &res);
	static Matriz &resta(const Matriz &m1, const Matriz &m2, Matriz &res);
	static Matriz &multiplicar(const Matriz &m1, const Matriz &m2, Matriz &res);
	static Matriz &multiplicar(const Matriz &m1, const float &escala, Matriz &res);
	static Vector &multiplicar(const Matriz &m1, const Vector &v, Vector &result);

	//aritmética de matrices

	Matriz &operator+=(const Matriz &m) { return suma(*this, m, *this);}
	Matriz &operator-=(const Matriz &m) { return resta(*this, m, *this);}
	Matriz &operator*=(const Matriz &m) {Matriz tm(*this); return multiplicar(tm, m, *this);}
	Matriz &operator*=(const float &escala) { return multiplicar(*this, escala, *this);}
	Matriz &operator+(const Matriz &m) const { Matriz tm; return suma(*this, m, tm);}
	Matriz &operator-(const Matriz &m) const { Matriz tm; return resta(*this, m, tm);}
	Matriz &operator*(const Matriz &m) const { Matriz tm; return multiplicar(*this, m, tm);} 
	Matriz &operator*(const float &escala) const { Matriz tm; return multiplicar(*this, escala, tm);}
	Vector operator*(const Vector &v) const;

	//determinante
	float determinante() const;
	static float determinante(const Matriz &m) { return m.determinante();}

	//trasposicion
	Matriz &trasponer();
	static Matriz &trasponer(const Matriz &m, Matriz &res) { res = m; return res.trasponer(); }
	static Matriz trasponer(const Matriz &m) { return Matriz(m).trasponer();}

	//inversa
	static Matriz &Matriz::inversa(const Matriz &m1, Matriz &res);
	static Matriz Matriz::inversa(const Matriz &m1) { Matriz tm; return inversa(m1, tm);}
	Matriz inversa() const {Matriz tm; return inversa(*this, tm);}
	
	~Matriz(void);
};

#endif

