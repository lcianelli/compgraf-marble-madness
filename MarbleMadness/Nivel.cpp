#include "Nivel.h"

#include "tinyxml.h"

#include "Camara.h"

#include "ManejadorTextura.h"
int texidesc;
int texfondo;

SDL_Surface* s;

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

	texidesc= ManejadorTextura::inst()->cargar("imgs\\texturaEscenario.png");

	//cargar(nomArch);

//	iniciar();

	this->dimensionEscenario=3;


	//this->entorno= new GLMmodel();
	//entorno = glmReadOBJ("modelos/montana.obj");
	
	cargar("modelos/PruebaXML7.xml");

	this->iniciar();
	//cargar("modelos/PruebaXML.xml");
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
	//cambio isa 22/05/2011
	/*	this->escenario = new Escenario();
	this->personaje = new Personaje();	
	this->escenario->agregarObjeto(personaje);*/	

	this->personaje= new Bola();
	int t;
	int s;

	float pos[3]={0.0,0.0,0.0};
	float vel[3]={0.0,0.0,0.0};

	//bola->setPosicion(pos);


	//float* lala= bola->getPosicion();

	this->personaje->setVelocidad(vel);

	this->escenario->dondeEstoy(0.0,0.0,t,s);
	this->personaje->setPiso((ObjetoEstatico*)this->escenario->obtenerObjeto(t,s));

	this->personaje->setPosicion(pos);


	this->objsDinamicos.push_front(this->personaje);
	
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
		glLightfv(GL_LIGHT0, GL_POSITION, Configuracion::inst()->getDireccionLuz(0));
		glLightfv(GL_LIGHT0, GL_DIFFUSE, Configuracion::inst()->getColorLuz(0));
		glEnable( GL_LIGHTING );
		glEnable( GL_LIGHT0 );
	}



	glPushMatrix();

	
	//glMaterialfv(GL_FRONT_AND_BACK, GL_COLOR_MATERIAL, entorno->materials[1].emmissive);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, entorno->materials[1].diffuse);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, entorno->materials[1].specular);
	//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, entorno->materials[1].shininess);


	//glEnable(GL_TEXTURE_2D);

	//glmDraw(entorno, GLM_SMOOTH|GLM_TEXTURE);
	//glTranslatef(-15.0,-30.0,55.0);
	//glTranslatef(-ANCHO_CELDA_GRILLA/2.0,0.0,-ANCHO_CELDA_GRILLA/2.0);


	glPushMatrix();

	glTranslatef(ANCHO_CELDA_GRILLA/2.0,0.0,ANCHO_CELDA_GRILLA/2.0);

	dibujarObjDinamicos();

	glPopMatrix();
	GLfloat* vistaNueva = new GLfloat[3];
	vistaNueva[0] = 0.0;//this->dimensionEscenario/2.0;
	vistaNueva[1] = 0.0;
	vistaNueva[2] = 0.0;//this->dimensionEscenario/2.0;

	//Camara::inst()->setVista(Camara::inst()->getposicionCamara(),vistaNueva,Camara::inst()->getvectorCamara());

	/*glBegin(GL_LINES);
		glColor3f(1.0,0.0,0.0);
		glVertex3f(-15.0f, 0.0f, 0.0f);
		glVertex3f(15.0f, 0.0f, 0.0f);
		glColor3f(0.0,1.0,0.0);
		glVertex3f(0.0f, -15.0f, 0.0f);
		glVertex3f(0.0f, 15.0f, 0.0f);
		glColor3f(0.0,0.0,1.0);
		glVertex3f(0.0f, 0.0f, 15.0f);
		glVertex3f(0.0f, 0.0f, -15.0f);
		glColor3f(0.8,0.8,0.8);
		glVertex3f(-5.0f, 15.0f, 5.0f);
		glVertex3f(-5.0f, -15.0f, 5.0f);
	glEnd();*/


		glBindTexture(GL_TEXTURE_2D, texidesc);
		glEnable( GL_TEXTURE_2D );

	this->escenario->dibujar();
	

	
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	//glTranslatef(15.0,30.0,-55.0);

}

