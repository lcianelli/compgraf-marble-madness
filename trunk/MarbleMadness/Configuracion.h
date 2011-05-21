#pragma once
#ifndef MARBLE_CONFIGURACION_H
#define MARBLE_CONFIGURACION_H

#include <SDL.h>
#include <SDL_opengl.h>


class Configuracion
{
private:
	static Configuracion* instancia;
	Configuracion(void);

	float velocidad;
	bool texturas;
	bool interpolado;
	bool wireframe;
	bool cambiarLuz;

	//Por ahora solo permitimos cambiar la direccion y el color difuso de la luz de LIGHT0
	float direccionesLuz[5][4];
	float lucesDifusas[5][4];
	float lucesAmbiente[5][4];
	float lucesEspeculares[5][4];


public:
	static Configuracion* inst() {
		if (!instancia) {
			instancia = new Configuracion();
		}
		return instancia;
	}
	
	~Configuracion(void);
	void inicializar();
	float getVelocidad();
	bool getInterpolado();
	bool getTexturas();
	bool getWireframe();
	float* getDireccionLuz(int luz);
	float* getColorLuz(int luz);
	bool getCambiarLuz();

	void setVelocidad(float v);
	void setInterpolado(bool interpolado);
	void setTexturas(bool t);
	void setWireframe(bool w);
	void setLuz(int luz, float* direccion, float* color);
	void setCambiarLuz(bool c);

	//aumenta los valores de R, G y B en la luz id
	void aumentarR(int id);
	void aumentarG(int id);
	void aumentarB(int id);

	void disminuirR(int id);
	void disminuirG(int id);
	void disminuirB(int id);


};

#endif

