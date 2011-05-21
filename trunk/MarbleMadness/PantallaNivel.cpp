#include "PantallaNivel.h"
#include "Camara.h"

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

/*void updateAlpha() {	
	alphaz += (ticksIni - ticksFin) * xspeed * 20;
	alphax += (ticksIni - ticksFin) * zspeed * 100;
}*/


PantallaNivel::PantallaNivel(void)
{
	this->ticksIni = 0;
	this->ticksFin = 0;
	this->loop= true;
}


PantallaNivel::~PantallaNivel(void)
{
}


void PantallaNivel::dibujar() {

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	//glLoadIdentity();
	
	glEnable(GL_DEPTH_TEST);

	GLfloat lightPos[4] = {0.0, 5.8 ,0.0, 1.0};  ////posicion de la luz
	GLfloat lightVector[3] = {0.0, -1.0 ,0.0};
	////////
	GLfloat luzAmbient[4] = {0.8,0.8,0.8,1.0};
	GLfloat luzDiff[4] = {1.0, 1.0, 1.0,1.0};
	GLfloat luzSpec[4] = {0.5, 0.5, 0.5,1.0};

    ///luces del modelo
	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION, lightPos);
	glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,lightVector);
	glLightf(GL_LIGHT0,GL_SPOT_CUTOFF,60);
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDiff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzSpec);

	glEnable(GL_LIGHTING);
	float* val_ptr = new float[4];
	val_ptr[0]=0.0;
	val_ptr[1]=0.0;
	val_ptr[2]=-5.0;
	val_ptr[3]=1.0;
	glLightfv(GL_LIGHT1,GL_POSITION,val_ptr);

	float* val_color = new float[3];
	val_color[0]=1.0;
	val_color[1]=1.0;
	val_color[2]=1.0;

	glLightfv(GL_LIGHT1,GL_DIFFUSE,val_color);
	glLightfv(GL_LIGHT1,GL_SPECULAR,val_color);

	glEnable(GL_LIGHT1);

	// cambio isa 16/5/2011
	//glTranslatef(0.f,0.f, -10.f);
	
	//Ponemos la camara con la pelotita.
	//gluLookAt(xpos, 0.5f , zpos + 1.f, xpos, 0.f, zpos, 0.f, 1.f, 0.f); 

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_QUADS);
		glColor3ub(0, 0, 255);	
		float yaux = 0.f;
		glVertex3f(-2.f, -2.f, yaux);
		glVertex3f(2.f,-2.f, yaux);
	
		glVertex3f(2.f, 2.f, yaux);
		glVertex3f(-2.f, 2.f, yaux);
	glEnd();

	this->nivelActual->dibujar();
	/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

	glPushMatrix();
		glTranslatef(xpos,ypos,zpos);

		glRotatef(alphax,1.f,0.f,0.f);
		glRotatef(alphaz,0.f,0.f,1.0);

		glColor3ub(255, 0, 0);
	
		GLUquadric* sphereQuadric = gluNewQuadric();

		gluSphere(sphereQuadric, 1.0, 50, 50);
	
	glPopMatrix();

	gluDeleteQuadric(sphereQuadric);
	*/
	//glFlush();
	SDL_GL_SwapBuffers();

}

void PantallaNivel::actualizar(int tiempo) {
	if (this->nivelActual != NULL) {
		
		this->nivelActual->actualizar(tiempo);
	}

	/*Uint32 tiempoTranscurrido = ticksIni - ticksFin;
	
	xpos += (ticksIni - ticksFin)*xspeed;
	zpos += (ticksIni - ticksFin)*zspeed;
	updateAlpha();
	if (saltar) {
		ypos += (1.f*tiempoTranscurrido)*(2.f*A*tiempoSaltoActual+ A*tiempoTranscurrido+B);
		cout << ypos << endl;
		tiempoSaltoActual += tiempoTranscurrido;
		if (tiempoSaltoActual >= T_SALTO) {
			saltar = false;
		}
	}
	ticksFin = ticksIni;*/
}

void PantallaNivel::procesarEventos() {

	//printf("Estoy procesando eventos\n");


	ticksIni =  SDL_GetTicks();
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		switch (ev.type) {
			case SDL_KEYDOWN:
	printf("Estoy SDL_KEYDOWN\n");
				handleKeyDown(&ev.key.keysym);
				this->nivelActual->teclaPresionada(&ev.key.keysym);
				break;
			case SDL_KEYUP:
	printf("Estoy SDL_KEYUP\n");
				handleKeyUp(&ev.key.keysym);
				this->nivelActual->teclaLiberada(&ev.key.keysym);
				break;
			case SDL_MOUSEBUTTONDOWN:
	printf("Estoy SDL_MOUSEBUTTONDOWN\n");
				Camara::inst()->manejadorComienzoMovimientoCamara(&ev.button);
				break;
			case SDL_MOUSEMOTION:
	printf("Estoy SDL_MOUSEMOTION\n");
				Camara::inst()->manejadorMovimientoCamara(&ev.motion);
				break;
			case SDL_MOUSEBUTTONUP:
	printf("Estoy SDL_MOUSEBUTTONUP\n");
				Camara::inst()->manejadorFinMovimientoCamara(&ev.button);
				break;			
			case SDL_QUIT:
				this->detener();
				delete Juego::inst();
				break;
		}
	}	
}

void PantallaNivel::inicializar() {
	this->idNivel=1;
	this->nivelActual=new Nivel(this->idNivel);
	//this->nivelActual->iniciar();
	this->ticksIni = SDL_GetTicks();
	this->ticksFin = this->ticksIni;
	this->loop = true;
}

void PantallaNivel::handleKeyDown(SDL_keysym* keysym) {
	switch (keysym->sym) {
	case SDLK_g:
		Ambiente::aplicarGravedad(!Ambiente::aplicarG);
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

void PantallaNivel::cambiarNivel()
{
	this->idNivel+=1;
	delete this->nivelActual;
	this->nivelActual=new Nivel(this->idNivel);
}
