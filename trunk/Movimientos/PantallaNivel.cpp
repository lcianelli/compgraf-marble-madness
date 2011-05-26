#include "PantallaNivel.h"

#include "Vector.h"
#include "Rayo.h"
#include "Plano.h"
#include "Rectangulo.h"
#include "Matriz.h"

typedef struct bola_t {
	Vector ac;
	Vector vel;
	Vector centro;
	float radio;
	Plano* p;
};
/*bool saltar = false;
const Uint32 T_SALTO = 500;//duracion del salto en ms
Uint32 tiempoSaltoActual = 0;
GLfloat Y_MAX = 1.f;
GLfloat  A = -6.f/((T_SALTO+T_SALTO/2)*(T_SALTO/2));
GLfloat B = -A*T_SALTO;*/

bola_t bola;


Vector ejes[3];
Plano plano;
Vector acel(0.00001f, 0.f, 0.f);
float maxvel = 0.02f;

//funciones auxiliares
void dibujarEjes();
void dibujarVector(const Vector &_vect, const Vector &color);
void dibujarEsfera(const Vector &pos, float radio);

void dibujarEsfera(const Vector &pos, float _radio, const Vector &_color) {
	Plano XZ = Plano(Vector(0.f, 0.f, 0.f), Vector(0.f, 1.f, 0.f).unitario());
	float cosXZ = abs(bola.p->Normal().escalar(XZ.Normal()));
	float anguloXZ = RadAGrados(acos(cosXZ));
	Vector vecRotXZ = bola.p->Normal() * XZ.Normal();
	Plano XY = Plano(Vector(0.f, 0.f, 0.f), Vector(0.f, 0.f, 1.f).unitario());
	float cosXY = abs(bola.p->Normal().escalar(XY.Normal()));
	float anguloXY = RadAGrados(acos(cosXY));
	Vector vecRotXY = bola.p->Normal() * XY.Normal();
	Plano YZ = Plano(Vector(0.f, 0.f, 0.f), Vector(1.f, 0.f, 0.f).unitario());
	float cosYZ = abs(bola.p->Normal().escalar(YZ.Normal()));
	float anguloYZ = RadAGrados(acos(cosYZ));
	Vector vecRotYZ = bola.p->Normal() * YZ.Normal();


	glPushMatrix();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
	glRotatef(anguloXZ, vecRotXZ.X(), vecRotXZ.Y(), vecRotXZ.Z());	
	glRotatef(anguloXY, vecRotXY.X(), vecRotXY.Y(), vecRotXY.Z());
	glRotatef(anguloYZ, vecRotYZ.X(), vecRotYZ.Y(), vecRotYZ.Z());
	
	glTranslatef(bola.centro.X(), bola.centro.Y(), bola.centro.Z());
	
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
	
	plano = Plano(Vector(1.f, 0.f,0.f), Vector(1.f, -1.f, 0.f));  
	//r = Rectangulo(plano, Vector(0.f, 0.f, 1.f), 3.0f, 3.0f);
	ejes[0] = Vector(1.0f, 0.f, 0.f);
	ejes[1] = Vector(0.f, 1.f, 0.f);
	ejes[2] = Vector(0.f, 0.f, 1.f);
	bola.vel = Vector(0.f, 0.f, 0.f);
	bola.ac = Vector(0.00001f, 0.f, 0.f);
	bola.radio = 0.1f;
	bola.centro = Vector(0.3f, bola.radio, 0.4f);
	bola.p = &plano;

}

void PantallaNivel::cambiarNivel() {

}

