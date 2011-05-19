#include "PantallaNivel.h"

#include "Vector.h"
#include "Rayo.h"
#include "Plano.h"
#include "Rectangulo.h"
#include "Matriz.h"

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

float modVelocidad;

Vector aceleracion;
Vector velocidad;
Vector posicion;
Plano plano;
Rectangulo r;
float radio;
Vector ejes[3];
Vector normalActual;
Vector vectorGiro;
Vector interseccion;

float anguloGiro;
const float modAceleracion = 0.00002f;
Matriz mBola;

const float MAX_VEL = 0.01f;


//funciones auxiliares
void dibujarEjes();
void dibujarVector(const Vector &_vect, const Vector &color);
void dibujarEsfera(const Vector &pos, float _radio);
float angulo( Rectangulo &rect, const Matriz &sistema, Vector &vGiro);

bool print = false;

void dibujarEsfera(const Vector &pos, float _radio, const Vector &_color) {
	glPushMatrix();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

		glRotatef(-anguloGiro, vectorGiro.X(), vectorGiro.Y(), vectorGiro.Z() );	
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
	
	plano = Plano(Vector(0.f, 0.f,0.f), Vector(1.f,1.f,0.f).unitario());  //plano horizontal
	r = Rectangulo(plano, Vector(0.f, 0.f, 1.f), 3.0f, 3.0f); //rectangulo horizontal 3x3
	ejes[0] = Vector(1.0f, 0.f, 0.f); //x
	ejes[1] = Vector(0.f, 1.f, 0.f); //y
	ejes[2] = Vector(0.f, 0.f, 1.f); //z
	velocidad = Vector(0.f, 0.f, 0.f); //vel pelota
	aceleracion = Vector(0.f, 0.f, 0.f); //ac. pelota
	radio = 0.1f; //radio pelota
	posicion = Vector(2.3f, radio, 0.4f); //posicion pelota
	mBola = Matriz();//creamos matriz identidad
	normalActual = Vector(0.f, 1.f, 0.f);
	float angl = angulo(r, mBola, vectorGiro);
	anguloGiro = RadAGrados(angl);	
	normalActual = r.Normal();
	modVelocidad = 0.000f;
}

//calcula el angulo que forma el rectangulo rect con el plano horizontal del sistema dado 
float angulo( Rectangulo &rect, const Matriz &sistema, Vector &vGiro) {
	Rectangulo tempRect(sistema*rect.Posicion(), sistema*rect.Normal(), sistema*rect.P2(), rect.W(), rect.H()); 
	vGiro;
	if (tempRect.P1().Y() == tempRect.P2().Y()) {
		if (tempRect.P1().Y() <= tempRect.P3().Y()) {
			vGiro = tempRect.P2()-tempRect.P1();
		} else {
			vGiro = tempRect.P4() - tempRect.P3();
		}
	} else {
		if (tempRect.P1().Y() <= tempRect.P2().Y()) {
			vGiro = tempRect.P1()-tempRect.P3();
		} else {
			vGiro = tempRect.P2() - tempRect.P4();
		}
	}
	 
	return acos(tempRect.Normal().escalar(normalActual));

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
	dibujarEsfera(posicion, radio, Vector(1.f, 0.f, 0.f));
	dibujarPlano(plano, 3.f, 3.f, Vector(1.f, 1.f, 1.f));
	glBegin(GL_POINTS);
	glColor3ub(255, 0, 0);

	glVertex3f(interseccion.X(), interseccion.Y(), interseccion.Z());
	glEnd();
	
	glFlush();
	SDL_GL_SwapBuffers();

}

void PantallaNivel::actualizar(int tiempo) {

	if (print) {
		cout << "posicion: " << posicion.X() << "," << posicion.Y() << "," << posicion.Z() << "; velocidad (" << modVelocidad << ") : " << velocidad.X() << "," << velocidad.Y() << "," << velocidad.Z() << ";" << endl;
	}
	

	velocidad = velocidad*modVelocidad;
	modVelocidad = velocidad.norma();
	Vector desplazamiento = Vector(aceleracion*modAceleracion*tiempo*tiempo*(1.f/2.f) + velocidad*tiempo);
	float distInt;
	Vector normal;
	Rectangulo r2 = Rectangulo(Plano(Vector(0.f, 0.f, 0.f), Vector(0.f, 1.f, 0.f)), Vector(0.f, 0.f, 1.f), r.W(), r.H());
	if (r2.probarInterseccion(Rayo(posicion, -r2.Normal()), distInt, normal, interseccion) > 0) {
		//velocidad = -velocidad;
		posicion += desplazamiento;
	} 
	
	velocidad += aceleracion*modAceleracion*tiempo;	
	modVelocidad = velocidad.norma();
	velocidad = velocidad.unitario();
	if (modVelocidad > MAX_VEL) {
		aceleracion = Vector(0.f, 0.f, 0.f);
		modVelocidad = MAX_VEL;
	}
	

	

}

void PantallaNivel::procesarEventos() {
	ticksIni =  SDL_GetTicks();
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
			case SDL_KEYDOWN:
				print = true;
				handleKeyDown(&ev.key.keysym);
				
				break;
			case SDL_KEYUP:
				print = false;
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
			if (modVelocidad >= MAX_VEL) {
				velocidad = Vector(-1.f, velocidad.Y(), velocidad.Z()).unitario();
			} else {
				aceleracion = Vector(-1.f, aceleracion.Y(), aceleracion.Z()).unitario();
			}
			break;
		case SDLK_RIGHT:
			if (modVelocidad >= MAX_VEL) {
				velocidad = Vector(1.f, velocidad.Y(), velocidad.Z()).unitario();
			} else {
				aceleracion = Vector(1.f, aceleracion.Y(), aceleracion.Z()).unitario();
			}
			break;
		case SDLK_UP:
			if (modVelocidad >= MAX_VEL) {
				velocidad = Vector(velocidad.X(), velocidad.Y(), -1.f).unitario();
			} else {
				aceleracion = Vector(aceleracion.X(), aceleracion.Y(), -1.f).unitario();
			}
			break;
		case SDLK_DOWN:
			if (modVelocidad >= MAX_VEL) {
				velocidad = Vector(velocidad.X(), velocidad.Y(), 1.f).unitario();
			} else {
				aceleracion = Vector(aceleracion.X(), aceleracion.Y(), 1.f).unitario();
			}
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
			if (velocidad.X() < 0.f) {
				velocidad = Vector(0.f, velocidad.Y(), velocidad.Z()).unitario();
				
			}
			if (aceleracion.X() < 0.f) {
				aceleracion = Vector(0.f, aceleracion.Y(), aceleracion.Z()).unitario();
			}
			break;
		case SDLK_RIGHT:
			if (velocidad.X() > 0.f) {
				velocidad = Vector(0.f, velocidad.Y(), velocidad.Z());
			}
			if (aceleracion.X() > 0.f) {
				aceleracion = Vector(0.f, aceleracion.Y(), aceleracion.Z());
			}
			break;
		case SDLK_UP:
			if (velocidad.Z() < 0.f) {
				velocidad = Vector(velocidad.X(), velocidad.Y(), 0.f);
			}			
			if (aceleracion.Z() < 0.f) {
				aceleracion = Vector(aceleracion.X(), aceleracion.Y(), 0.f);
			}
			break;
		case SDLK_DOWN:
			if (velocidad.Z() > 0.f) {
				velocidad = Vector(velocidad.X(), velocidad.Y(), 0.f);
			}
			if (aceleracion.Z() > 0.f) {
				aceleracion = Vector(aceleracion.X(), aceleracion.Y(), 0.f);
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

