#include "PantallaNivel.h"
#include "Camara.h"

float cnt1;
float cnt2;


PantallaNivel::PantallaNivel(void)
{
	this->ticksIni = 0;
	this->ticksFin = 0;
	this->loop= true;
	this->idNivel = 1;
	nivelActual = NULL;
	hud = NULL;
	
}


PantallaNivel::~PantallaNivel(void)
{

}


void PantallaNivel::dibujar() {

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glEnable(GL_DEPTH_TEST);

	//GLfloat lightPos[4] = {0.0, 5.8 ,0.0, 1.0};  ////posicion de la luz
	//GLfloat lightVector[3] = {0.0, -1.0 ,0.0};
	//////////
	//GLfloat luzAmbient[4] = {0.8,0.8,0.8,1.0};
	//GLfloat luzDiff[4] = {1.0, 1.0, 1.0,1.0};
	//GLfloat luzSpec[4] = {0.5, 0.5, 0.5,1.0};

 //   ///luces del modelo
	//glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION, lightPos);
	//glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,lightVector);
	//glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,60);
 //   glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbient);
 //   glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDiff);
 //   glLightfv(GL_LIGHT0, GL_SPECULAR, luzSpec);

	glEnable(GL_LIGHTING);
	float* val_ptr = new float[4];
	val_ptr[0]=0.0;
	val_ptr[1]=0.0;
	val_ptr[2]=-5.0;
	val_ptr[3]=1.0;
	glLightfv(GL_LIGHT1,GL_POSITION,val_ptr);

	float* val_color = new float[3];
	val_color[0]=1.0;
	val_color[1]=1.0;
	val_color[2]=1.0;

	glLightfv(GL_LIGHT1,GL_DIFFUSE,val_color);
	glLightfv(GL_LIGHT1,GL_SPECULAR,val_color);

	glEnable(GL_LIGHT1);

	// cambio isa 16/5/2011
	//glTranslatef(0.f,0.f, -10.f);
	
	//Ponemos la camara con la pelotita.
	//gluLookAt(xpos, 0.5f , zpos + 1.f, xpos, 0.f, zpos, 0.f, 1.f, 0.f); 

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
		glColor3ub(0, 0, 255);	
		float yaux = 0.f;
		glVertex3f(-2.f, -2.f, yaux);
		glVertex3f(2.f,-2.f, yaux);
	
		glVertex3f(2.f, 2.f, yaux);
		glVertex3f(-2.f, 2.f, yaux);
	glEnd();

	this->nivelActual->dibujar();
	this->hud->dibujarHud();

	//glFlush();
	SDL_GL_SwapBuffers();

}

void PantallaNivel::actualizar(int tiempo) {
	if (this->nivelActual != NULL) {
		
		this->nivelActual->actualizar(tiempo);
	}
	if (this->hud != NULL) {
		this->hud->actualizar(tiempo);
	}
}

void PantallaNivel::procesarEventos() {

	//printf("Estoy procesando eventos\n");


	ticksIni =  SDL_GetTicks();
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
			case SDL_KEYDOWN:
	printf("Estoy SDL_KEYDOWN\n");
				handleKeyDown(&ev.key.keysym);
				this->nivelActual->teclaPresionada(&ev.key.keysym);
				break;
			case SDL_KEYUP:
	printf("Estoy SDL_KEYUP\n");
				this->nivelActual->teclaLiberada(&ev.key.keysym);
				break;
			case SDL_MOUSEBUTTONDOWN:
	printf("Estoy SDL_MOUSEBUTTONDOWN\n");
				Camara::inst()->manejadorComienzoMovimientoCamara(&ev.button);
				break;
			case SDL_MOUSEMOTION:
	printf("Estoy SDL_MOUSEMOTION\n");
				Camara::inst()->manejadorMovimientoCamara(&ev.motion);
				break;
			case SDL_MOUSEBUTTONUP:
	printf("Estoy SDL_MOUSEBUTTONUP\n");
				Camara::inst()->manejadorFinMovimientoCamara(&ev.button);
				break;			
			case SDL_QUIT:
				this->detener();
				delete Juego::inst();
				break;
		}
	}	
}

void PantallaNivel::inicializar() {
	if (this->nivelActual == NULL) {
		
		this->nivelActual=new Nivel(this->idNivel);
		this->hud = new HUD(1000, 1000*10*1, this->idNivel);
	}
	
	//this->nivelActual->iniciar();
	this->ticksIni = SDL_GetTicks();
	this->ticksFin = this->ticksIni;
	this->loop = true;
}

void PantallaNivel::handleKeyDown(SDL_keysym* keysym) {
	switch (keysym->sym) {
		case SDLK_p:
			Juego::inst()->pausar();
			//this->pausa=!this->pausa;
			break;
		case SDLK_q:
			this->detener();
			delete Juego::inst();
			break;
		case SDLK_g:
			Ambiente::aplicarGravedad(!Ambiente::aplicarG);
			break;
		case SDLK_ESCAPE:
			this->detener();
			delete Juego::inst();
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
		default:break;
	}
}


void PantallaNivel::cambiarNivel()
{
	this->idNivel+=1;
	delete this->nivelActual;
	this->nivelActual=new Nivel(this->idNivel);
}

Nivel* PantallaNivel::getNivel() {
	return this->nivelActual;
}

HUD* PantallaNivel::getHud() {
	return this->hud;
}

void PantallaNivel::resumir() {
	this->ticksIni = SDL_GetTicks();
	this->ticksFin = this->ticksIni;
	this->loop = true;
}

void PantallaNivel::setNivel(Nivel* niv) {
	this->nivelActual = niv;
}


