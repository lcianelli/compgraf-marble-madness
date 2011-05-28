#include "PantallaOpciones.h"

SlidebarGUI* draggedObject;


PantallaOpciones::PantallaOpciones(void)
{
	wireframe = 0;
	interpolado = 0;
	texturas = 0;
	aceptarBtn = 0;
	for (int i = 0; i < 4; i++) {
		dirluz[i] = 0;
	}
	velBar = 0;
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
	delete velBar;
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
		float luz[4];
		mouseDown = true;
		ObjetoGUI* objClick = this->menuOpciones->objetoClickeado(ev.x, s->h-ev.y);
		if (objClick == this->texturas) {
			this->texturas->onClick();
			Configuracion::inst()->setTexturas(this->texturas->isChecked());
		} else if (objClick == this->interpolado) {
			this->interpolado->onClick();
			Configuracion::inst()->setInterpolado(this->interpolado->isChecked());
		} else if (objClick == this->wireframe) {
			this->wireframe->onClick();
			Configuracion::inst()->setWireframe(this->wireframe->isChecked());
		} else if (objClick == this->dirluz[0]) {
			this->dirluz[0]->setChecked(true);
			this->dirluz[1]->setChecked(false);
			this->dirluz[2]->setChecked(false);
			this->dirluz[3]->setChecked(false);

			luz[0] = 1.f;
			luz[1] = 1.f;
			luz[2] = 1.f;
			luz[3] = 0.f;
			Configuracion::inst()->setDireccionLuz(0, luz);
			Configuracion::inst()->setCambiarLuz(true);

		} else if (objClick == this->dirluz[1]) {
			this->dirluz[1]->setChecked(true);
			this->dirluz[0]->setChecked(false);
			this->dirluz[2]->setChecked(false);
			this->dirluz[3]->setChecked(false);
			luz[0] = 1.f;
			luz[1] = 1.f;
			luz[2] = -1.f;
			luz[3] = 0.f;
			Configuracion::inst()->setDireccionLuz(0, luz);
			Configuracion::inst()->setCambiarLuz(true);

		} else if (objClick == this->dirluz[2]) {
			this->dirluz[2]->setChecked(true);
			this->dirluz[0]->setChecked(false);
			this->dirluz[1]->setChecked(false);
			this->dirluz[3]->setChecked(false);
			
			luz[0] = -1.f;
			luz[1] = 1.f;
			luz[2] = -1.f;
			luz[3] = 0.f;
			Configuracion::inst()->setDireccionLuz(0, luz);
			Configuracion::inst()->setCambiarLuz(true);
		} else if (objClick == this->dirluz[3]) {
			this->dirluz[3]->setChecked(true);
			this->dirluz[1]->setChecked(false);
			this->dirluz[2]->setChecked(false);
			this->dirluz[0]->setChecked(false);
			luz[0] = -1.f;
			luz[1] = 1.f;
			luz[2] = 1.f;
			luz[3] = 0.f;
			Configuracion::inst()->setDireccionLuz(0, luz);
			Configuracion::inst()->setCambiarLuz(true);
		} else if (objClick == this->menuOpciones->getBotonCiere()) {
			Juego::inst()->pausar();
		} else if (objClick == this->velBar) {
			mouseDown = true;
			draggedObject = dynamic_cast<SlidebarGUI*>(objClick);
		} else if (objClick == rBar) {
			mouseDown = true;
			draggedObject = dynamic_cast<SlidebarGUI*>(objClick);
		} else if (objClick == gBar) {
			mouseDown = true;
			draggedObject = dynamic_cast<SlidebarGUI*>(objClick);
		} else if (objClick == bBar) {
			mouseDown = true;
			draggedObject = dynamic_cast<SlidebarGUI*>(objClick);
		} else if (objClick == aceptarBtn) {
			Juego::inst()->pausar();
		}
		
	}
}

void PantallaOpciones::handleMouseMoved(const SDL_MouseMotionEvent &ev) {
	if (mouseDown && draggedObject != 0) {
		
		draggedObject->actualizar(ev.xrel);
		cout << "Actualize: " << draggedObject->Actual() << endl;
	}
}

