#include "MenuGUI.h"

namespace mmgui {

MenuGUI::MenuGUI(void)
{
	this->x = this->y = this->w = this->h = 0;
	this->botonCierre = new BotonGUI();
	this->agegarHijo(botonCierre);
	//TODO: inicializar textura del boton de cierre;
	

}

MenuGUI::MenuGUI(int x, int y, int w, int h) {
	setLimites(x, y, w, h);
	this->botonCierre= new BotonGUI(w-20, h-20, 10, 10);
	this->agegarHijo(botonCierre);
	//TODO: inicializar textura del boton de cierre;
}

void MenuGUI::dibujar() {
	if (this->idTextura >= 0) {
		glBindTexture(GL_TEXTURE_2D, this->idTextura);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);	
		
	}
	glTexCoord2f(1.0f, 0.0f); glVertex2i(this->w, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(this->w, this->h);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0, this->h);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 0);	

	vector<ObjetoGUI*>::iterator it;
	for (it = this->hijos.begin(); it != this->hijos.end(); it++) {
		glPushMatrix();
		ObjetoGUI* hijo = (*it);
		glTranslatef((float)hijo->X(), (float)hijo->Y(), 0.f);	
		hijo->dibujar();
		glPopMatrix();	
	}
}



MenuGUI::~MenuGUI(void)
{
}

}
