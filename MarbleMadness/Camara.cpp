#include "StdAfx.h"
#include "Camara.h"

#include <math.h>

Camara* Camara::instancia = 0;

Camara::Camara(void)
{
	this->xMouse= 0.0;
	this->yMouse= 0.0;
	this->bottonDerDown= false;
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



Camara::~Camara(void)
{
}
