#ifndef MATHEX_H
#define MATHEX_H

#include <math.h>

#define EPSILON 1.0e-4
#define CERO EPSILON

#define M_PI 3.1415926535

template <class T> inline T limitar(const T &x, const T &menor, const T &mayor) {

	if (x < menor) return menor;
	if (x > mayor) return mayor;
	return x;
}

template <class T> inline T sqr(const T &x) {
	return x * x;	
}

template <class T> inline T RadAGrados(const T &rad) {
	return (rad * 180.0) / M_PI;
}

template <class T> inline T GradosARad(const T &grados) {
	return (grados * M_PI) / 180.0;
}



#endif


