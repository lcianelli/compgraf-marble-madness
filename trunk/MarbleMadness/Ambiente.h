#pragma once
class Ambiente
{
public:
	/*
		Vector representando la gravedad, con su respectivo modulo asociado a sus componentes
	*/
	static float *gravedad;

	static bool aplicarG;
	/*
		Modulo de dicha fuerza
	*/
	static float modFuerzaExterna;

	static void init();

	static void aplicarGravedad(bool aplicar);
	Ambiente(void);
	~Ambiente(void);
};

