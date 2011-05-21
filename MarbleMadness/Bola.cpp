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
	rotacion[0] = ax;
	rotacion[1] = ay;
	rotacion[2] = az;
}

Bola::~Bola(void)
{
}

void Bola::dibujar() {


	// cambio isa 16/5/2011
	glPushMatrix();
		glTranslatef(centro[0], centro[1], centro[2]);


//		gluSphere(sphereQuadric, this->r, 50, 50);
	
	// cambio isa 16/5/2011
		glPopMatrix();

	//	glRotatef(rotacion[0],1.f,0.f,0.f);
	//	glRotatef(rotacion[2],0.f,0.f,1.0);
	//	glColor3ub(255, 0, 0);
	//
	//	GLUquadric* sphereQuadric = gluNewQuadric();

	//	gluSphere(sphereQuadric, this->r, 50, 50);
	//
	//// cambio isa 16/5/2011
	//	glPopMatrix();

	//gluDeleteQuadric(sphereQuadric);
}

void Bola::actualizar(int tiempo) {
	if (!this->actualizado) {
		int dT = tiempo;
		int tiempoTranscurrido;
		while (dT > 0) {
			tiempoTranscurrido = dT; //me dirá el tiempo transcurrido hasta el momento en que ocurra un choque. Inicializamos en dT por si no ocurre
			Rayo rMov(Vector(this->centro), Vector(this->direccion).unitario());
			float distanciaChoque;
			Vector normalChoque;
			Vector puntoChoque;
			ObjetoJuego* objChoque = calcularProximaInteraccion(rMov, distanciaChoque, normalChoque, puntoChoque);			
			
			if (objChoque != NULL && distanciaChoque >= CERO ) {
				if (acelerar && fabs(modAceleracion ) != CERO) {
					tiempoTranscurrido = (-modVelocidad + sqrtf(sqr(modVelocidad) + 2.f*modAceleracion*(distanciaChoque))) / modAceleracion;
				} else {
					tiempoTranscurrido = distanciaChoque / modVelocidad;	
				}				
			} 
			
			if (tiempoTranscurrido <= dT) {
				actualizarMovimiento(tiempoTranscurrido);
				procesarInteraccion(objChoque, tiempoTranscurrido, distanciaChoque, normalChoque, puntoChoque);
			} else {				
				actualizarMovimiento(dT);
			}
		
			dT -= tiempoTranscurrido;

		}
		this->actualizado = true;
	}	
}

//NO SE USA MAS
void Bola::actualizarFisica(int tiempo) {
	
	/*list<ObjetoJuego*> l;
	interactuar(&l);
	//ahora calculo nueva velocidad;
	float* aceleracion = new float[3];
	for (int i = 0; i < 3; i++) {
		aceleracion[i] = this->fuerza[i] * this->masa * this->modfuerza;
		
		direccion[i] += (aceleracion[i]*tiempo*tiempo)/2.f + velocidad[i]*tiempo;
		velocidad[i] += aceleracion[i]*tiempo;
		
	}
	modVelocidad = modulo(velocidad, 3);
	//normalizar(direccion, 3);
	delete [] aceleracion;*/
}


//NO SE USA MAS
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

//NO SE USA MAS
float* Bola::getFuerzaAplicada(ObjetoJuego* obj, float &modulo) {
	return 0;
}

//NO SE USA MAS
float* Bola::getNormalInteraccion(ObjetoJuego* obj) {
	return 0;
}

//
void Bola::setPiso(ObjetoEstatico* obj){
	this->piso=obj;
}

ObjetoEstatico* Bola::dondeEstoy() {

	//TODO: obtener la posicion donde estoy en la grilla

	return this->piso;
}

void Bola::actualizarMovimiento(int tiempo) {
	Vector vel = Vector(this->direccion).unitario();
	Vector aceleracion = Vector(this->fuerza).unitario()*modfuerza*masa;
	Vector desplazamiento = Vector(aceleracion*modAceleracion*(float)tiempo*(float)tiempo*(1.f/2.f) + vel*(float)tiempo);
	Vector pos = Vector(this->centro);

	pos += desplazamiento;
	Vector dV = (aceleracion*tiempo).unitario();
	vel += dV;	
	modVelocidad += (aceleracion*tiempo).norma();
	vel = vel.unitario();
	if (modVelocidad > BOLA_VEL_MAX) {
		aceleracion = Vector(0.f, 0.f, 0.f);
		modVelocidad = BOLA_VEL_MAX;
	}
	delete [] this->direccion;
	delete [] this->centro;
	this->centro = pos.floatArr();
	direccion = vel.floatArr();
	
}

ObjetoJuego* Bola::calcularProximaInteraccion(const Rayo &rMovimiento, float distanciaChoque, Vector &normalChoque, Vector &puntoChoque) {
	//TODO: implementar!!!!
	return NULL;
}	

void Bola::procesarInteraccion(ObjetoJuego* objChoque, float tiempoTranscurrido, float distanciaChoque, Vector &normalChoque, Vector& puntoChoque) {
	//TODO: implementar!!!
}