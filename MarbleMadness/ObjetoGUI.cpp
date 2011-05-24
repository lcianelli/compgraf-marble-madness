#include "ObjetoGUI.h"

namespace mmgui {

ObjetoGUI::~ObjetoGUI(void)
{
	this->padre = NULL;
	removerHijos();
}

void ObjetoGUI::agegarHijo(ObjetoGUI* h) {
	this->hijos.push_back(h);
	h->setPadre(this);
}

void ObjetoGUI::agregarHijoEn(ObjetoGUI* h, int indice) {
	this->hijos[indice] = h;
}

void ObjetoGUI::removerHijoEn(int indice) {
	this->hijos[indice] = NULL;
}

void ObjetoGUI::removerHijos() {
	this->hijos.clear();
}

void ObjetoGUI::setLimites(int x, int y, int w, int h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

bool ObjetoGUI::clicked(int x, int y) {
	return (x >= this->x && x <= this->x+this->w && y >= this->y && y <= this->y + this->h );
}

}