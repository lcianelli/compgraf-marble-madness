#pragma once
#ifndef SLIDEBARGUI_H
#define SLIDEBARGUI_H


#include "ObjetoGUI.h"
#include "Vector.h"

namespace mmgui{

class SlidebarGUI : public ObjetoGUI
{
protected:
	float valorMin;
	float valorMax;
	float valorActual;
	int idTexturaBarra;
	int idTexturaMarcador;
	Vector colorMarcador;
	
public:
	SlidebarGUI(float min, float max, float inicio);
	SlidebarGUI(int x, int y, int w, int h, float min, float max, float inicio);


	inline float Min() { return this->valorMin;}
	inline float Max() { return this->valorMax;}
	inline float Actual() { return this->valorActual; }

	inline void Min(float min) { this->valorMin = min;}
	inline void Max(float max) {this->valorMax = max;}
	inline void Actual(float actual) { this->valorActual = actual;}

	void actualizar(int desplazamiento);

	void dibujar();

	bool clicked(int x, int y);

	~SlidebarGUI(void);
};

}

#endif SLIDEBARGUI_H;