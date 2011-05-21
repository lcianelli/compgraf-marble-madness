#include "Escenario.h"

#include "Prisma.h"
#include "Rampa.h"


Escenario::Escenario(void)
{
	for (int i = 0; i < MATRIZ_DIMENSION; i++) {
		for (int j = 0; j < MATRIZ_DIMENSION; j++) {
			this->grilla[i][j] = NULL;
		}
	}
	Ambiente::init();
}




void Escenario::dondeEstoy(float x, float z, int &t, int &s){
	t=x/ANCHO_CELDA_GRILLA;
	s=z/ANCHO_CELDA_GRILLA;
}

ObjetoJuego* Escenario::obtenerObjeto(int t, int s){
	return this->grilla[t][s];
}

void Escenario::agregarObjeto(ObjetoJuego* obj) {
	if (obj->esEstatico())  {
		this->objsEstaticos.push_back(dynamic_cast<ObjetoEstatico*>(obj));
	}
}


Escenario::~Escenario(void)
{

	
}

void Escenario::dibujar() {
	//TODO: dibujar cosas del escenario, en caso de que las tenga, luces, decorados, etc.

	//Dibujo cada objeto que forma parte de la escena
/*
	list<ObjetoEstatico*>::iterator itEst;
	for (itEst = this->objsEstaticos.begin(); itEst != this->objsEstaticos.end(); itEst++) {
		glTranslatef();
		(*itEst)->dibujar();
	}

*/
	//glScaled(MATRIZ_SUELO_W,MATRIZ_SUELO_H,1);
	//glTranslatef(0,0,-10);

	GLfloat escalado;
	GLfloat translado;

	for(int i=0;i<MATRIZ_DIMENSION;i++){
		glTranslatef(ANCHO_CELDA_GRILLA*i,0,0);
		for(int j=0;j<MATRIZ_DIMENSION;j++){
			glTranslatef(0,0,-ANCHO_CELDA_GRILLA*j);

			escalado = ((float)(this->grilla[i][j])->getAltura())/ANCHO_CELDA_GRILLA;
			translado = (ANCHO_CELDA_GRILLA/2.0)*escalado + (ANCHO_CELDA_GRILLA/2.0)*(1.0-escalado);
			glScaled(1, ((float)(this->grilla[i][j])->getAltura())/ANCHO_CELDA_GRILLA,1);
			glTranslatef(0.0,translado,0.0);

			this->grilla[i][j]->dibujar();
			glTranslatef(0,0,ANCHO_CELDA_GRILLA*j);

			glTranslatef(0.0,-translado,0.0);
			glScaled(1,ANCHO_CELDA_GRILLA/((float)(this->grilla[i][j])->getAltura()),1);

		}
		glTranslatef(-ANCHO_CELDA_GRILLA*i,0,0);
	}
	//glTranslatef(0,0,10);
	//glScaled(1/MATRIZ_SUELO_W,1/MATRIZ_SUELO_H,1);

}

void Escenario::actualizar(int tiempo) {
	//TODO: actualizar cosas del escenario, en caso de que las tenga, luces, decorados, etc.

	//Actualizo cada objeto que forma parte de la escena


	list<ObjetoEstatico*>::iterator itEst;
	for (itEst = this->objsEstaticos.begin(); itEst != this->objsEstaticos.end(); itEst++) {
		(*itEst)->actualizar(tiempo);
	}
}

void Escenario::cargarObjeto(int s, int t, float objH, TipoObjeto tipo, int objH2, int rot){
	ObjetoEstatico* objeto;
	if(tipo == PRISMA){
		objeto = new Prisma();
	}else if(tipo == RAMPA){
		objeto = new Rampa();
		((Rampa*)objeto)->setAlturaSueloRampa(objH2);
	}
	objeto->setAltura(objH);

	this->grilla[s][t]= objeto;
}


