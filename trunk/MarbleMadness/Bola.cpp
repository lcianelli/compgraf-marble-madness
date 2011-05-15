#include "Bola.h"


Bola::Bola(void)
{
}


Bola::~Bola(void)
{
}

void Bola::dibujar() {
}

void Bola::actualizar(int tiempo) {

}

void Bola::actualizarFisica(int tiempo) {
	

}

void Bola::interactuar(list<ObjetoJuego*> interactores) {
	float* fuerzaTotal = new float[3];
	list<ObjetoJuego*>::iterator it;
	for (it = interactores.begin(); it != interactores.end(); it++) {
		
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