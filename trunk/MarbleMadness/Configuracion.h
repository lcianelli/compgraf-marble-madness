#pragma once
#ifndef MARBLE_CONFIGURACION_H
#define MARBLE_CONFIGURACION_H

#include <vector>

using namespace std;

class Configuracion
{
private:
	static Configuracion* instancia;
	Configuracion(void);

	float velocidad;
	bool texturas;
	bool interpolado;
	bool wireframe;
	vector<float*> direccionesLuz;
	vector<float*> coloresLuz;
	

public:
	
	~Configuracion(void);
	float getVelocidad();
	bool usarTexturas();
	bool usarInterpolado();
	bool mostrarWireframe();
	float* getDireccionLuz(int luz);
	float* getColorLuz(int luz);
	void setVelocidad(float v);
	void setInterpolado(bool interpolado);
	void setTexturas(bool t);
	void setWireframe(bool w);
	void setLuz(int luz, float* direccion, float* color);




};

#endif

