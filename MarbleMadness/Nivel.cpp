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
	if(Configuracion::inst()->getWireframe())
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	else
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	if(Configuracion::inst()->getTexturas())
		glDisable(GL_TEXTURE_2D);
	else
		glEnable(GL_TEXTURE_2D);

	if(Configuracion::inst()->getInterpolado()==true)
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);
	if(Configuracion::inst()->getCambiarLuz())
	{
		//Deshabilito, cambio y vuelvo a habilitar
		glDisable( GL_LIGHTING );
		glDisable( GL_LIGHT0 );		
		glLightfv(GL_LIGHT0, GL_DIFFUSE, Configuracion::inst()->getColorLuz(0));
		glEnable( GL_LIGHTING );
		glEnable( GL_LIGHT0 );
	}

	dibujarObjDinamicos();

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
	
	actualizarFisica(tiempo);

	actualizarObjDinamicos(tiempo);
	
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
		case SDLK_F1:
			Configuracion::inst()->setWireframe(!Configuracion::inst()->getWireframe());
			break;
		case SDLK_F2:
			Configuracion::inst()->setInterpolado(!Configuracion::inst()->getInterpolado());
			break;
		case SDLK_F3:
			Configuracion::inst()->setTexturas(!Configuracion::inst()->getTexturas());
			break;
		case SDLK_F4:
			Configuracion::inst()->aumentarR(0);
			Configuracion::inst()->setCambiarLuz(true);
			break;
		case SDLK_F5:
			Configuracion::inst()->aumentarG(0);
			Configuracion::inst()->setCambiarLuz(true);
			break;
		case SDLK_F6:
			Configuracion::inst()->aumentarB(0);
			Configuracion::inst()->setCambiarLuz(true);
			break;
		case SDLK_F7:
			Configuracion::inst()->disminuirR(0);
			Configuracion::inst()->setCambiarLuz(true);
			break;
		case SDLK_F8:
			Configuracion::inst()->disminuirG(0);
			Configuracion::inst()->setCambiarLuz(true);
			break;
		case SDLK_F9:
			Configuracion::inst()->disminuirB(0);
			Configuracion::inst()->setCambiarLuz(true);
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

void Nivel::agregarObjetoDinamico(ObjetoJuego* obj){
	if (!obj->esEstatico())  {
		this->objsDinamicos.push_back(dynamic_cast<ObjetoDinamico*>(obj));
	}
}


void Nivel::dibujarObjDinamicos(){
	list<ObjetoDinamico*>::iterator itDin;
	for (itDin = this->objsDinamicos.begin(); itDin != this->objsDinamicos.end(); itDin++) {
		(*itDin)->dibujar();
	}
}

void Nivel::actualizarObjDinamicos(int tiempo){
	list<ObjetoDinamico*>::iterator itDin;
	for (itDin = this->objsDinamicos.begin(); itDin != this->objsDinamicos.end(); itDin++) {
		(*itDin)->actualizar(tiempo);
	}
}

void Nivel::actualizarFisica(int tiempo) {
	list<ObjetoDinamico*>::iterator it;
	for (it = objsDinamicos.begin(); it != objsDinamicos.end(); it++) {
		(*it)->actualizado = false;
	}
	for (it = objsDinamicos.begin(); it != objsDinamicos.end(); it++) {
		if (!(*it)->actualizado) {
			(*it)->actualizarFisica(tiempo);
		}
	}

}

