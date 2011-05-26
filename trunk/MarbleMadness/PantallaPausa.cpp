#include "PantallaPausa.h"

int texFondoId;


PantallaPausa::PantallaPausa(void)
{
	this->nivelActual = 0;
	this->hud = 0;
	this->resumeBtn = 0;
	this->opcionesBtn = 0;
	this->salirBtn = 0;
	this->reiniciarBtn = 0;
	this->menuPausa = 0;
}

PantallaPausa::~PantallaPausa(void)
{
}

void PantallaPausa::dibujar() {
	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_ACCUM_BUFFER_BIT );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

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
			glTranslatef(this->menuPausa->X(), this->menuPausa->Y(), 0.f);
			this->menuPausa->dibujar();			
			glTranslatef(-this->menuPausa->X(), -this->menuPausa->Y(), 0.f);			
		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_LIGHTING);	//glDisable(GL_BLEND);
	SDL_GL_SwapBuffers();
}

void PantallaPausa::actualizar(int tiempo) {
	//?? por ahora nada
}

void PantallaPausa::procesarEventos() {
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

void PantallaPausa::inicializar() {
	s = SDL_GetVideoSurface();

	if (this->resumeBtn == 0) {
		this->menuPausa = new MenuGUI(s->w/2-200, s->h/2-200, 400, 400);
		this->menuPausa->Color(Vector(0.f, 1.f, 1.f));
		this->menuPausa->setPadre(NULL);
		texFondoId = ManejadorTextura::inst()->cargar("imgs\\menupausa.png");
		this->menuPausa->setImagen(texFondoId);

		this->resumeBtn = new BotonGUI(50, 150, 50, 20);
		this->menuPausa->agegarHijo(this->resumeBtn);
		this->resumeBtn->Color(Vector(1.f, 0.f, 0.f));
		this->opcionesBtn = new BotonGUI(50, 120, 50, 20);
		this->menuPausa->agegarHijo(this->opcionesBtn);
		this->opcionesBtn->Color(Vector(0.f, 1.f, 0.f));
		this->salirBtn = new BotonGUI(50, 90, 50, 20);
		this->menuPausa->agegarHijo(this->salirBtn);
		this->salirBtn->Color(Vector(0.f, 0.f, 1.f));
		this->reiniciarBtn = new BotonGUI(50, 60, 50, 20);
		this->menuPausa->agegarHijo(this->reiniciarBtn);
		this->reiniciarBtn->Color(Vector(1.f, 1.f, 1.f));
	}
	
	this->ticksIni = SDL_GetTicks();
	this->ticksFin = this->ticksIni;
	this->loop = true;
	
	//TextureManager::Inst()->LoadTexture("menupausa.png", texFondoId);
}


void PantallaPausa::cambiarNivel() {
	//no hace nada, porque aca no se cambia de nivel en esta vista
}

void PantallaPausa::handleKeyDown(SDL_keysym* keysym) {
	switch (keysym->sym) {
	case SDLK_q:
		this->detener();
		delete Juego::inst();
		break;
	case SDLK_p:
		Juego::inst()->resumir();
		break;
	default:
		break;
	}
}

void PantallaPausa::handleMouseDown(const SDL_MouseButtonEvent &ev) {

	if (ev.button == SDL_BUTTON_LEFT) {
		mouseDown = true;
		ObjetoGUI* objClick = this->menuPausa->objetoClickeado(ev.x, s->h-ev.y);
		
		if (this->resumeBtn == objClick) {			
			Juego::inst()->resumir();
		} else if (this->opcionesBtn == objClick) {
			Juego::inst()->opciones();
		} else if (this->salirBtn == objClick) {
			Juego::inst()->salir();
		} else if (this->reiniciarBtn == objClick) {
			Juego::inst()->reiniciarNivel();
		} else if (this->menuPausa->getBotonCiere() == objClick) {
			Juego::inst()->resumir();
		}
	}
}

void PantallaPausa::handleMouseMoved(const SDL_MouseMotionEvent &ev) {
	/*if (mouseDown) {
		cout << "mouse Dragged "<< ev.xrel;
	}*/
}

void PantallaPausa::handleMouseUp(const SDL_MouseButtonEvent &ev) {
	mouseDown = false;
}

void PantallaPausa::resumir() {
	s = SDL_GetVideoSurface();
	this->ticksIni = SDL_GetTicks();
	this->ticksFin = this->ticksIni;
	this->loop = true;
}