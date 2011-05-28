#include "SlidebarGUI.h"
#include <iostream>

using namespace std;

namespace mmgui {

int xFromValor(float valor, float min, float max, int w) {
	return (int)(((min-valor)/(max-valor))*w);
}

float valorFromX(float mini, float max, int w, int x) {
	if (x > w) return mini;
	if (x < 0) return max;
	return fabs((((float)(x))/((float)(w)))*(max-mini));
}

SlidebarGUI::SlidebarGUI(float min, float max, float inicio) {
	this->valorMin = min;
	this->valorMax = max;
	this->valorActual = inicio;
	setLimites(0, 0, 0, 0);
}

SlidebarGUI::SlidebarGUI(int x, int y, int w, int h, float min, float max, float inicio) {
	setLimites(x, y, w, h);
	Min(min);
	Max(max);
	Actual(inicio);
}

void SlidebarGUI::actualizar(int desplazamiento) {
	float dValor = desplazamiento*(Max() - Min())/w;
	valorActual += dValor;
	if (valorActual > Max() ) {
		valorActual = Max();
	} else if (valorActual<Min()) {
		valorActual =Min();
	}
	
}



void SlidebarGUI::dibujar() {

	glColor3f(1.f, 1.f, 1.f);
	int xref = this->w*(this->valorActual-this->valorMin)/(this->valorMax-this->valorMin);
	glBegin(GL_QUADS);
		glVertex3f(xref-5, 0, 0);
		glVertex3f(xref+5, 0, 0);
		glVertex3f(xref+5, h, 0);
		glVertex3f(xref-5, h, 0);

	glEnd();

	/*glColor3f(color.X(), color.Y(), color.Z());
	glBegin(GL_QUADS);
	glVertex3f(0.f, 0.f, 0.f );
	glVertex3f(w, 0.f, 0.f);
	glVertex3f(w, h, 0.f);
	glVertex3f(0.f, h, 0.f);
	glEnd();*/
	
	/*float wtresporc = this->w*0.03f;
	float hcincoporc = this->h*0.05f;
	//glTexCoord2f(1.0f, 0.0f);
		glColor3f(color.X(), color.Y(), color.Z());
		glBegin(GL_QUADS);

		glVertex3f(xFromValor(this->valorActual, this->valorMin, this->valorMax, this->w)+wtresporc, 0-hcincoporc, 0);
		//glTexCoord2f(1.0f, 1.0f); 
		glVertex3f(this->w-wtresporc, this->h-hcincoporc, 0);
		//glTexCoord2f(0.0f, 1.0f); 
		glVertex3f(0+wtresporc, this->h-hcincoporc, 0);
		//glTexCoord2f(0.0f, 0.0f); 
		glVertex3f(0+wtresporc, 0+hcincoporc, 0);	
		glEnd();*/
}


SlidebarGUI::~SlidebarGUI(void)
{
}

bool SlidebarGUI::clicked(int x, int y) {
	cout << "x" << x << ", y" << y << endl;
	int coef = w*(valorActual-valorMin)/(valorMax-valorMin);
	return (y >= this->y && y <= this->y + this->h) && (x >= this->x + coef-5) && (x <= this->x + coef +5);
}


}