void dibujarPlano(const Plano &pl, float w, float h, const Vector &_color) {
	Plano XZ = Plano(Vector(0.f, 0.f, 0.f), Vector(0.f, 1.f, 0.f).unitario());
	float cosXZ = abs(bola.p->Normal().escalar(XZ.Normal()));
	float anguloXZ = RadAGrados(acos(cosXZ));
	Vector vecRotXZ = bola.p->Normal() * XZ.Normal();
	Plano XY = Plano(Vector(0.f, 0.f, 0.f), Vector(0.f, 0.f, 1.f).unitario());
	float cosXY = abs(bola.p->Normal().escalar(XY.Normal()));
	float anguloXY = RadAGrados(acos(cosXY));
	Vector vecRotXY = bola.p->Normal() * XY.Normal();
	Plano YZ = Plano(Vector(0.f, 0.f, 0.f), Vector(1.f, 0.f, 0.f).unitario());
	float cosYZ = abs(bola.p->Normal().escalar(YZ.Normal()));
	float anguloYZ = RadAGrados(acos(cosYZ));
	Vector vecRotYZ = bola.p->Normal() * YZ.Normal();
	
	glPushMatrix();

	

	glTranslatef(pl.Posicion().X(), pl.Posicion().Y(), pl.Posicion().Z());
	glRotatef(anguloXZ, vecRotXZ.X(), vecRotXZ.Y(), vecRotXZ.Z());	
	glRotatef(anguloXY, vecRotXY.X(), vecRotXY.Y(), vecRotXY.Z());
	glRotatef(anguloYZ, vecRotYZ.X(), vecRotYZ.Y(), vecRotYZ.Z());
	glTranslatef(-pl.Posicion().X(), -pl.Posicion().Y(), -pl.Posicion().Z());
	dibujarEjes();
	glColor3f(_color.X(), _color.Y(), _color.Z());
	glBegin(GL_QUADS);
	glVertex3f(-w/2, 0.f, -h/2);
		glVertex3f(w/2, 0.f, -h/2);
		glVertex3f(w/2, 0.f, h/2);
		glVertex3f(-w/2, 0.f, h/2);
		
		
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
	
//	gluLookAt(xpos, 0.5f , zpos + 1.f, xpos, 0.f, zpos, 0.f, 1.f, 0.f); 
	
	dibujarPlano(plano, 4.f, 3.f, Vector(1.f, 1.f, 1.f));
	dibujarEsfera(bola.centro, bola.radio, Vector(1.f, 0.f, 0.f));
	
	glFlush();
	SDL_GL_SwapBuffers();

}

void PantallaNivel::actualizar(int tiempo) {
	if (bola.vel.norma() >= maxvel) {
		bola.ac = Vector(0.f, 0.f, 0.f);
		bola.vel.unitario();
		bola.vel = bola.vel * maxvel;
	} else {
		bola.ac = acel;
	}
	Vector pNormal;
	float dist;
	Rayo r(bola.centro, Vector(bola.vel).unitario());
	float tiempoF = tiempo;
	float dT = tiempoF;
	float tm;
	while (dT > CERO) {
		if (plano.probarInterseccion(r, dist, pNormal) > 0) {
			
			tm = (dist-bola.radio)/bola.vel.norma();
			//cout << dist << ", tChoque: " << tm << ", tiempo act: " << dT << endl;
			if (tm >= dT) {
				bola.centro += bola.ac*((dT*dT)/2.f) + bola.vel*dT;
				bola.vel += bola.ac * dT;
				//bola.centro += bola.vel*dT; //no choca aun
			} else {
				bola.centro += bola.ac*((tm*tm)/2.f) + bola.vel*tm;
				bola.vel += bola.ac * tm;
				float rt2=bola.vel.norma();
				bola.vel.unitario();						// Normalize It
				Vector normal = Vector(plano.Normal());
				// Compute Reflection
				bola.vel =Vector::unitario( (normal*(2*normal.escalar(-bola.vel))) + bola.vel );
				bola.vel = bola.vel*rt2;	
				

			}
			dT -= tm;

		} else {
			bola.centro += bola.ac*((dT*dT)/2.f) + bola.vel*dT;
				bola.vel += bola.ac * dT;
			dT = 0.f;
			
		//}
	}
	
	
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
			
			break;
		case SDLK_RIGHT:
			
			break;
		case SDLK_UP:
			
			break;
		case SDLK_DOWN:
			
			break;
		case SDLK_a:
			
			break;
		case SDLK_SPACE:
			
			break;
		default:break;
	}
}

void PantallaNivel::handleKeyUp(SDL_keysym* keysym) {


	switch (keysym->sym) {
			case SDLK_LEFT:
			
			break;
		case SDLK_RIGHT:
			
			break;
		case SDLK_UP:
					
			break;
		case SDLK_DOWN:
						
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