void PantallaOpciones::handleMouseUp(const SDL_MouseButtonEvent &ev) {
	mouseDown = false;
	if (draggedObject != 0) {
		if (draggedObject == this->velBar) {
			Configuracion::inst()->setVelocidad(this->velBar->Actual());
		}
		if (draggedObject == this->rBar) {
			Configuracion::inst()->setR(0, this->rBar->Actual());
			Configuracion::inst()->setCambiarLuz(true);
		}
		if (draggedObject == this->gBar) {
			Configuracion::inst()->setG(0, this->gBar->Actual());
			Configuracion::inst()->setCambiarLuz(true);
		}
		if (draggedObject == this->bBar) {
			Configuracion::inst()->setB(0, this->bBar->Actual());
			Configuracion::inst()->setCambiarLuz(true);
		}
	}
	draggedObject = 0;
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
		int menuTexId = ManejadorTextura::inst()->cargar("imgs\\Opciones.png");
		this->menuOpciones = new MenuGUI(0, 0, s->w, s->h);
		this->menuOpciones->Color(Vector(1.f, 0.f, 1.f));
		this->menuOpciones->setPadre(NULL);
		this->menuOpciones->setImagen(menuTexId);
		wireframe = new CheckboxGUI(270, 416, 15, 15, false);
		wireframe->Color(Vector(0.f, 1.f, 0.f));
		this->menuOpciones->agegarHijo(wireframe);
		interpolado = new CheckboxGUI(270, 383 , 15, 15, false);
		interpolado->Color(Vector(0.f, 1.f, 0.f));
		this->menuOpciones->agegarHijo(interpolado);
		texturas = new CheckboxGUI(270,  350, 15, 15, false);
		texturas->Color(Vector(0.f, 1.f, 0.f));
		this->menuOpciones->agegarHijo(texturas);
		this->velBar = new SlidebarGUI(445, 382, 195, 20, 0.1f, 10.f, 1.0f); 
		this->velBar->Color(Vector(1.f, 0.f, 1.f));
		menuOpciones->agegarHijo(this->velBar);
		this->rBar = new SlidebarGUI(159, 244, 195, 20, 0.f, 1.f, 1.0f); 
		this->rBar->Color(Vector(1.f, 0.f, 1.f));
		menuOpciones->agegarHijo(this->rBar); 
		this->gBar = new SlidebarGUI(159, 215, 195, 20, 0.f, 1.f, 1.0f); 
		menuOpciones->agegarHijo(this->gBar); 
		this->bBar = new SlidebarGUI(159, 182, 195, 20, 0.f, 1.f, 1.0f); 
		menuOpciones->agegarHijo(this->bBar); 
		//direcciones de la luz
		dirluz[0] = new CheckboxGUI(472, 243, 18, 18, false);
		dirluz[0]->Color(Vector(0.f, 1.f, 0.f));
		this->menuOpciones->agegarHijo(dirluz[0]);

		dirluz[1] = new CheckboxGUI(472, 172, 18, 18, false);
		dirluz[1]->Color(Vector(0.f, 1.f, 0.f));
		this->menuOpciones->agegarHijo(dirluz[1]);
//--done
		dirluz[2] = new CheckboxGUI(600.f, 243.f, 18, 18, false);
		dirluz[2]->Color(Vector(0.f, 1.f, 0.f));
		this->menuOpciones->agegarHijo(dirluz[2]);

		dirluz[3] = new CheckboxGUI(600.f, 172.f, 18, 18, false);
		dirluz[3]->Color(Vector(0.f, 1.f, 0.f));
		this->menuOpciones->agegarHijo(dirluz[3]);
		
		dirluz[0]->setChecked(true);


		aceptarBtn = new BotonGUI(318, 110, 160, 35);
		aceptarBtn->Color(Vector(1.f, 1.f, 1.f));
		this->menuOpciones->agegarHijo(aceptarBtn);
	}
	
	this->ticksIni = SDL_GetTicks();
	this->ticksFin = this->ticksIni;
	this->loop = true;
	//texFondoId = ManejadorTextura::inst()->cargar("C:\\CompGraf\\Obligatorio1\\MarbleMadness\\frogatto-spritesheet1.png");
}

void PantallaOpciones::cambiarNivel() {

}