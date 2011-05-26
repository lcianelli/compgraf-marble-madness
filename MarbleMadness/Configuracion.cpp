#include "Configuracion.h"

Configuracion* Configuracion::instancia = 0;

Configuracion::Configuracion(void)
{
}


Configuracion::~Configuracion(void)
{
}

void Configuracion::inicializar()
{	
	//INICIALIZO LOS ATRIBUTOS DE INSTANCIA!!!!!

	for(int i=0; i<5; i++){
		for(int j=0; j<4;j++){
			instancia->direccionesLuz[i][j]=0.0f;
			instancia->lucesAmbiente[i][j]=1.0f;
			instancia->lucesDifusas[i][j]=1.0f;
			instancia->lucesEspeculares[i][j]=1.0f;
		}
	}

	instancia->cambiarLuz=false;
	instancia->texturas=true;
	instancia->wireframe=false;
	instancia->interpolado=true;
	instancia->velocidad=1.0f;
	instancia->direccionesLuz[0][0]=-1.0f;
	instancia->direccionesLuz[0][1]=1.0f;
	instancia->direccionesLuz[0][2]=1.0f;
	instancia->direccionesLuz[0][3]=0.0f;


	glLightfv(GL_LIGHT0, GL_AMBIENT, instancia->lucesAmbiente[0]);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, instancia->lucesDifusas[0]);
	glLightfv(GL_LIGHT0, GL_SPECULAR, instancia->lucesEspeculares[0]);
	glLightfv(GL_LIGHT0, GL_POSITION, instancia->direccionesLuz[0]);

	//Al inicio comienzo con las luces habilitadas
	// Setup lighting
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
}

void Configuracion::setWireframe(bool w)
{
	wireframe=w;
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); esto es para mostrar todo como wireframe
}

bool Configuracion::getWireframe()
{
	return wireframe;
}

void Configuracion::setInterpolado(bool i)
{
	interpolado=i;
}

bool Configuracion::getInterpolado()
{

	return interpolado;
}

float* Configuracion::getColorLuz(int luz)
{
	return instancia->lucesDifusas[luz];
}


void Configuracion::setTexturas(bool t)
{
	texturas=t;
}

bool Configuracion::getTexturas()
{
	return texturas;
}

void Configuracion::aumentarR(int id)
{
	if(instancia->lucesDifusas[id][0]!=1.0f)
		instancia->lucesDifusas[id][0]+=0.1f;
}

void Configuracion::aumentarG(int id)
{
	if(instancia->lucesDifusas[id][1]!=1.0f)
		instancia->lucesDifusas[id][1]+=0.1f;
}

void Configuracion::aumentarB(int id)
{
	if(instancia->lucesDifusas[id][2]!=1.0f)
		instancia->lucesDifusas[id][2]+=0.1f;
}



void Configuracion::disminuirR(int id)
{
	if(instancia->lucesDifusas[id][0]!=0.0f)
		instancia->lucesDifusas[id][0]-=0.1f;
}


void Configuracion::disminuirG(int id)
{
	if(instancia->lucesDifusas[id][1]!=0.0f)
		instancia->lucesDifusas[id][1]-=0.1f;
}

void Configuracion::disminuirB(int id)
{
	if(instancia->lucesDifusas[id][2]!=0.0f)
		instancia->lucesDifusas[id][2]-=0.1f;
}


bool Configuracion::getCambiarLuz()
{
	return instancia->cambiarLuz;
}

void Configuracion::setCambiarLuz(bool c)
{
	instancia->cambiarLuz=c;
}

float* Configuracion::getDireccionLuz(int id) {
	return direccionesLuz[id];
}

void Configuracion::setDireccionLuz(int id, float* dir) {
	for (int i = 0; i < 4; i++) {
		direccionesLuz[id][i] = dir[i];
	}
}
