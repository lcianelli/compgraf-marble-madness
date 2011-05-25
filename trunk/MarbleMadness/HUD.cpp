#include "HUD.h"
#include <iostream>

#include <string>

using namespace std;

const int FUENTE_HUD_MAIN_SIZE = 16;

void descomponerTiempo(int tmilis, int &minutos, int &segundos, int &decimas);

HUD::HUD(int puntajeInicial, int tiempoTotal, int nivel)
{
	
	this->puntaje = puntajeInicial;
	this->tiempoInicial = this->tiempo = tiempoTotal;
	this->nivel = nivel;
	this->fuenteHudMain.init("fuentes\\test.TTF", FUENTE_HUD_MAIN_SIZE);
}

void HUD::dibujarHud()
{
	int mins, segs, deci;
	descomponerTiempo(tiempo, mins, segs, deci);
	SDL_Surface* s = SDL_GetVideoSurface();
	int windowW = s->w;
	int windowH = s->h;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glDisable(GL_LIGHTING);
		glLoadIdentity();

		
		glOrtho(0.f, s->w, 0.f, s->h, -1.f, 1.f);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glViewport(0, 0, (GLsizei) s->w, (GLsizei) s->h);
			
		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	////



	glPushMatrix();
	glLoadIdentity();

	
	glColor3ub(0, 120, 200);

	print(fuenteHudMain, windowW/2-8*FUENTE_HUD_MAIN_SIZE, windowH-1.6*FUENTE_HUD_MAIN_SIZE, "Tiempo: ");
	int x= windowW/2;
	float escala = 1.f;
	glPushMatrix();
	if (tiempo < tiempoInicial*0.15f) {
		glColor3ub(255, 0, 0);
		escala = 1.6f;
		glScalef(escala, escala, escala);
		
	} else if (tiempo < tiempoInicial*0.35f) {
		glColor3ub(244, 252, 5);
		escala = 1.3f;
		glScalef(escala, escala, escala);
	} else {
		glColor3ub(35, 255, 35);
	}
	if (mins > 0) {
		print(fuenteHudMain, x, windowH-FUENTE_HUD_MAIN_SIZE*escala - 10/escala, "%i:", mins);
		x+= 25;
	} 

	print(fuenteHudMain, x, windowH-FUENTE_HUD_MAIN_SIZE*escala - 10/escala, "%02i.", segs);
	x+= 38*escala;
	float escaladeci = escala * 0.6f;
	glScalef(escaladeci, escaladeci, escaladeci);
	print(fuenteHudMain, x, windowH-FUENTE_HUD_MAIN_SIZE*escala - 10/escala, "%02i", deci);
	
	glPopMatrix();
	glColor3ub(154, 0, 50);
		print(fuenteHudMain, 20, 20, "Puntaje: %i", this->puntaje);

	glColor3ub(255, 200, 255);
	print(fuenteHudMain, windowW-100, 20, "Nivel: %i", this->nivel);
	glPopMatrix();
	
	
	
	

	

}


void HUD::actualizar(int tiempoTranscurrido) {
	
	if (this->tiempo / 1000 > (this->tiempo - tiempoTranscurrido) / 1000) {
		this->puntaje--;
	}	
	this->tiempo -= (tiempo >= tiempoTranscurrido) ? tiempoTranscurrido : tiempo;
}

void descomponerTiempo(int tmilis, int &minutos, int &segundos, int &decimas) {
	int taux = tmilis;
	minutos = (taux/1000)/60;
	taux -= minutos*1000*60;
	segundos = taux / 1000;
	taux -= segundos*1000;
	decimas = taux / 10;
	
}



HUD::~HUD(void)
{
	this->fuenteHudMain.clean();
}
