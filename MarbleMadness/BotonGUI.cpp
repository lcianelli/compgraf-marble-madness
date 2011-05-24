#include "BotonGUI.h"

namespace mmgui {

BotonGUI::BotonGUI() {
	this->h = this->w = this->x = this->y;
	this->idTextura = -1;
}

BotonGUI::BotonGUI(int x, int y, int w, int h) {
	setLimites(x, y, w, h);
	this->idTextura = -1;
}

BotonGUI::BotonGUI(int x, int y, int w, int h, const string &texto) {
	setLimites(x, y, w, h);
	this->texto = string(texto);
	this->idTextura = -1;
}

BotonGUI::BotonGUI(const string &texto) {
	setLimites(0, 0, 0, 0);
	this->texto = string(texto);
	this->idTextura = -1;
}

void BotonGUI::setTexto(const string &texto) {
	this->texto = string(texto);
}

BotonGUI::~BotonGUI(void)
{
	ObjetoGUI::~ObjetoGUI();
}

void BotonGUI::dibujar() {

	if (this->idTextura >= 0) {
		glBindTexture(GL_TEXTURE_2D, this->idTextura);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);	
		
	}
	glTexCoord2f(1.0f, 0.0f); glVertex2i(this->w, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(this->w, this->h);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0, this->h);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0, 0);	

	if (!texto.empty()) {
		//TODO: dibujar texto
	}

	vector<ObjetoGUI*>::iterator it;
	for (it = this->hijos.begin(); it != this->hijos.end(); it++) {
		glPushMatrix();
		ObjetoGUI* hijo = (*it);
		glTranslatef(hijo->X(), hijo->Y(), 0.f);	
		hijo->dibujar();
		glPopMatrix();	
	}

	


}

}
