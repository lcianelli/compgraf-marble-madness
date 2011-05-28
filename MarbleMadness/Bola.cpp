#include "Bola.h"


Bola::Bola(void)
{
	
	this->centro = new float[3];
	this->rotacion = new float[3];

	this->piso = NULL;
	this->velocidad = new float[3];

	this->posicion = new float[3]; // posicion respecto a sus coordenadas locales

	this->escalado = new float[3];
	escalado[0]= 1.0;
	escalado[1]= 1.0;
	escalado[2]= 1.0;

	this->colisione =false;


	for (int i = 0; i < 3; i++) {
		centro[i] = rotacion[i] = velocidad[i] = posicion[i] = 0.f;
	}

	this->cantSalto = 0.1;
	this->salto = 0.0;
	this->AnguloGiroAnteriorEjeY = 0.0;
	this->matrizTransformacion = Matriz();


}

void Bola::setCentro(float cx, float cy, float cz) {
	centro[0] = cx;
	centro[1] = cy;
	centro[2] = cz;
}

void Bola::setRotacion(float ax, float ay, float az) {
	rotacion[0] = ax;
	rotacion[1] = ay;
	rotacion[2] = az;
}

Bola::~Bola(void)
{
}

void Bola::dibujar() {


	// cambio isa 16/5/2011
	//glPushMatrix();
		//glTranslatef(centro[0], centro[1], centro[2]);


//		gluSphere(sphereQuadric, this->r, 50, 50);
	
	// cambio isa 16/5/2011
		//glPopMatrix();

	//	glRotatef(rotacion[0],1.f,0.f,0.f);
	//	glRotatef(rotacion[2],0.f,0.f,1.0);

	glBegin(GL_LINE);
		glColor3f(1.0,0.0,0.0);
		glVertex3f(100.0,0.0,0.0);
		glVertex3f(-100.0,0.0,0.0);
		glColor3f(0.0,1.0,0.0);
		glVertex3f(0.0,100.0,0.0);
		glVertex3f(0.0,-100.0,0.0);
		glColor3f(0.0,0.0,1.0);
		glVertex3f(0.0,0.0,100.0);
		glVertex3f(0.0,0.0,-100.0);
	glEnd();


		glColor3ub(255, 0, 0);
	//
		GLUquadric* sphereQuadric = gluNewQuadric();

		gluSphere(sphereQuadric, 2.0, 50, 50);
	//
	//// cambio isa 16/5/2011
	//	glPopMatrix();

		gluDeleteQuadric(sphereQuadric);
}

void Bola::setPiso(ObjetoEstatico* obj){
	this->piso=obj;
}

ObjetoEstatico* Bola::dondeEstoy() {

	//TODO: obtener la posicion donde estoy en la grilla

	return this->piso;
}


