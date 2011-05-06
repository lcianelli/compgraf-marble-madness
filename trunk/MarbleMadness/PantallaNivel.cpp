#include "PantallaNivel.h"


Uint32 ticksIni = 0, ticksFin = 0;

GLfloat xspeed = 0, zspeed= 0;
const GLfloat XSPEED = 0.01;
const GLfloat ZSPEED = 0.01;

GLfloat xpos=0.f;
GLfloat zpos=0.f;

GLfloat alphaz = 0.f;
GLfloat alphax = 0.f;

void updateAlpha() {	
	alphaz += (ticksIni - ticksFin) * xspeed * 20;
	alphax += (ticksIni - ticksFin) * zspeed * 100;
}


PantallaNivel::PantallaNivel(void)
{
}


PantallaNivel::~PantallaNivel(void)
{
}


void PantallaNivel::dibujar() {

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	
	
	glTranslatef(0.f,0.f, -10.f);
	
	//Ponemos la camara con la pelotita.
	gluLookAt(xpos, 1.f , zpos + 1.f, xpos, 0.f, zpos, 0.f, 1.f, 0.f); 

	glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);
	glBegin(GL_QUADS);
	glColor3ub(0, 0, 255);	
	int yaux = 0.f;
	glVertex3f(-2.f, -2.f, yaux);
	glVertex3f(2.f,-2.f, yaux);
	
	glVertex3f(2.f, 2.f, yaux);
	glVertex3f(-2.f, 2.f, yaux);
	glEnd();


	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

	glPushMatrix();
		glTranslatef(xpos,0.f,zpos);

		glRotatef(alphax,1.f,0.f,0.f);
		glRotatef(alphaz,0.f,0.f,1.0);

		glColor3ub(255, 0, 0);
	
		GLUquadric* sphereQuadric = gluNewQuadric();

		gluSphere(sphereQuadric, 1.0, 50, 50);
	
	glPopMatrix();

	gluDeleteQuadric(sphereQuadric);
	glFlush();
	SDL_GL_SwapBuffers();

}

void PantallaNivel::actualizar() {
	
	xpos += (ticksIni - ticksFin)*xspeed;
	zpos += (ticksIni - ticksFin)*zspeed;
	updateAlpha();
	ticksFin = ticksIni;
}

void PantallaNivel::procesarEventos() {
	ticksIni =  SDL_GetTicks();
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
			case SDL_KEYDOWN:
				handleKeyDown(&ev.key.keysym);
				break;
			case SDL_KEYUP:
				handleKeyUp(&ev.key.keysym);
				break;
			case SDL_QUIT:
				this->detener();
				delete Juego::inst();
				break;
		}
	}	
}

void PantallaNivel::inicializar() {
	this->loop = true;
}

void PantallaNivel::handleKeyDown(SDL_keysym* keysym) {
	switch (keysym->sym) {
		case SDLK_ESCAPE:
			this->detener();
			delete Juego::inst();
			break;
		case SDLK_LEFT:
			xspeed = -XSPEED;
			break;
		case SDLK_RIGHT:
			xspeed = XSPEED;
			break;
		case SDLK_UP:
			zspeed = -ZSPEED;
			break;
		case SDLK_DOWN:
			zspeed = ZSPEED;
			break;
		default:break;
	}
}

void PantallaNivel::handleKeyUp(SDL_keysym* keysym) {


	switch (keysym->sym) {
			case SDLK_LEFT:
			if (xspeed < 0.f) {
				xspeed = 0.f;
			}
			break;
		case SDLK_RIGHT:
			if (xspeed > 0.f) {
				xspeed = 0.f;
			}
			break;
		case SDLK_UP:
			if (zspeed < 0.f) {
				zspeed = 0.f;
			}			
			break;
		case SDLK_DOWN:
			if (zspeed > 0.f) {
				zspeed = 0.f;
			}			
			break;
		default:break;
	}

}