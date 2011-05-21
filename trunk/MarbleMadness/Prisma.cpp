#include "Prisma.h"


Prisma::Prisma(void): ObjetoEstatico()
{
	this->objeto= new GLMmodel();
	objeto = glmReadOBJ("modelos/objetoPrisma10.obj");
}


Prisma::~Prisma(void)
{
}

void Prisma::dibujar() {

	glMaterialfv(GL_FRONT_AND_BACK, GL_COLOR_MATERIAL, objeto->materials[1].emmissive);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objeto->materials[1].diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objeto->materials[1].specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, objeto->materials[1].shininess);

	//GLfloat escalado = this->altura/10.0;
	//GLfloat translado = (10.0/2)*escalado + (10.0/2)*(1-escalado);

	//glScaled(1,this->altura/10.0,1);


	//glTranslatef(0.0,translado,0.0);

	glmDraw(objeto, GLM_SMOOTH);

	//glTranslatef(0.0,-translado,0.0);

	//glScaled(1,10.0/this->altura,1);

}

void Prisma::actualizar(int tiempo) {

}

void Prisma::actualizarFisica(int tiempo) {
	//nada...
}

void Prisma::interactuar(list<ObjetoJuego*>* interactores) {

}


float* Prisma::getFuerzaAplicada(ObjetoJuego* obj, float &modulo) {
	float* fuerzaAplicada = new float[3];
	float* reaccion = getNormalInteraccion(obj);
	
	
	modulo = obj->modfuerza;
	return fuerza;
}


float* Prisma::getNormalInteraccion(ObjetoJuego* obj) {
	float * normal = new float[3];

	//TODO: almacenar en "normal" los datos de la normal a la cara con la que obj interactua, en la misma direccion desde la que obj "golpea"

	normalizar(normal, 3);
	return normal;	
}