void Nivel::actualizar(int tiempo) {
	//TODO: actualizar HUD
	/**	
		TODO: "actualizacion logica": Termino el juego? está en pausa? Se dan condiciones 
		logicas para que haya un cambio de estado en el nivel? 
		EN GRAL.: ¿Sucedio algo que afecte al funcionamiento del juego?
	*/

	//actualizo la escena de juego
	
	actualizarObjDinamicos(tiempo);
	
	
	SDL_Surface* s = SDL_GetVideoSurface();
	//glOrtho(0.f, s->w, 0.f, s->h, -1.f, 1.f);

	//glLoadIdentity();
	///glViewport(0, 0, (GLsizei) s->w, (GLsizei) s->h);
	glBindTexture(GL_TEXTURE_2D, texfondo);
	glEnable( GL_TEXTURE_2D );			
			

	glBegin(GL_QUADS);
		glTexCoord2f( 0.f, 1.0f );
		glVertex3f(0.f, 10.f, 0.f);
		glTexCoord2f( 0.f, 0.f );
		glVertex3f(0.f, 0.f,0.f);
		
		glTexCoord2f( 1.f, 0.f );
		glVertex3f(10.f, 0.f, 0.f);
		glTexCoord2f( 1, 1.f );
		glVertex3f(10.f, 10.f, 0.f);
		
	glEnd();


}

void Nivel::teclaPresionada(SDL_keysym* keysym) {
	float ptoCambioDiraccion[3];
	float anguloGiroY = this->personaje->getAnguloGiroAnteriorEjeY();// = this->personaje->
	float anguloRadianes = anguloGiroY*3.14159/180.0;
	float* posicion = this->personaje->getPosicion();
	float reseteoPos[3] = {0.0,0.0,0.0};
	float* velocidad = this->personaje->getVelocidad();

	switch(keysym->sym) {
		case SDLK_DOWN:
			//TODO: Borrar!
			printf("Estoy SDLK_DOWN\n");
			ptoCambioDiraccion[0]= posicion[0]*cos(anguloRadianes);
			//TODO: ver q onda el [1]
			ptoCambioDiraccion[1]= 0.0;
			ptoCambioDiraccion[2]= -posicion[0]*sin(anguloRadianes);
			this->personaje->setPosicion(reseteoPos);
			posicion[0]=0.0;
			this->personaje->CambioDireccion(ptoCambioDiraccion,180.0);
			break;
		case SDLK_UP:
			//TODO: Borrar!!
			printf("Estoy SDLK_UP\n");
			//TODO: manejar bien el tema del aumento de velocidad
			//deltaX += 0.001;
			if(velocidad[0]<5.0){
				velocidad[0] += 0.01;
			}
			this->personaje->setVelocidad(velocidad);
			break;
		case SDLK_LEFT:
			//TODO: Borrar!!
			printf("Estoy SDLK_LEFT\n");
			ptoCambioDiraccion[0]= posicion[0]*cos(anguloRadianes);// + ptoCambioDiraccion[0];
			//TODO: ver q onda el [1]
			ptoCambioDiraccion[1]= 0.0;
			ptoCambioDiraccion[2]= -posicion[0]*sin(anguloRadianes);// + ptoCambioDiraccion[2];
			//if(anguloGiroY >){}
			this->personaje->setPosicion(reseteoPos);
			this->personaje->CambioDireccion(ptoCambioDiraccion,15.0);
			break;
		case SDLK_RIGHT:
			//TODO: Borrar!!
			printf("Estoy SDLK_RIGHT\n");
			ptoCambioDiraccion[0]= posicion[0]*cos(anguloRadianes);// + ptoCambioDiraccion[0];
			//TODO: ver q onda el [1]
			ptoCambioDiraccion[1]= 0.0;
			ptoCambioDiraccion[2]= -posicion[0]*sin(anguloRadianes);// + ptoCambioDiraccion[2];
			this->personaje->setPosicion(reseteoPos);
			this->personaje->CambioDireccion(ptoCambioDiraccion,345.0);
			break;
		case SDLK_a:
			//TODO: Borrar!!
			printf("Estoy SDLK_a\n");
			this->personaje->Saltar();
			break;
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
		default:
			break;
	}
}


void Nivel::teclaLiberada(SDL_keysym* keysym) {
	switch(keysym->sym) {
		case SDLK_a:
			//TODO: ver bien como manejar el empezar a caer del salto
			//dejoDeSaltar=true;
			glRotatef(315.0,0.0,0.0,1.0);
			break;
		default:
			break;
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
		glPushMatrix();
			float* posicion = (*itDin)->getPosicion();
			Matriz matrizTraslacion = Matriz(posicion);
			(*itDin)->multMatriz(matrizTraslacion);
			float* matrizTransformacionObjeto = (*itDin)->getMatriz().getMatrizVector();

			printf("Empieza Matriz:  \n");
			for(int i=0; i<16; i++){
				printf(" Array:  %f\n",matrizTransformacionObjeto[i]);
			}

			glMatrixMode(GL_MODELVIEW);

			glMultMatrixf(matrizTransformacionObjeto);
			
			float altura = (*itDin)->getPiso()->getAltura() + (*itDin)->getPiso()->getAlturaSuelo() + 2.0;
			glTranslatef(0.0,altura,0.0);	

			(*itDin)->dibujar();
		
			
		glPopMatrix();
	}
}

