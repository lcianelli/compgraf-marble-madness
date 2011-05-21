#include "PantallaNivel.h"

#include "Vector.h"
#include "Rayo.h"
#include "Plano.h"
#include "Rectangulo.h"


GLfloat xspeed = 0, zspeed= 0;
const GLfloat XSPEED = 0.01f;
const GLfloat ZSPEED = 0.01f;

GLfloat xpos=0.f;
GLfloat zpos=0.f;
GLfloat ypos = 0.f;

GLfloat alphaz = 0.f;
GLfloat alphax = 0.f;

bool saltar = false;
const Uint32 T_SALTO = 500;//duracion del salto en ms
Uint32 tiempoSaltoActual = 0;
GLfloat Y_MAX = 1.f;
GLfloat  A = -6.f/((T_SALTO+T_SALTO/2)*(T_SALTO/2));
GLfloat B = -A*T_SALTO;

Vector aceleracion;
Vector velocidad;
Vector posicion;
Plano plano;
Rectangulo r;
float radio;
Vector ejes[3];

//funciones auxiliares
void dibujarEjes();
void dibujarVector(const Vector &_vect, const Vector &color);
void dibujarEsfera(const Vector &pos, float radio);

void dibujarEsfera(const Vector &pos, float _radio, const Vector &_color) {
	glPushMatrix();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

	
		glTranslatef(pos.X(), pos.Y(), pos.Z());
		
		glColor3f(_color.X(), _color.Y(), _color.Z());
	
		GLUquadric* sphereQuadric = gluNewQuadric();

		gluSphere(sphereQuadric, _radio, 50, 50);
	
		gluDeleteQuadric(sphereQuadric);
	glPopMatrix();
}


PantallaNivel::PantallaNivel(void)
{
	this->ticksIni = 0;
	this->ticksFin = 0;
	
	plano = Plano(Vector(0.f, 0.f,0.f), Vector(0.f,1.f,0.f));  
	r = Rectangulo(plano, Vector(0.f, 0.f, 1.f), 3.0f, 3.0f);
	ejes[0] = Vector(1.0f, 0.f, 0.f);
	ejes[1] = Vector(0.f, 1.f, 0.f);
	ejes[2] = Vector(0.f, 0.f, 1.f);
	velocidad = Vector(0.f, 0.f, 0.f);
	aceleracion = Vector(0.f, 0.f, 0.f);
	radio = 0.1f;
	posicion = Vector(0.3f, radio, 0.4f);

}

void PantallaNivel::cambiarNivel() {

}

void dibujarPlano(const Plano &pl, float w, float h, const Vector &_color) {

	Vector v1, v2, v3, v4;
	v1 = r.Posicion();
	v2= r.opuesto().unitario()*w + r.Posicion();
	v3 = (pl.Normal()*(v2-v1)).unitario()*h + v1;
	v4 = v3+(v2-v1);
	glPushMatrix();
	//glTranslatef(pl.Posicion().X(), pl.Posicion().Y(), pl.Posicion().Z());
	glColor3f(_color.X(), _color.Y(), _color.Z());
	glBegin(GL_QUADS);
		glVertex3f(v1.X(), v1.Y(), v1.Z());
		glVertex3f(v2.X(), v2.Y(), v2.Z());
		glVertex3f(v4.X(), v4.Y(), v4.Z());
		glVertex3f(v3.X(), v3.Y(), v3.Z());
		
		
	glEnd();

	glPopMatrix();
}


PantallaNivel::~PantallaNivel(void)
{
}


void PantallaNivel::dibujar() {
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	
	glEnable(GL_DEPTH_TEST);
	
	glTranslatef(0.f,0.f, -5.f);
	
	gluLookAt(xpos, 0.5f , zpos + 1.f, xpos, 0.f, zpos, 0.f, 1.f, 0.f); 
	dibujarEjes();
	dibujarPlano(plano, 3.f, 3.f, Vector(1.f, 1.f, 1.f));
	dibujarEsfera(posicion, radio, Vector(1.f, 0.f, 0.f));
	
	glFlush();
	SDL_GL_SwapBuffers();

}

void PantallaNivel::actualizar(int tiempo) {
	posicion = Vector(velocidad.X()*tiempo, velocidad.Y()*tiempo, velocidad.Z()*tiempo);

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
	
	this->ticksIni = SDL_GetTicks();
	this->ticksFin = this->ticksIni;
	this->loop = true;
}

void PantallaNivel::handleKeyDown(SDL_keysym* keysym) {
	switch (keysym->sym) {
	case SDLK_g:
		
		break;
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
		case SDLK_a:
			if (!saltar) {
				saltar = true;
				tiempoSaltoActual = 0;
			}
			break;
		case SDLK_SPACE:
			if (!saltar) {
				saltar = true;
				tiempoSaltoActual = 0;
			}
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

void dibujarEjes() {

	for (int i = 0; i < 3; i++) {
		dibujarVector(ejes[i], Vector((i == 0) ? 1.f : 0.f, (i==1) ? 1.f : 0.f, (i == 2) ? 1.f : 0.f));
	}
}

void dibujarVector(const Vector &_vect, const Vector &color) {
	glBegin(GL_LINES);
	glColor3f(color.X(), color.Y(), color.Z());
	glVertex3f(0.f, 0.f, 0.f);
	glVertex3f(_vect.X(), _vect.Y(), _vect.Z());
	glEnd();
}

