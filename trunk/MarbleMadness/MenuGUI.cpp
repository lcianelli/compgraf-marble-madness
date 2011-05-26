#include "MenuGUI.h"

namespace mmgui {

MenuGUI::MenuGUI(void)
{
	this->x = this->y = this->w = this->h = 0;
	this->botonCierre = new BotonGUI();
	this->agegarHijo(botonCierre);
	this->idTextura = -1;
	//TODO: inicializar textura del boton de cierre;
	

}

MenuGUI::MenuGUI(int x, int y, int w, int h) {
	setLimites(x, y, w, h);
	this->botonCierre= new BotonGUI(w-20, h-20, 10, 10);
	this->agegarHijo(botonCierre);
	//TODO: inicializar textura del boton de cierre;
}

void MenuGUI::dibujar() {
	
	vector<ObjetoGUI*>::iterator it;
	for (it = this->hijos.begin(); it != this->hijos.end(); it++) {
		//glPushMatrix();
		ObjetoGUI* hijo = (*it);
		glTranslatef((float)hijo->X(), (float)hijo->Y(), 0.f);	
		hijo->dibujar();
		glTranslatef(-(float)hijo->X(), -(float)hijo->Y(), 0.f);	
		//glPopMatrix();	
	}

	if (this->idTextura >= 0 && Configuracion::inst()->getTexturas()) {
		glBindTexture(GL_TEXTURE_2D, idTextura);
		glEnable( GL_TEXTURE_2D );
		//NO DESCOMENTARRRR, CAGA TODOOOOOOOOO
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);	
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);	
		
	} else {
		glColor3f(color.X(), color.Y(), color.Z());
	}
	
	glBegin(GL_QUADS);
		
		glTexCoord2f( 0.f, 1.0f );
		glVertex3f(0, this->h, 0);
		glTexCoord2f( 0.f, 0.f );
		glVertex3f(0.f, 0.f,0.f);
		
		glTexCoord2f( 1.f, 0.f );
		glVertex3f(this->w, 0, 0);
		glTexCoord2f( 1.f, 1.f );
		glVertex3f(this->w, this->h, 0);
		
	glEnd();
	if (this->idTextura >= 0 && Configuracion::inst()->getTexturas()) {
		glBindTexture(GL_TEXTURE_2D, 0);//"unbind" :P
		glDisable( GL_TEXTURE_2D );
	}
	
}



MenuGUI::~MenuGUI(void)
{
}

ObjetoGUI* MenuGUI::objetoClickeado(int x, int y) {
	if (clicked(x, y) ){
		vector<ObjetoGUI*>::iterator it;
		for (it = this->hijos.begin(); it != this->hijos.end(); it++) {			
			ObjetoGUI* hijo = (*it);
			if (hijo->clicked(x-X(), y-Y())) {
				return hijo;//se clickeo un hijo
			}
		}
		return this;

	} else {
		return 0;
	}
	
}

}
