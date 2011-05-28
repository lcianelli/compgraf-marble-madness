#include "ObjetoDinamico.h"


Matriz ObjetoDinamico::getMatriz(){
	return this->matrizTransformacion;
}

void ObjetoDinamico::multMatriz(Matriz matriz){
	this->matrizTransformacion = this->matrizTransformacion.multiplicar(matriz);
}

bool ObjetoDinamico::esEstatico() {
	return false;
}

ObjetoEstatico* ObjetoDinamico::getPiso(){
	return this->piso;
}

void ObjetoDinamico::setPiso(ObjetoEstatico* obj){
	this->piso=obj;
}

//TODO: ver si se usa
bool ObjetoDinamico::getColisione(){
	return this->colisione;
}
//TODO: ver si se usa
void ObjetoDinamico::setColisione(bool colisiono){
	this->colisione= colisiono;
}

float* ObjetoDinamico::getescalado(){
	return this->escalado;
}

void ObjetoDinamico::setescalado(float* scale){
	this->escalado[0]=scale[0];
	this->escalado[1]=scale[1];
	this->escalado[2]=scale[2];
}


float* ObjetoDinamico::getPosicion(){
	return this->posicion;
}

void ObjetoDinamico::setPosicion(float* pos){
	this->posicion[0]=pos[0];
	this->posicion[1]=pos[1];
	this->posicion[2]=pos[2];
}

float* ObjetoDinamico::getVelocidad(){
	return this->velocidad;
}

void ObjetoDinamico::setVelocidad(float* vel){
	this->velocidad[0]=vel[0];
	this->velocidad[1]=vel[1];
	this->velocidad[2]=vel[2];
}

float ObjetoDinamico::getSalto(){
	return this->salto;
}

void ObjetoDinamico::setSalto(float sal){
	this->salto = sal;
}

float ObjetoDinamico::getCantSalto(){
	return this->salto;
}

void ObjetoDinamico::setCantSalto(float cantSal){
	this->cantSalto = cantSal;
}


float ObjetoDinamico::getAnguloGiroAnteriorEjeY(){
	return this->AnguloGiroAnteriorEjeY;
}




/********************   MANEJO MOVIMIENTOS   **************************/


void ObjetoDinamico::subeRampa(float anguloGiroZ, float* ptoSubidaCaida){

	//AnguloGiroZ se obtuvo de la rampa
	Matriz matrizTraslacion = Matriz(ptoSubidaCaida);
	this->multMatriz(matrizTraslacion);
	Matriz matrizRotacion = Matriz(anguloGiroZ,3);
	this->multMatriz(matrizRotacion);
	//glTranslatef(ptoSubidaCaida[0],ptoSubidaCaida[1],ptoSubidaCaida[2]);
	//glRotatef(anguloGiroZ,0.0,0.0,1.0);
}

void ObjetoDinamico::CambioDireccion(float* ptoCambioDiraccion, float anguloGiroY){
	//Avanzo deltaX 
	//AnguloGiroY se seteo segun la tecla presionada para cambiar la direccion del movimiento
	Matriz matrizTraslacion = Matriz(ptoCambioDiraccion);
	this->multMatriz(matrizTraslacion);
	Matriz matrizRotacion = Matriz(anguloGiroY,2);
	this->multMatriz(matrizRotacion);
	//glTranslatef(ptoCambioDiraccion[0],ptoCambioDiraccion[1],ptoCambioDiraccion[2]);
	//glRotatef(anguloGiroY,0.0,1.0,0.0);
	this->AnguloGiroAnteriorEjeY = anguloGiroY;
}

void ObjetoDinamico::Saltar(){
	if(salto==0.0){
		//empieza el salto
		//glRotatef(45.0,0.0,0.0,1.0);
		Matriz matrizRotacion = Matriz(45.0,3);
		this->multMatriz(matrizRotacion);
	}
	// incremento la variable que me indica cuanto se salto en total
	salto += cantSalto;
	float* trans;
	trans[0]= cantSalto;
	trans[1]= 0.0;
	trans[2]= 0.0;
	Matriz matrizTraslacion = Matriz(trans);
	this->multMatriz(matrizTraslacion);
	//glTranslatef(cantSalto,0.0,0.0);
}

void ObjetoDinamico::Colision(float anguloRotarNormalZ, float anguloRotarNormalY, float* ptoPlano){


	//ptoPlano[0]=0.0;
	//Llevar pto del plano al 0,0,0 global
	//glTranslatef(ptoPlano[0],ptoPlano[1],ptoPlano[2]);

	float ptoPlano2[3];
	ptoPlano2[0] = -ptoPlano[0];
	ptoPlano2[1] = -ptoPlano[1];
	ptoPlano2[2] = -ptoPlano[2];

	////Matriz matrizTraslacion = Matriz(ptoPlano2);
	////this->multMatriz(matrizTraslacion);

	// Llevar la normal del plano al eje de las X
	//glRotatef(anguloRotarNormalZ,0.0,0.0,1.0);
	//////float anguloZ = RadAGrados(anguloRotarNormalZ);
	//////Matriz matrizRotacionZ = Matriz(360.0-anguloZ,3);
	//////this->multMatriz(matrizRotacionZ);
	////////glRotatef(anguloRotarNormalY,0.0,1.0,0.0);
	//////float anguloY = RadAGrados(anguloRotarNormalY);
	//////Matriz matrizRotacionY = Matriz(360.0-anguloY,2);
	//////this->multMatriz(matrizRotacionY);


	Matriz matrizReflejo = Matriz(180.0+(90.0-(this->AnguloGiroAnteriorEjeY))*2.0,2);
	this->multMatriz(matrizReflejo);

	// Hacer la reflexion del movimiento con respecto al plano
	Matriz matrizReflexionPlanoYZ= Matriz(3);
	this->multMatriz(matrizReflexionPlanoYZ);


	// Deshacer las rotaciones q llevaron la normal del plano al eje X
	//glRotatef(360-anguloRotarNormalY,0.0,1.0,0.0);
	//////Matriz matrizRotacionY2 = Matriz(anguloY,2);
	//////this->multMatriz(matrizRotacionY2);
	////////glRotatef(360-anguloRotarNormalZ,0.0,0.0,1.0);
	//////Matriz matrizRotacionZ2 = Matriz(anguloZ,3);
	//////this->multMatriz(matrizRotacionZ2);

	// Vuelvo del todo
	//ptoPlano[0] = -ptoPlano[0];
	//ptoPlano[1] = -ptoPlano[1];
	//ptoPlano[2] = -ptoPlano[2];
	////Matriz matrizTraslacion2 = Matriz(ptoPlano);
	////this->multMatriz(matrizTraslacion2);
}


/********************   FIN MANEJO MOVIMIENTOS   **************************/


ObjetoDinamico::~ObjetoDinamico(void)
{
}

