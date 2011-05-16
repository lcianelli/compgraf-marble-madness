#include "Bola.h"


Bola::Bola(void)
{
	
	this->centro = new float[3];
	this->rotacion = new float[3];
	this->direccion = new float[3];
	this->fuerza = new float[3];
	this->modfuerza = 0.f;
	this->modVelocidad = 0.f;
	this->piso = NULL;
	this->velocidad = new float[3];
	this->acelerar = false;

	for (int i = 0; i < 3; i++) {
		centro[i] = rotacion[i] = direccion[i] = fuerza[i] = velocidad[i] = 0.f;
	}

}

void Bola::setCentro(float cx, float cy, float cz) {
	centro[0] = cx;
	centro[1] = cy;
	centro[2] = cz;
}

void Bola::setRotacion(float ax, float ay, float az) {
	centro[0] = ax;
	centro[1] = ay;
	centro[2] = az;
}

Bola::~Bola(void)
{
}

void Bola::dibujar() {
	glPushMatrix();
		glTranslatef(centro[0], centro[1], centro[2]);

		glRotatef(rotacion[0],1.f,0.f,0.f);
		glRotatef(rotacion[2],0.f,0.f,1.0);
		glColor3ub(255, 0, 0);
	
		GLUquadric* sphereQuadric = gluNewQuadric();

		gluSphere(sphereQuadric, this->r, 50, 50);
	
	glPopMatrix();

	gluDeleteQuadric(sphereQuadric);
}

void Bola::actualizar(int tiempo) {
	

	if (acelerar) {
		this->centro[0] += (this->direccion[0]*this->modfuerza/this->masa)*tiempo*tiempo;
		this->centro[1] += (this->direccion[1]*this->modfuerza/this->masa)*tiempo*tiempo;
		this->centro[2] += (this->direccion[2]*this->modfuerza/this->masa)*tiempo*tiempo;
	} else {
		this->centro[0] += this->direccion[0]*this->modVelocidad*tiempo;
		this->centro[1] += this->direccion[1]*this->modVelocidad*tiempo;
		this->centro[2] += this->direccion[2]*this->modVelocidad*tiempo;
	}
	
	//cout << "centro " << centro[0] << "," << centro[1] << "," << centro[2] << endl;
	
	this->rotacion[0] = this->direccion[0]*this->modVelocidad*tiempo;
	this->rotacion[1] = this->direccion[1]*this->modVelocidad*tiempo;
	this->rotacion[2] = this->direccion[2]*this->modVelocidad*tiempo;

}

void Bola::actualizarFisica(int tiempo) {
	
	list<ObjetoJuego*> l;
	interactuar(&l);
	//ahora calculo nueva velocidad;
	float* aceleracion = new float[3];
	for (int i = 0; i < 3; i++) {
		aceleracion[i] = this->fuerza[i] * this->masa * this->modfuerza;
		
		direccion[i] += aceleracion[i]*tiempo/10.f;		
	}
	
	modVelocidad = modulo(direccion, 3);
	normalizar(direccion, 3);
	delete [] aceleracion;
}

void Bola::interactuar(list<ObjetoJuego*>* interactores) {
	float* fuerzaTotal = new float[3];
	float* fuerzaAplicada;
	float moduloFuerzaAplicada;

	//procesar gravedad
	for(int i = 0; i < 3; i++) {
		fuerzaTotal[i] = Ambiente::gravedad[i];
	}
	//TODO: procesar el objeto en el que estoy parado
	if (this->piso != 0) {

	}
	//FIN TODO

	list<ObjetoJuego*>::iterator it;
	for (it = interactores->begin(); it != interactores->end(); it++) {
		if (!(*it)->esEstatico()) {
			//TODO: Ver que hacemos cuando no es estatico XD
		} else {
			fuerzaAplicada = (*it)->getFuerzaAplicada(this, moduloFuerzaAplicada);
			for (int i = 0; i < 3; i++) {
				fuerzaTotal[i] += fuerza[i] * moduloFuerzaAplicada;
			}
			delete [] fuerzaAplicada;
		}
	}

	//actualizamos ahora las fuerzas actuantes sobre el objeto
	this->modfuerza = modulo(fuerzaTotal, 3);
	normalizar(fuerzaTotal, 3);
	for (int i = 0; i < 3; i++) {
		this->fuerza[i] = fuerzaTotal[i];
	}
	delete[] fuerzaTotal;
}

float* Bola::getFuerzaAplicada(ObjetoJuego* obj, float &modulo) {
	return 0;
}

float* Bola::getNormalInteraccion(ObjetoJuego* obj) {
	return 0;
}

ObjetoEstatico* Bola::dondeEstoy() {

	//TODO: obtener la posicion donde estoy en la grilla

	return 0;
}

