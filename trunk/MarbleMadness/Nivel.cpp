#include "Nivel.h"

#include "tinyxml.h"

#include "Camara.h"


Nivel::Nivel(int num)
{
	this->numero = num;
	this->puntaje = 1000*num;
	this->estado=no_iniciado;
	this->escenario= new Escenario();
	this->personaje=NULL;
	this->inicioNivel=NULL;
	this->finNivel=NULL;

	char* nomArch=new char[12];
	strcpy(nomArch,"nivel");
	char* nuevo=new char[2];
	nuevo=itoa(this->numero,nuevo,10);
	strcat(nomArch,nuevo);
	strcat(nomArch,".xml");
	//cargar(nomArch);

//	iniciar();

	this->dimensionEscenario=2;

	cargar("modelos/PruebaXML.xml");
}

void Nivel::cargar(char* nomArch)
{
    TiXmlDocument XMLdoc(nomArch);
    bool loadOkay = XMLdoc.LoadFile();
    if (loadOkay)
    {
        cout << "PruebaXML.xml loaded" << endl;
        TiXmlElement *Matriz, *Fila, *ObjetoPosicion;
        Matriz = XMLdoc.FirstChildElement( "Matriz" );



		int s = 0;
		int t = 0;

        if ( Matriz )
        {
            // Parse parameters
            Fila = Matriz->FirstChildElement("Fila");
            while ( Fila )
            {
				ObjetoPosicion = Fila->FirstChildElement("Objeto");
				while ( ObjetoPosicion )
				{
					cout << "Parameter: tipo= '" << ObjetoPosicion->Attribute("tipo") << "', y='" << ObjetoPosicion->Attribute("altura") << "'" << endl;

					const char* tipo= ObjetoPosicion->Attribute("tipo");
					int y= atoi(ObjetoPosicion->Attribute("altura"));
					int y2= atoi(ObjetoPosicion->Attribute("alturaSuelo"));
					int r= atoi(ObjetoPosicion->Attribute("rotacion"));

					TipoObjeto tipoObj;
					if(strcmp(tipo,"PRISMA")==0){
						tipoObj= PRISMA;
					}else if (strcmp(tipo,"RAMPA")==0){
						tipoObj= RAMPA;
					}

					this->escenario->cargarObjeto(s,t,y,tipoObj,y2,r);

					ObjetoPosicion = ObjetoPosicion->NextSiblingElement( "Objeto" );
					t++;
				}
				Fila = Fila->NextSiblingElement( "Fila" );
				t= 0;
				s++;
			}
		}
}
}

Nivel::~Nivel(void)
{
}

void Nivel::iniciar() {
	this->escenario = new Escenario();
	this->personaje = new Personaje();	
	this->escenario->agregarObjeto(personaje);	
}



void Nivel::dibujar() {
	//dibujo el escenario
	if(Configuracion::inst()->getWireframe())
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	else
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	if(Configuracion::inst()->getTexturas())
		glDisable(GL_TEXTURE_2D);
	else
		glEnable(GL_TEXTURE_2D);

	if(Configuracion::inst()->getInterpolado()==true)
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);
	if(Configuracion::inst()->getCambiarLuz())
	{
		//Deshabilito, cambio y vuelvo a habilitar
		glDisable( GL_LIGHTING );
		glDisable( GL_LIGHT0 );		
		glLightfv(GL_LIGHT0, GL_DIFFUSE, Configuracion::inst()->getColorLuz(0));
		glEnable( GL_LIGHTING );
		glEnable( GL_LIGHT0 );
	}

	dibujarObjDinamicos();

	GLfloat* vistaNueva = new GLfloat[3];
	vistaNueva[0] = 0.0;//this->dimensionEscenario/2.0;
	vistaNueva[1] = 0.0;
	vistaNueva[2] = 0.0;//this->dimensionEscenario/2.0;

	//Camara::inst()->setVista(Camara::inst()->getposicionCamara(),vistaNueva,Camara::inst()->getvectorCamara());

	glTranslatef(-15.0,-30.0,55.0);
	glPushMatrix();

	this->escenario->dibujar();
	

	glPopMatrix();
	glTranslatef(15.0,30.0,-55.0);

	//glTranslatef(this->dimensionEscenario*MATRIZ_SUELO_W,0,this->dimensionEscenario*MATRIZ_SUELO_H);

	//TODO: Dibujar HUD
}

