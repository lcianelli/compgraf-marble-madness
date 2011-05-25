#pragma once
#ifndef MENU_GUI_H
#define MENU_GUI_H

#include "ObjetoGUI.h"
#include "BotonGUI.h"

namespace mmgui {

class MenuGUI : public ObjetoGUI
{
protected:
	int idTextura;
	BotonGUI* botonCierre;
public:

	MenuGUI();
	MenuGUI(int x, int y, int w, int h);	
	
	//le da el id de la textura a usar como imagen
	inline void setImagen(int idTex) { this->idTextura = idTex;}

	void dibujar();

	BotonGUI* getBotonCiere() const { return this->botonCierre;} 

	ObjetoGUI* objetoClickeado(int x, int y);
	
	virtual ~MenuGUI(void);
};

}

#endif MENU_GUI_H;
