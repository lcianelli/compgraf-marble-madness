#pragma once
#ifndef OBJETO_GUI_H
#define OBJETO_GUI_H

#include <vector>
#include <SDL_opengl.h>
#include <SDL.h>
#include "Vector.h"

namespace mmgui {

using namespace std;

class ObjetoGUI
{

protected:
	ObjetoGUI* padre;
	vector<ObjetoGUI*> hijos;
	int x, y, w, h; //dimensiones del objeto
	Vector color;
public:

	void agegarHijo(ObjetoGUI* h);
	void agregarHijoEn(ObjetoGUI* h, int indice);
	void removerHijoEn(int indice);

	void removerHijos();

	virtual void dibujar() = 0;

	virtual void setLimites(int x, int y, int w, int h);

	virtual bool clicked(int x, int y);

	inline int X() {return this->x;}
	inline int Y() {return this->y;}
	inline int W() {return this->w;}
	inline int H() {return this->h;}
	inline Vector Color() {return this->color;}
	inline void Color(const Vector &col) { this->color = Vector(col);}

	inline void setPadre(ObjetoGUI* padre) { this->padre = padre;}
	
	virtual ~ObjetoGUI(void);
};

}



#endif OBJETO_GUI_H;
