#include <stdio.h>
#include "getnum.h"
#include "rand.h"
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

#define BORRA_BUFFER while(getchar()!= '\n');
#define DEBUG
#define DIM 5
#define DIRECCIONES_POSIBLES 8

typedef char * TipoLinea;
typedef TipoLinea * TipoTablero;
typedef struct
{
	int fila;
	int columna;
}tCoordenada;

int HayGanador(TipoTablero tablero, int dim);
int HayCortesDesdePos(TipoTablero tablero, tCoordenada posicion, int dim);
int HayCortesDesdePosEnDir(TipoTablero tablero, tCoordenada posicion, int dim, int direccion);
void CalcularDeltasFilCol(int direccion, int * deltaFil, int * deltaCol);

int
main(void)
{
	randomize();
	TipoTablero tablero;
	tablero = malloc(pow(DIM, 2));
	int i, j;
	for(i = 0; i < DIM; i++)
	{
		tablero[i] = malloc(DIM);
		/*for(j = 0; j < DIM; j++)
		{
			tablero[i][j] = randInt(0, 4) + 'A';
			printf("%c ", tablero[i][j]);
		}
		putchar('\n');*/
	}
	//tCoordenada origen = {0, 0};
	//tCoordenada destino = {2,0};
	//int cortes = JugadaValida(tablero, origen, destino, DIM);
	#ifdef DEBUG
		tablero[0][0] = '0'; tablero[0][1] = 'A'; tablero[0][2] = '0'; tablero[0][3] = '0'; tablero[0][4] = '0';
		tablero[1][0] = '0'; tablero[1][1] = '0'; tablero[1][2] = 'C'; tablero[1][3] = 'B'; tablero[1][4] = 'D';
		tablero[2][0] = '0'; tablero[2][1] = '0'; tablero[2][2] = 'A'; tablero[2][3] = 'E'; tablero[2][4] = '0';
		tablero[3][0] = '0'; tablero[3][1] = 'C'; tablero[3][2] = 'D'; tablero[3][3] = '0'; tablero[3][4] = 'A';
		tablero[4][0] = 'B'; tablero[4][1] = '0'; tablero[4][2] = '0'; tablero[4][3] = 'E'; tablero[4][4] = '0';
		
		for(i = 0; i < DIM; i++)
		{
			for(j = 0; j < DIM; j++)
			{
				printf("%c ", tablero[i][j]);
			}
			putchar('\n');
		}
		
		//tCoordenada origen = {3,2};
		//tCoordenada destino = {1,4};
		int hayGanador = HayGanador(tablero, DIM);
		printf("%d\n", hayGanador);
	#endif
	return 0;
}

int HayGanador(TipoTablero tablero, int dim)
{
	int i, j, hayCortes = 0;
	tCoordenada posicion;
	
	//Recorre cada posición del tablero
	for(i = 0; i < dim && !hayCortes; i++)
	{
		for(j = 0; j < dim && !hayCortes; j++)
		{
			//Si la posición [i][j] no está vacía, se evalúa si hay algún corte posible arrancando desde esa posición
			if(tablero[i][j] != '0')
			{
				posicion.fila = i;
				posicion.columna = j;
				hayCortes = HayCortesDesdePos(tablero, posicion, dim); //Si hay algún corte, automáticamente sale del ciclo y no sigue recorriendo
			}
		}
	}
	return !hayCortes; //Si no hay ningún corte posible, significa que hay un ganador y devuelve 1, en caso contratio devuelve 0
}

int HayCortesDesdePos(TipoTablero tablero, tCoordenada posicion, int dim)
{
	int i, hayCortes = 0;
	
	//Para cada dirección posible evalúa si existe algún corte partiendo desde la posición pasada como parámetro
	for(i = 0; i < DIRECCIONES_POSIBLES && !hayCortes; i++)
		//Evalúa los cortes en cada dirección, y para pasar la dirección como parámetro, pasa el ángulo
		hayCortes = HayCortesDesdePosEnDir(tablero, posicion, dim, i * 45); //Si hay algún corte en alguna dirección, hayCortes pasa a valer 1 y sale del ciclo
	return hayCortes;
	
}

int HayCortesDesdePosEnDir(TipoTablero tablero, tCoordenada posicion, int dim, int direccion)
{
	int i, j, deltaFil, deltaCol;
	
	//Calculo el sentido en que recorro el tablero según la dirección
	CalcularDeltasFilCol(direccion, &deltaFil, &deltaCol);
	
	for(i = posicion.fila + deltaFil, j = posicion.columna + deltaCol; i >= 0 && i < dim && j >= 0 && j < dim; i += deltaFil, j += deltaCol)
	{
		//Si en esa posición hay algún botón, se fija cuál es
		if(tablero[i][j] != '0') 
		{
			//Si es del mismo color devuelve 1, si no 0 ya que el primero que apareció es de otro color y no hay cortes en esa dirección
			if(tablero[i][j] == tablero[posicion.fila][posicion.columna])
				return 1;
			else
				return 0;
		}
	}
	return 0; //Si salió del ciclo significa que no habían otros botones en esa dirección, por lo que no hay cortes posibles
}

void CalcularDeltasFilCol(int direccion, int * deltaFil, int * deltaCol)
{
	switch(direccion)
	{
		case 0:
			*deltaFil = 0;
			*deltaCol = 1;
		break;
		
		case 45:
			*deltaFil = -1;
			*deltaCol = 1;
		break;
		
		case 90:
			*deltaFil = -1;
			*deltaCol = 0;
		break;
		
		case 135:
			*deltaFil = -1;
			*deltaCol = -1;
		break;
		
		case 180:
			*deltaFil = 0;
			*deltaCol = -1;
		break;
		
		case 225:
			*deltaFil = 1;
			*deltaCol = -1;
		break;
		
		case 270:
			*deltaFil = 1;
			*deltaCol = 0;
		break;
		
		case 315:
			*deltaFil = 1;
			*deltaCol = 1;
		break;
	}
}

