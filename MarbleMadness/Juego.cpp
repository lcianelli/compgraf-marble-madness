#include "Juego.h"

#include "Camara.h"

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
	string nombreEstado = string("juego");
	estados[nombreEstado] = new PantallaNivel();
	nombreEstado = string("pausa");
	estados[nombreEstado] = new PantallaPausa();
	nombreEstado = string("opciones");
	estados[nombreEstado] = new PantallaOpciones();
}

void Juego::setEstadoActual(EstadoVisual* estado) {
	if (this->estadoActual != 0) {
		this->estadoActual->detener();		
	}
	this->estadoActual = estado;
	this->estadoActual->inicializar();
	this->estadoActual->correr();
}

void Juego::setEstadoActual(const string &idEstado) {
	setEstadoActual(estados[idEstado]);
}


void Juego::inicializar(int w, int h) {
	this->w = w;
	this->h = h;
	cargarEstados();
	//inicializamos el subsistema de video de SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());		
		quitSDLApp(-1);
	}
	const SDL_VideoInfo* info = SDL_GetVideoInfo();
	
	if (!info) {
		//Seg�n dice la referencia de SDL, esto nunca deber�a pasar
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
	this->estadoActual = estados["juego"];
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

	/*Preparamos marco de visi�n*/
	glViewport(0, 0, width, height);

	/*Cambiamos a la matriz de proyeccion y seteamos nuestro volumen de vista.*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 45.0, ratio, 0.1f, -100.0f );
	
	Configuracion::inst()->inicializar();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLfloat* pos = Camara::inst()->getposicionCamara();
	GLfloat* pto = Camara::inst()->getpuntoVista();
	gluLookAt( pos[0], pos[1], pos[2], pto[0], pto[1], pto[2], 0.f, 1.f, 0.f); 	
	
}

void Juego::avanzarNivel(){
	//this->estadoActual->cambiarNivel();
}

EstadoVisual* Juego::getEstado(const string &idEstado) {
	return estados[idEstado];
}

EstadoVisual* Juego::getEstadoActual() {
	return this->estadoActual;
}

void Juego::pausar() {
	PantallaPausa* pPausa = dynamic_cast<PantallaPausa*>(getEstado("pausa"));
	PantallaNivel* pNivel = dynamic_cast<PantallaNivel*>(getEstado("juego"));
	pPausa->setNivel(pNivel->getNivel());
	pPausa->setHud(pNivel->getHud());
	this->setEstadoActual(pPausa);
}

void Juego::resumir() {
	PantallaNivel* pNivel = dynamic_cast<PantallaNivel*>(getEstado("juego"));
	this->setEstadoActual(pNivel);

}


void Juego::reiniciarNivel() {
	PantallaNivel* pNivel = dynamic_cast<PantallaNivel*>(getEstado("juego"));
	pNivel->setNivel(0);
	this->setEstadoActual(pNivel);
}

void Juego::salir() {
	//TODO: implementar salida del juego
}

void Juego::opciones() {
	PantallaOpciones* pOpciones = dynamic_cast<PantallaOpciones*>(getEstado("opciones"));
	PantallaNivel* pNivel = dynamic_cast<PantallaNivel*>(getEstado("juego"));
	pOpciones->setNivel(pNivel->getNivel());
	pOpciones->setHud(pNivel->getHud());
	this->setEstadoActual(pOpciones);
}
