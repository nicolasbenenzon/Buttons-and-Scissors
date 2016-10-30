#ifndef _rand_h

#define _rand_h

/*Devuelve un número real pseudo-aleatorio
del intervalo [0, 1)*/
double randNormalize(void);

/*Devuelve un número entero pseudo-aleatorio
del intervalo [izq, der] especificado por el
usuario.*/
int randInt(int izq, int der);

/*Devuelve un número real pseudo-aleatorio
del intervalo [izq, der) especificado por el
usuario.*/
double randReal(double izq, double der);

/*Establece una nueva secuencia de números
pseudo-aleatorios.*/
void randomize(void);

#endif