void Nivel::actualizar(int tiempo) {
	//TODO: actualizar HUD
	/**	
		TODO: "actualizacion logica": Termino el juego? está en pausa? Se dan condiciones 
		logicas para que haya un cambio de estado en el nivel? 
		EN GRAL.: ¿Sucedio algo que afecte al funcionamiento del juego?
	*/

	//actualizo la escena de juego
	
	actualizarFisica(tiempo);

	actualizarObjDinamicos(tiempo);
	
	this->escenario->actualizar(tiempo);
}

void Nivel::teclaPresionada(SDL_keysym* keysym) {
	switch(keysym->sym) {
		case SDLK_UP:
			this->personaje->moverArriba();
			break;
		case SDLK_DOWN:
			this->personaje->moverAbajo();
			break;
		case SDLK_LEFT:
			this->personaje->moverIquierda();
			break;
		case SDLK_RIGHT:
			this->personaje->moverDerecha();
			break;
		default:break;
		case SDLK_1:
			glTranslatef(0.0,0.0,1.0);
			break;
		case SDLK_2:
			glTranslatef(0.0,0.0,-1.0);
			break;
		case SDLK_3:
			glTranslatef(0.0,1.0,0.0);
			break;
		case SDLK_4:
			glTranslatef(0.0,-1.0,0.0);
			break;
		case SDLK_5:
			glTranslatef(1.0,0.0,0.0);
			break;
		case SDLK_6:
			glTranslatef(-1.0,0.0,0.0);
			break;
	}
}


void Nivel::teclaLiberada(SDL_keysym* keysym) {
	switch(keysym->sym) {
		case SDLK_UP:
			this->personaje->detenerArriba();
			break;
		case SDLK_DOWN:
			this->personaje->detenerAbajo();
			break;
		case SDLK_LEFT:
			this->personaje->detenerIquierda();
			break;
		case SDLK_RIGHT:
			this->personaje->detenerDerecha();
			break;
		default:break;
	}
}

void Nivel::agregarObjetoDinamico(ObjetoJuego* obj){
	if (!obj->esEstatico())  {
		this->objsDinamicos.push_back(dynamic_cast<ObjetoDinamico*>(obj));
	}
}


void Nivel::dibujarObjDinamicos(){
	list<ObjetoDinamico*>::iterator itDin;
	for (itDin = this->objsDinamicos.begin(); itDin != this->objsDinamicos.end(); itDin++) {
		(*itDin)->dibujar();
	}
}

void Nivel::actualizarObjDinamicos(int tiempo){
	list<ObjetoDinamico*>::iterator itDin;
	for (itDin = this->objsDinamicos.begin(); itDin != this->objsDinamicos.end(); itDin++) {
		(*itDin)->actualizar(tiempo);
	}
}

void Nivel::actualizarFisica(int tiempo) {
	list<ObjetoDinamico*>::iterator it;
	for (it = objsDinamicos.begin(); it != objsDinamicos.end(); it++) {
		(*it)->actualizado = false;
	}
	for (it = objsDinamicos.begin(); it != objsDinamicos.end(); it++) {
		if (!(*it)->actualizado) {
			(*it)->actualizarFisica(tiempo);
		}
	}

}


void Nivel::dondeEstoy(float x, float z, int &t, int &s) {
	if (escenario != NULL && x / ANCHO_CELDA_GRILLA < MATRIZ_DIMENSION && z / ANCHO_CELDA_GRILLA < MATRIZ_DIMENSION) {
		escenario->dondeEstoy(x, z, t, s);
	}
	t = MATRIZ_DIMENSION + 1;
	s = MATRIZ_DIMENSION +1;
}

ObjetoJuego* Nivel::obtenerObjeto(int t, int s) {
	if (t < MATRIZ_DIMENSION && s < MATRIZ_DIMENSION) {
		return escenario->obtenerObjeto(t, s);
	}
	return NULL;
}