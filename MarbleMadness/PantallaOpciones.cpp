#include "PantallaOpciones.h"



PantallaOpciones::PantallaOpciones(void)
{
	wireframe = 0;
	interpolado = 0;
	texturas = 0;
	aceptarBtn = 0;
	for (int i = 0; i < 4; i++) {
		dirluz[i] = 0;
	}
}


PantallaOpciones::~PantallaOpciones(void)
{
	delete wireframe;
	delete interpolado;
	delete texturas;
	delete aceptarBtn;
	for (int i = 0; i < 4; i++) {
		delete dirluz[i];
	}
}


void PantallaOpciones::dibujar() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	if (nivelActual!= 0) {
		nivelActual->dibujar();
	}
	if (hud != 0) {
		hud->dibujarHud();
	}

	//una vez dibujado el hud, me dibujo yo :P

	//deberia tambien dibujar el menu de pausa... cuando lo tenga :)
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glDisable(GL_LIGHTING);
		glLoadIdentity();

		
		glOrtho(0.f, s->w, 0.f, s->h, -1.f, 1.f);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glViewport(0, 0, (GLsizei) s->w, (GLsizei) s->h);
			glTranslatef(this->menuOpciones->X(), this->menuOpciones->Y(), 0.f);
			this->menuOpciones->dibujar();			
			glTranslatef(-this->menuOpciones->X(), -this->menuOpciones->Y(), 0.f);			
		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	SDL_GL_SwapBuffers();
}

void PantallaOpciones::actualizar(int tiempo) {
	//?? por ahora nada
}

void PantallaOpciones::procesarEventos() {
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
			case SDL_KEYDOWN:	

				handleKeyDown(&ev.key.keysym);
				break;
			case SDL_MOUSEBUTTONDOWN:				
				this->handleMouseDown(ev.button);
				//Camara::inst()->manejadorComienzoMovimientoCamara(&ev.button);
				break;
			case SDL_MOUSEMOTION:

				this->handleMouseMoved(ev.motion);
				//Camara::inst()->manejadorMovimientoCamara(&ev.motion);
				break;
			case SDL_MOUSEBUTTONUP:
				this->handleMouseUp(ev.button);
				//Camara::inst()->manejadorFinMovimientoCamara(&ev.button);
				break;			
			case SDL_QUIT:
				this->detener();
				delete Juego::inst();
				break;
		}
	}	
}

void PantallaOpciones::handleKeyDown(SDL_keysym* keysym) {
	switch (keysym->sym) {
	case SDLK_q:
		this->detener();
		delete Juego::inst();
		break;
	case SDLK_p:
		//Juego::inst()->resumir();
		break;
	default:
		break;
	}
}

void PantallaOpciones::handleMouseDown(const SDL_MouseButtonEvent &ev) {

	if (ev.button == SDL_BUTTON_LEFT) {
		mouseDown = true;
		ObjetoGUI* objClick = this->menuOpciones->objetoClickeado(ev.x, s->h-ev.y);
		if (objClick == this->texturas) {
			this->texturas->onClick();
		} else if (objClick == this->interpolado) {
			this->interpolado->onClick();
		} else if (objClick == this->wireframe) {
			this->wireframe->onClick();
		} else if (objClick == this->dirluz[0]) {
			this->dirluz[0]->setChecked(true);
			this->dirluz[1]->setChecked(false);
			this->dirluz[2]->setChecked(false);
			this->dirluz[3]->setChecked(false);
		} else if (objClick == this->dirluz[1]) {
			this->dirluz[1]->setChecked(true);
			this->dirluz[0]->setChecked(false);
			this->dirluz[2]->setChecked(false);
			this->dirluz[3]->setChecked(false);
		} else if (objClick == this->dirluz[2]) {
			this->dirluz[2]->setChecked(true);
			this->dirluz[0]->setChecked(false);
			this->dirluz[1]->setChecked(false);
			this->dirluz[3]->setChecked(false);
		} else if (objClick == this->dirluz[3]) {
			this->dirluz[3]->setChecked(true);
			this->dirluz[1]->setChecked(false);
			this->dirluz[2]->setChecked(false);
			this->dirluz[0]->setChecked(false);
		}
		
	}
}

void PantallaOpciones::handleMouseMoved(const SDL_MouseMotionEvent &ev) {
	/*if (mouseDown) {
		cout << "mouse Dragged "<< ev.xrel;
	}*/
}

void PantallaOpciones::handleMouseUp(const SDL_MouseButtonEvent &ev) {
	mouseDown = false;
}

void PantallaOpciones::resumir() {
	s = SDL_GetVideoSurface();
	this->ticksIni = SDL_GetTicks();
	this->ticksFin = this->ticksIni;
	this->loop = true;
}

void PantallaOpciones::inicializar() {
	s = SDL_GetVideoSurface();
	mouseDown = false;
	if (this->wireframe == 0) {
		this->menuOpciones = new MenuGUI(0, 0, s->w, s->h);
		this->menuOpciones->Color(Vector(1.f, 0.f, 1.f));
		this->menuOpciones->setPadre(NULL);
		wireframe = new CheckboxGUI(10, (s->h*3)/4, 10, 10, false);
		wireframe->Color(Vector(0.f, 1.f, 0.f));
		this->menuOpciones->agegarHijo(wireframe);
		interpolado = new CheckboxGUI(10, (s->h*3)/4 - 20, 10, 10, false);
		interpolado->Color(Vector(0.f, 1.f, 0.f));
		this->menuOpciones->agegarHijo(interpolado);
		texturas = new CheckboxGUI(10,  (s->h*3)/4 - 40, 10, 10, false);
		texturas->Color(Vector(0.f, 1.f, 0.f));
		this->menuOpciones->agegarHijo(texturas);

		for (int i = 0; i < 4; i++) {
			dirluz[i] = new CheckboxGUI((s->w*3)/4 + (i%2)*35, (i < 2) ? s->h/4+30 : s->h/4, 15, 15, false);
			dirluz[i]->Color(Vector(0.f, 1.f, 0.f));
			this->menuOpciones->agegarHijo(dirluz[i]);
		}
		dirluz[0]->setChecked(true);
	}
	
	this->ticksIni = SDL_GetTicks();
	this->ticksFin = this->ticksIni;
	this->loop = true;
	//texFondoId = ManejadorTextura::inst()->cargar("C:\\CompGraf\\Obligatorio1\\MarbleMadness\\frogatto-spritesheet1.png");
}

void PantallaOpciones::cambiarNivel() {

}