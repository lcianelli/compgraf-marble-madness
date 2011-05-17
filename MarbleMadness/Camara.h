#pragma once

#include <SDL.h>
#include <SDL_opengl.h>


#define pi 3.1415926535


class Camara
{
private:
	static Camara* instancia;
	GLfloat xMouse;
	GLfloat yMouse;
	GLboolean bottonDerDown;
	Camara(void);
public:

	static Camara* inst() {
		if (!instancia) {
			instancia = new Camara();
		}
		return instancia;
	}

	GLfloat getXMouse();

	void setXMouse(GLfloat newXMouse);

	GLfloat getYMouse();

	void setYMouse(GLfloat newYMouse);

	void manejadorComienzoMovimientoCamara(SDL_MouseButtonEvent* mouse);

	void manejadorMovimientoCamara(SDL_MouseMotionEvent* mouse);

	void manejadorFinMovimientoCamara(SDL_MouseButtonEvent* mouse);

	~Camara(void);
};