void Nivel::actualizarObjDinamicos(int tiempo){
	list<ObjetoDinamico*>::iterator itDin;
	for (itDin = this->objsDinamicos.begin(); itDin != this->objsDinamicos.end(); itDin++) {

		// Calcula su nueva posicion en funcion de la anterior, la velocidad y el deltaT
		float* velocidad= (*itDin)->getVelocidad();
		float* posicion= (*itDin)->getPosicion();
		Vector vectorPosicion = Vector(posicion[0],posicion[1],posicion[2]);
		
		//nueva posicion respecto a los ejes locales.
		float nuevaPosicion[3];
		nuevaPosicion[0] = posicion[0] + velocidad[0]*tiempo/1000;
		nuevaPosicion[1] = posicion[1] + velocidad[1]*tiempo/1000;
		nuevaPosicion[2] = posicion[2] + velocidad[2]*tiempo/1000;
		Vector vectorNuevaPosicion = Vector(nuevaPosicion[0],nuevaPosicion[1],nuevaPosicion[2]);

		//Calcular la posicion global: multiplicar la matriz inversa de transformacion del objeto
		// por la nueva posicion local.
		//posicion global para saber dond esta en el escenario
		Matriz matrizTransformacion2 = (*itDin)->getMatriz();
		float* vectorNuevaPosicionGlobal = matrizTransformacion2.multiplicar(vectorNuevaPosicion);
		float* vectorPosicionGlobal = matrizTransformacion2.multiplicar(vectorPosicion);

		Vector vec = Vector(vectorPosicionGlobal[0],vectorPosicionGlobal[1],vectorPosicionGlobal[2]);


		// obtengo el objeto en el escenario sobre el q estaria en la proxima posicion.
		int t;
		int s;
		this->escenario->dondeEstoy(vectorNuevaPosicionGlobal[0]+ANCHO_CELDA_GRILLA/2.0,vectorNuevaPosicionGlobal[2]+ANCHO_CELDA_GRILLA/2.0,t,s);
		ObjetoEstatico* prox=(ObjetoEstatico*)this->escenario->obtenerObjeto(t,s);
		// Calculo la altura del objeto al que deberia de pasar

if(prox != NULL){
		float proxAltura = prox->getAltura() + prox->getAlturaSuelo();

		printf("proxAltura: %f\n",proxAltura);


//manejar mientras esta en colision!!!!!
//se va a actualizar el escalado
//una vez q termina la deformacion, esto nos lo va a indicar una bandera en el objeto

		float actualAltura = (*itDin)->getPiso()->getAltura() + (*itDin)->getPiso()->getAlturaSuelo();

		if(actualAltura < proxAltura){
			// ************************** COLISION *****************************//

			Vector puntoCara;
			//Para obtener la normal con la que choca el objeto, transformamos la direccion que es 
			// siempre sobre el eje local de las X a una direccion global
			Vector dir = Vector(1.0,0.0,0.0);
			Vector origen = Vector(0.0,0.0,0.0);
			float* dirAux = matrizTransformacion2.multiplicar(dir);
			float* origenAux = matrizTransformacion2.multiplicar(origen);
			Vector vectorDireccion = Vector(dirAux[0]-origenAux[0],dirAux[1]-origenAux[1],dirAux[2]-origenAux[2]);
			//float* vectorDireccionPasarAux = matrizTransformacion2.multiplicar(vectorDireccion);
			float vectorDireccionPasar[3];
			vectorDireccionPasar[0] = vectorDireccion.X();
			vectorDireccionPasar[1] = vectorDireccion.Y();
			vectorDireccionPasar[2] = vectorDireccion.Z();

			Vector normal = prox->getNormalInteraccion(vectorDireccionPasar,puntoCara);

			// obtenemos el plano con el que se va a chocar

			//el pto cara es relativo al sist del obj con el q voy a chocar!!
			float distX= ANCHO_CELDA_GRILLA*(0.5 + t);
			float distZ= ANCHO_CELDA_GRILLA*(0.5 + s);
			// el ptoCara absoluto es el relativo al obj estatico mas
			//las transformaciones q se le hizo al prisma en el escenario
			puntoCara = puntoCara + Vector(distX,proxAltura/2.0,distZ);
			//TODO: ver q onda con la Y !!!

			// REFLEJO DEL PLANO CON EL QUE CHOCA
						Matriz matrizInversaTransformacion = (*itDin)->getMatriz().inversa();
			Vector ptoCaraRelativo = matrizInversaTransformacion.multiplicar(puntoCara);
			float* ptoCaraRelativoFloat = new float[3];
			ptoCaraRelativoFloat[0] = ptoCaraRelativo.X();
			ptoCaraRelativoFloat[1] = ptoCaraRelativo.Y();
			ptoCaraRelativoFloat[2] = ptoCaraRelativo.Z();
			// TODO: Calcular cuanto hay q rotar en Y y en Z, para eso se necesita multiplicar
			// a la normal de la cara absoluta por la matriz de transformacion para obtener la normal relativa.
	Vector normalRelativa = matrizInversaTransformacion.multiplicar(normal);
			//float radianesZ = normalRelativa.Z()/sqrt(sqr(normalRelativa.Z())+sqr(normalRelativa.Y()))*3.141592654/180.0;
			//float radianesY = normalRelativa.X()/sqrt(sqr(normalRelativa.Z())+sqr(normalRelativa.X()))*3.141592654/180.0;

			float anguloRotacionParaNormalEjeZ = 0.0;
			float anguloRotacionParaNormalEjeY = 0.0;

			if( sqrt(sqr(normalRelativa.Z())+sqr(normalRelativa.Y())) != 0 ){
				anguloRotacionParaNormalEjeZ= asin(normalRelativa.Z()/sqrt(sqr(normalRelativa.Z())+sqr(normalRelativa.Y())));
			}
			
			if( sqrt(sqr(normalRelativa.Z())+sqr(normalRelativa.X())) != 0 ){
				anguloRotacionParaNormalEjeY= acos(normalRelativa.X()/sqrt(sqr(normalRelativa.Z())+sqr(normalRelativa.X())));
			}
			(*itDin)->Colision(anguloRotacionParaNormalEjeZ,anguloRotacionParaNormalEjeY,ptoCaraRelativoFloat);

			//TODO: setearle al objeto q empiece la deformacion con los scale necesarios

			// Reseteo posicion para que empiece a moverse desde su sistema relativo
			nuevaPosicion[0]=0.0;
			nuevaPosicion[1]=0.0;
			nuevaPosicion[2]=0.0;
			(*itDin)->setPosicion(nuevaPosicion);

		}else if(actualAltura > proxAltura){
			// ************************** CAIGO O RAMPA *****************************//
			//ptoGiroCoords[1]=proxAltura;
			(*itDin)->setPiso((ObjetoEstatico*)this->escenario->obtenerObjeto(t,s));
			(*itDin)->setPosicion(nuevaPosicion);
		nuevaPosicion[0]=0.0;
			nuevaPosicion[1]=0.0;
			nuevaPosicion[2]=0.0;
			(*itDin)->setPosicion(nuevaPosicion);
			//float* bajar = new float[3];
			//bajar[0]= 0.0;
			//bajar[1]= -(actualAltura - proxAltura);
			//bajar[2]= 0.0;
			//Matriz matrizTraslacion = Matriz(bajar);
			//(*itDin)->multMatriz(matrizTraslacion);
		}else{
			// ************************** SOLO ME DESPLAZO *****************************//
			(*itDin)->setPiso((ObjetoEstatico*)this->escenario->obtenerObjeto(t,s));

			float* posicion2= (*itDin)->getPosicion();
		//	Vector vectorPosicion = Vector(posicion[0],posicion[1],posicion[2]);
			float* velocidad2= (*itDin)->getVelocidad();
			//nueva posicion respecto a los ejes locales.
			float nuevaPosicion2[3];
			nuevaPosicion2[0] = velocidad2[0]*tiempo/1000;
			nuevaPosicion2[1] = velocidad2[1]*tiempo/1000;
			nuevaPosicion2[2] = velocidad2[2]*tiempo/1000;
			(*itDin)->setPosicion(nuevaPosicion2);
			(*itDin)->setPosicion(nuevaPosicion);
		}


}


		
		//TODO: ver como funciona internamente la rotacion de la misma pelota
		// setea angulo de rotacion sobre su propio eje.
		//(*itDin)->setRotacion(tiempo);

	}
}

