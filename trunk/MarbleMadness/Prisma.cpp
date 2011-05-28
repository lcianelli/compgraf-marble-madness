#include "Prisma.h"


Prisma::Prisma(void): ObjetoEstatico()
{
	this->objeto= new GLMmodel();
	objeto = glmReadOBJ("modelos/objetoPrisma10.obj");
}


Prisma::~Prisma(void)
{
}

void Prisma::dibujar() {

	//glMaterialfv(GL_FRONT_AND_BACK, GL_COLOR_MATERIAL, objeto->materials[1].emmissive);
 //   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, objeto->materials[1].diffuse);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, objeto->materials[1].specular);
	//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, objeto->materials[1].shininess);

	glmDraw(objeto, GLM_SMOOTH | GLM_TEXTURE);
}


Vector Prisma::getNormalInteraccion(float* vectorDireccion, Vector &ptoCara) {
	float* normal = new float[3];

	//TODO: almacenar en "normal" los datos de la normal a la cara con la que obj interactua, en la misma direccion desde la que obj "golpea"



	vectorDireccion[1]=0.0;

	Vector vector = Vector(vectorDireccion[0],vectorDireccion[1],vectorDireccion[2]).unitario();

	printf("**    vectorDireccion    %f %f %f\n **",vectorDireccion[0],vectorDireccion[1],vectorDireccion[2]);

	Vector normalCara1 = Vector(1.0,0.0,0.0);
	Vector normalCara2 = Vector(0.0,0.0,1.0);
	Vector normalCara3 = Vector(-1.0,0.0,0.0);
	Vector normalCara4 = Vector(0.0,0.0,-1.0);

	Vector vectorRetorno;

	if((normalCara1.escalar(vector)<0)&&(((normalCara1*vector).Y() > 0)||(normalCara1*vector).igual(Vector(0.0,0.0,0.0)))){
		vectorRetorno= normalCara1;
	printf("**    ES   normalCara1  **");
	normalCara1.imprimir();
	}else 	if((normalCara2.escalar(vector)<0)&&(((normalCara2*vector).Y() > 0)||(normalCara2*vector).igual(Vector(0.0,0.0,0.0)))){
		vectorRetorno = normalCara2;
	printf("**    ES    normalCara2 **");
	}else 	if((normalCara3.escalar(vector)<0)&&(((normalCara3*vector).Y() > 0)||(normalCara3*vector).igual(Vector(0.0,0.0,0.0)))){
		vectorRetorno = normalCara3;
	printf("**    ES   normalCara3  **");
	}else 	if((normalCara4.escalar(vector)<0)&&(((normalCara4*vector).Y() > 0)||(normalCara4*vector).igual(Vector(0.0,0.0,0.0)))){
		vectorRetorno = normalCara4;
	printf("**    ES  normalCara4   **");
	}


	printf("Vector:  \n");
	vector.imprimir();

	printf("**    NORMAL   normalCara1  **\n");
	normalCara1.imprimir();
	printf("**    NORMAL   normalCara2  **\n");
	normalCara2.imprimir();	
	printf("**    NORMAL   normalCara3  **\n");
	normalCara3.imprimir();	
	printf("**    NORMAL   normalCara4  **\n");
	normalCara4.imprimir();

	printf("**    (normalCara1.escalar(vector))    %f\n **",(normalCara1.escalar(vector)));
	printf("**    (normalCara2.escalar(vector))    %f\n **",(normalCara2.escalar(vector)));
		printf("**    (normalCara3.escalar(vector))    %f\n **",(normalCara3.escalar(vector)));
			printf("**    (normalCara4.escalar(vector))    %f\n **",(normalCara4.escalar(vector)));

	printf("**    (normalCara1*vector)    %f %f %f\n **",(normalCara1*vector).X(),(normalCara1*vector).Y(),(normalCara1*vector).Z());
	printf("**   (normalCara2*vector)    %f %f %f\n **",(normalCara2*vector).X(),(normalCara2*vector).Y(),(normalCara2*vector).Z());
		printf("**    (normalCara3*vector)    %f %f %f \n **",(normalCara3*vector).X(),(normalCara3*vector).Y(),(normalCara3*vector).Z());
			printf("**    (normalCara4*vector)    %f %f %f\n **",(normalCara4*vector).X(),(normalCara4*vector).Y(),(normalCara4*vector).Z());
			
			
			// TODO: pasarlo a glm!!!
	for(int i = 0; i < this->objeto->numtriangles; i++){
		int indiceVertice1 = this->objeto->triangles[i].nindices[0];
		if((this->objeto->normals[indiceVertice1*3+0]==vectorRetorno.X())&&(this->objeto->normals[indiceVertice1*3+1]==vectorRetorno.Y())&&(this->objeto->normals[indiceVertice1*3+2]==vectorRetorno.Z())){
			int indiceVerticeEnArray = this->objeto->triangles[i].vindices[0];
			ptoCara= Vector(this->objeto->vertices[indiceVerticeEnArray*3+0],this->objeto->vertices[indiceVerticeEnArray*3+1],this->objeto->vertices[indiceVerticeEnArray*3+2]);
			break;
		}
	}

	printf("    VectorRetorno: %f %f %f\n", vectorRetorno.X(),vectorRetorno.Y(),vectorRetorno.Z());
	 
	return vectorRetorno;	
}



