
#include "StdAfx.h"
#include "Camara.h"

#include <math.h>

Camara* Camara::instancia = 0;

Camara::Camara(void)
{
	this->xMouse= 0.0;
	this->yMouse= 0.0;
	this->bottonDerDown= false;
	//TODO: ver bien dond se inician estas variables
	this->puntoVista = new GLfloat[3];
	this->puntoVista[0]= 0.0;
	this->puntoVista[1]= 0.0;
	this->puntoVista[2]= 0.0;
	this->posicionCamara = new GLfloat[3];
	this->posicionCamara[0]= 50.0;
	this->posicionCamara[1]= 50.0;
	this->posicionCamara[2]= -50.0;
	this->vectorCamara = new GLfloat[3];
	this->vectorCamara[0]= 0.0;
	this->vectorCamara[1]= 10.0;
	this->vectorCamara[2]= 0.0;
}


GLfloat* Camara::getpuntoVista(){
	return this->puntoVista;
}

void Camara::setpuntoVista(GLfloat* newPto){
	this->puntoVista = newPto;
}

GLfloat* Camara::getposicionCamara(){
	return this->posicionCamara;
}

void Camara::setposicionCamara(GLfloat* newPto){
	this->posicionCamara = newPto;
}

GLfloat* Camara::getvectorCamara(){
	return this->vectorCamara;
}

void Camara::setvectorCamara(GLfloat* newVect){
	this->vectorCamara = newVect;
}

GLfloat Camara::getXMouse(){
	return this->xMouse;
}

void Camara::setXMouse(GLfloat newXMouse){
	this->xMouse= newXMouse;
}

GLfloat Camara::getYMouse(){
	return this->yMouse;
}

void Camara::setYMouse(GLfloat newYMouse){
	this->yMouse= newYMouse;
}

void Camara::manejadorComienzoMovimientoCamara(SDL_MouseButtonEvent* mouse){
	if( mouse->button == SDL_BUTTON_RIGHT ){
		GLfloat xAct = mouse->x;
		GLfloat yAct = mouse->y;
		this->setXMouse(xAct);
		this->setYMouse(yAct);
		this->bottonDerDown= true;
	}
}

void Camara::manejadorMovimientoCamara(SDL_MouseMotionEvent* mouse){
	
	if( this->bottonDerDown ){
			
		
		GLfloat xAct = mouse->x;
		GLfloat yAct = mouse->y;

			float Yangmove;

			if( (this->xMouse!=0.0) && (xAct!=0.0) ){
				GLfloat aux = (this->yMouse/this->xMouse)-(yAct/xAct);
				Yangmove = atan(aux);
				Yangmove = Yangmove*(180/pi);
			}else{
				Yangmove = 1;
			}

			glRotatef(Yangmove, 0.0, 1.0, 0.0);	

			this->setXMouse(xAct);
			this->setYMouse(yAct);
	}
}

void Camara::manejadorFinMovimientoCamara(SDL_MouseButtonEvent* mouse){
	if( mouse->button == SDL_BUTTON_RIGHT ){
		this->bottonDerDown= false;
	}
}

void Camara::setVista(GLfloat* pos, GLfloat* pto, GLfloat* vect){
	this->setposicionCamara(pos);
	this->setpuntoVista(pto);
	this->setvectorCamara(vect);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt( pos[0], pos[1], pos[2], pto[0], pto[1], pto[2], vect[0], vect[1], vect[2]); 	
}

Camara::~Camara(void)
{
}
