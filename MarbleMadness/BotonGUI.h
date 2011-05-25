#pragma once
#ifndef BOTON_GUI_H
#define BOTON_GUI_H

#include <string>

#include "ObjetoGUI.h"
#include "Vector.h"

namespace mmgui {

class BotonGUI : public ObjetoGUI
{
private:
	int idTextura;
	string texto;
	

public:
	BotonGUI();
	BotonGUI(int x, int y, int w, int h);
	BotonGUI(int x, int y, int w, int h, const string &texto);
	BotonGUI(const string &texto);

	void setTexto(const string &texto);
	const string getTexto() const { return this->texto;}	


	//le da el id de la textura a usar como imagen
	inline void setImagen(int idTex) { this->idTextura = idTex;}

	void dibujar();
	virtual ~BotonGUI(void);
};

}

#endif BOTON_GUI_H;
