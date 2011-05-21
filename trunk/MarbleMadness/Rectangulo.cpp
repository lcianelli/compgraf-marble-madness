#include "Rectangulo.h"



float Rectangulo::probarInterseccion(const Rayo r, float &distancia, Vector &pNormal, Vector &interseccion) {
	int resultado = Plano::probarInterseccion(r, distancia, pNormal);
	if (resultado == 0) {
		interseccion = Vector();//vector invalido para la interseccion
		return 0.f; //rayo paralelo a plano
	} else {
		//choca con plano
		interseccion = Vector(r.P()+r.V()*distancia);
		Vector lado1 = p2-p1;
		Vector lado2 = p3-p1;
		float esc1 = lado2.escalar(interseccion-p1)/lado2.norma();
		float esc2 = lado1.escalar(interseccion-p1)/lado1.norma();
		//choca con rectangulo
		if ( fabs(esc1) >= CERO && esc1 < _w && esc2 < _h && fabs(esc2) >= CERO ) {
			return distancia;
		}
		//choca con plano pero no rectangulo
		return 0.f;
	}
}


Rectangulo::~Rectangulo(void)
{
}
