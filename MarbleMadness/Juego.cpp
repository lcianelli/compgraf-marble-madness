#include "Juego.h"
Juego* Juego::instancia = 0;

void quitSDLApp(int code);
void setupOpengl(int width, int height);


void quitSDLApp(int code) {
	SDL_Quit();
	exit(code);
}

Juego::Juego(void) {


}


Juego::~Juego(void) {
	quitSDLApp(0);
}

void Juego::cargarEstados() {

}

void Juego::setEstadoActual(EstadoVisual* estado) {

}

void Juego::inicializar(int w, int h) {
	this->w = w;
	this->h = h;
	//inicializamos el subsistema de video de SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());		
		quitSDLApp(-1);
	}
	const SDL_VideoInfo* info = SDL_GetVideoInfo();
	
	if (!info) {
		//Según dice la referencia de SDL, esto nunca debería pasar
		fprintf(stderr, "Failed to get video info: %s\n", SDL_GetError());
		quitSDLApp(-1);
	}
	Uint32 glFlags = SDL_OPENGL | SDL_HWSURFACE ;
	Uint8 bpp = info->vfmt->BitsPerPixel;
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	if ((this->pantalla = SDL_SetVideoMode(this->w, this->h, bpp, glFlags)) == 0) {
		fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
		quitSDLApp(1);
	}

	setupOpengl(this->w, this->h);
}

void Juego::iniciar() {
	//Como juego es estatico no preciso pasarlo al constructor.
	this->estadoActual = new PantallaNivel();
	this->estadoActual->inicializar();

	printf("Voy a correr\n");

	this->estadoActual->correr();
}


void setupOpengl(int width, int height) {
	float ratio = (float) width / (float) height;
	/*Culling*/
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);

	glClearColor(0.0f, 0.0f, 0.0f, 1.f);

	/*Preparamos marco de visión*/
	glViewport(0, 0, width, height);

	/*Cambiamos a la matriz de proyeccion y seteamos nuestro volumen de vista.*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45.0, ratio, 0.1f, -100.0f );
	
	
	
}

void Juego::avanzarNivel(){
	//this->estadoActual->cambiarNivel();
}

