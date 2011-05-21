#include "Rampa.h"


Rampa::Rampa(void): ObjetoEstatico()
{
	this->objeto= new GLMmodel();
	this->objeto = glmReadOBJ("C:/Users/Isabela/Desktop/objetoRampa10.obj");
}


void Rampa::setAlturaSueloRampa(int nuevaAltura){
	this->setAlturaSuelo(nuevaAltura);
	glmTransformar(this->objeto, this->getAlturaSuelo());
}

Rampa::~Rampa(void)
{
}

void Rampa::dibujar() {

	glMaterialfv(GL_FRONT_AND_BACK, GL_COLOR_MATERIAL, objeto->materials[1].emmissive);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objeto->materials[1].diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objeto->materials[1].specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, objeto->materials[1].shininess);


	//TODO: ver dond meter el define del ancho y largo de las celdas.
	//GLfloat escalado = this->getAlturaSuelo()/10.0;
	//GLfloat translado = (10.0/2)*escalado + (10.0/2)*(1-escalado);

	//glScaled(1.0,escalado,1.0);
	//glTranslatef(0.0,translado,0.0);

	//glmDraw(objetoRelleno, GLM_SMOOTH);

//	glScaled(1.0,escalado,1.0);
	//glTranslatef(0.0,-translado*2,0.0);

	//escalado = this->getAltura()/10.0;
	//translado = (10.0/2)*escalado + (10.0/2)*(1-escalado);

	glTranslatef(0.0,this->getAlturaSuelo(),0.0);

	glmDraw(objeto, GLM_SMOOTH);

	glTranslatef(0.0,-this->getAlturaSuelo(),0.0);

	//glTranslatef(0.0,translado,0.0);

	//glScaled(1,10.0/this->altura,1);

}

void Rampa::actualizar(int tiempo) {

}

void Rampa::actualizarFisica(int tiempo) {
	//nada...
}

void Rampa::interactuar(list<ObjetoJuego*>* interactores) {

}


float* Rampa::getFuerzaAplicada(ObjetoJuego* obj, float &modulo) {
	float* fuerzaAplicada = new float[3];
	float* reaccion = getNormalInteraccion(obj);
	
	
	modulo = obj->modfuerza;
	return fuerza;
}


float* Rampa::getNormalInteraccion(ObjetoJuego* obj) {
	float * normal = new float[3];

	//TODO: almacenar en "normal" los datos de la normal a la cara con la que obj interactua, en la misma direccion desde la que obj "golpea"

	normalizar(normal, 3);
	return normal;	
}


