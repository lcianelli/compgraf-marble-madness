#include "SlidebarGUI.h"


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
	int xActual = xFromValor(this->valorActual, this->valorMin, this->valorMax, this->w);
	xActual+= desplazamiento;
	valorActual = valorFromX(this->valorMin, this->valorMax, this->w, xActual);
}



void SlidebarGUI::dibujar() {
	float wtresporc = this->w*0.03f;
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
		glEnd();
}


SlidebarGUI::~SlidebarGUI(void)
{
}

}
