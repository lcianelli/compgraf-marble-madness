#pragma once
class Ambiente
{
public:
	/*
		Vector representando la gravedad, con su respectivo modulo asociado a sus componentes
	*/
	float *gravedad[3];

	/*
		Vector unitario que representa la fuerza aplicada cuando el jugador presiona una tecla. 
	*/
	float *fuerzaExterna[3];
	/*
		Modulo de dicha fuerza
	*/
	float modFuerzaExterna;


	Ambiente(void);
	~Ambiente(void);
};

