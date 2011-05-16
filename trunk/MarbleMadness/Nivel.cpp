#include "Nivel.h"

Nivel::Nivel(int num)
{
	this->numero = num;
	this->puntaje = 0;
	this->estado=no_iniciado;
	this->escenario= new Escenario();
	this->personaje=NULL;
	this->inicioNivel=NULL;
	this->finNivel=NULL;

	char* nomArch=new char[12];
	strcpy(nomArch,"nivel");
	char* nuevo=new char[2];
	nuevo=itoa(this->numero,nuevo,10);
	strcat(nomArch,nuevo);
	strcat(nomArch,".xml");
	cargar(nomArch);
}

void Nivel::cargar(char* nomArch)
{

}

Nivel::~Nivel(void)
{
}

void Nivel::iniciar() {
	this->escenario = new Escenario();
	this->personaje = new Personaje();	
	this->escenario->agregarObjeto(personaje);	
}

void Nivel::dibujar() {
	//dibujo el escenario

	this->escenario->dibujar();

	//TODO: Dibujar HUD
}

void Nivel::actualizar(int tiempo) {
	//TODO: actualizar HUD
	/**	
		TODO: "actualizacion logica": Termino el juego? está en pausa? Se dan condiciones 
		logicas para que haya un cambio de estado en el nivel? 
		EN GRAL.: ¿Sucedio algo que afecte al funcionamiento del juego?
	*/

	//actualizo la escena de juego
	
	this->escenario->actualizarFisica(tiempo);
	
	this->escenario->actualizar(tiempo);
}

void Nivel::teclaPresionada(SDL_keysym* keysym) {
	switch(keysym->sym) {
		case SDLK_UP:
			this->personaje->moverArriba();
			break;
		case SDLK_DOWN:
			this->personaje->moverAbajo();
			break;
		case SDLK_LEFT:
			this->personaje->moverIquierda();
			break;
		case SDLK_RIGHT:
			this->personaje->moverDerecha();
			break;
	}
}

void Nivel::teclaLiberada(SDL_keysym* keysym) {
	switch(keysym->sym) {
		case SDLK_UP:
			this->personaje->detenerArriba();
			break;
		case SDLK_DOWN:
			this->personaje->detenerAbajo();
			break;
		case SDLK_LEFT:
			this->personaje->detenerIquierda();
			break;
		case SDLK_RIGHT:
			this->personaje->detenerDerecha();
			break;
	}
}


