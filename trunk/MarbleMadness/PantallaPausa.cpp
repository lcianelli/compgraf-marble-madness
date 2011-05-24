#include "PantallaPausa.h"

int texFondoId;

PantallaPausa::PantallaPausa(void)
{
	this->nivelActual = 0;
	this->hud = 0;
}

PantallaPausa::~PantallaPausa(void)
{
}

void PantallaPausa::dibujar() {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
	if (nivelActual!= 0) {
		//nivelActual->dibujar();
	}
	if (hud != 0) {
		hud->dibujarHud();
	}

	//una vez dibujado el hud, me dibujo yo :P

	//deberia tambien dibujar el menu de pausa... cuando lo tenga :)
	
	/*glBindTexture(GL_TEXTURE_2D, texFondoId);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);	
	glEnable(GL_TEXTURE);	
	
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 0.f, -3.f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.f, -3.f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.f, 1.f, -3.f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.f, 0.f, -3.f);	

	SDL_GL_SwapBuffers();*/
}

void PantallaPausa::actualizar(int tiempo) {
	//?? por ahora nada
}

void PantallaPausa::procesarEventos() {
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
			case SDL_KEYDOWN:	
//				handleKeyDown(&ev.key.keysym);
				
				break;
			case SDL_KEYUP:
				
				break;
			case SDL_MOUSEBUTTONDOWN:
				//Camara::inst()->manejadorComienzoMovimientoCamara(&ev.button);
				break;
			case SDL_MOUSEMOTION:
				//Camara::inst()->manejadorMovimientoCamara(&ev.motion);
				break;
			case SDL_MOUSEBUTTONUP:
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

	this->ticksIni = SDL_GetTicks();
	this->ticksFin = this->ticksIni;
	this->loop = true;
	//texFondoId = ManejadorTextura::inst()->cargar("imgs\\Opciones.png");
}


void PantallaPausa::cambiarNivel() {
	//no hace nada, porque aca no se cambia de nivel en esta vista
}
