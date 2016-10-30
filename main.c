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

typedef char * TipoLinea;
typedef TipoLinea * TipoTablero;
typedef struct
{
	int fila;
	int columna;
}tCoordenada;

int JugadaValida(TipoTablero tablero, tCoordenada origen, tCoordenada destino, int dim);
int ExistePosicion(tCoordenada coordenada, int dim);
int EstaVacio(TipoTablero tablero, tCoordenada coordenada);
int DireccionCorte(tCoordenada origen, tCoordenada destino);
int HayOtrasVariedades(TipoTablero tablero, tCoordenada origen, tCoordenada destino, int direccion);
int EfectuarCorte(TipoTablero tablero, tCoordenada origen, tCoordenada destino, int direccion);
void CalcularDeltasFilCol(int direccion, int * deltaFil, int * deltaCol);
void ReportarErrorPosicion(tCoordenada coordenada);
void ReportarErrorEspacioVacio(tCoordenada coordenada);
void ReportarErrorLineaRecta();
void ReportarErrorVariedades();

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
		for(j = 0; j < DIM; j++)
		{
			tablero[i][j] = randInt(0, 4) + 'A';
			printf("%c ", tablero[i][j]);
		}
		putchar('\n');
	}
	//tCoordenada origen = {0, 0};
	//tCoordenada destino = {2,0};
	//int cortes = JugadaValida(tablero, origen, destino, DIM);
	#ifdef DEBUG
		tablero[0][0] = '0'; tablero[0][1] = 'A'; tablero[0][2] = '0'; tablero[0][3] = '0'; tablero[0][4] = '0';
		tablero[1][0] = '0'; tablero[1][1] = '0'; tablero[1][2] = '0'; tablero[1][3] = 'B'; tablero[1][4] = 'D';
		tablero[2][0] = '0'; tablero[2][1] = '0'; tablero[2][2] = 'B'; tablero[2][3] = '0'; tablero[2][4] = '0';
		tablero[3][0] = '0'; tablero[3][1] = 'C'; tablero[3][2] = 'D'; tablero[3][3] = 'C'; tablero[3][4] = 'A';
		tablero[4][0] = 'B'; tablero[4][1] = '0'; tablero[4][2] = '0'; tablero[4][3] = '0'; tablero[4][4] = '0';
		tCoordenada origen = {3,2};
		tCoordenada destino = {1,4};
		int existe = JugadaValida(tablero, origen, destino, DIM);
		printf("%d\n", existe);
		for(i = 0; i < DIM; i++)
		{
			for(j = 0; j < DIM; j++)
			{
				printf("%c ", tablero[i][j]);
			}
			putchar('\n');
		}
		
	
	#endif
	return 0;
}

int JugadaValida(TipoTablero tablero, tCoordenada origen, tCoordenada destino, int dim)
{
	int botonesCortados = 0, direccion = -1;
	
	//Verifico que exista la posición de origen, en caso negativo reporta el error y retorna 0
	if(ExistePosicion(origen, dim))
	{
		//En caso de existir la posición de origen, ahora verifico si existe la posición de destino, en caso negativo reporta el error y retorna 0
		if(ExistePosicion(destino, dim))
		{
			//Ahora verifico que tanto en el origen como en el destino haya algún botón, en caso negativo reporta el error y retorna 0
			if(!EstaVacio(tablero, origen) && !EstaVacio(tablero, destino))
			{
				//Luego verifico si el corte determinado por el origen y el destino forma efectivamente una línea recta
				if((direccion = DireccionCorte(origen, destino)) != -1)
				{
					//Finalmente, se valida que no haya otras variedades de botones en esa dirección
					if(! HayOtrasVariedades(tablero, origen, destino, direccion))
					{
						//En caso de haber cumplido con todos los requisitos, se efectúa el corte y guarda la cantidad de botones cortados
						botonesCortados = EfectuarCorte(tablero, origen, destino, direccion);
					}
					else
					{
						ReportarErrorVariedades(); //Como hay más de una variedad de botones en esa dirección, reporta el error
					}
				}
				else
				{
					ReportarErrorLineaRecta(); //Como el origen y destino no forman una línea recta, reporta el error
				}
			}
			else
			{
				//Si alguno de las 2 coordenadas es un espacio vacio entonces ve cuál es y reporta el error
				if(EstaVacio(tablero, origen)) ReportarErrorEspacioVacio(origen);
				else ReportarErrorEspacioVacio(destino);
			}
		}
		else
		{
			ReportarErrorPosicion(destino); //Como no existe la posición de destino, reporta el error
		}
	}
	else
	{
		ReportarErrorPosicion(origen); //Como no existe la posición de origen, reporta el error
	}
	
	return botonesCortados;
}

int ExistePosicion(tCoordenada coordenada, int dim)
{
	return (coordenada.fila >= 0 && coordenada.fila < dim && coordenada.columna >= 0 && coordenada.columna < dim);
}

int EstaVacio(TipoTablero tablero, tCoordenada coordenada)
{
	return (tablero[coordenada.fila][coordenada.columna] == '0');
}

int DireccionCorte(tCoordenada origen, tCoordenada destino)
{
	if(origen.fila == destino.fila) //Si ambos están en la misma fila
	{
		if(origen.columna < destino.columna) //Si el destino está a la derecha del origen
			return 0;
		else 
			if(origen.columna > destino.columna) //Si el destino está a la izquierda del origen
				return 180;
	}
	else if(origen.columna == destino.columna) //Si están en la misma columna
	{
		if(origen.fila < destino.fila) //Si el destino está por debajo del origen
			return 270;
		return 90; //El destino está por encima del origen
	}
	//Si no se cumplieron las condiciones anteriores, ahora se fija por las diagonales
	else if(abs(origen.fila - destino.fila) == abs(origen.columna - destino.columna))
	{
		//Si se forma una línea recta en diagonal, entonces retorna la respectiva dirección
		if(origen.fila > destino.fila)
		{
			if(origen.columna < destino.columna)
				return 45;
			return 135;
		}
		if(origen.columna < destino.columna)
			return 315;
		return 225;
	}
	return -1; //En caso de no haber cumplido ninguna condición, significa que no forma una línea recta y retorna -1
}

int HayOtrasVariedades(TipoTablero tablero, tCoordenada origen, tCoordenada destino, int direccion)
{
	int fil, col, deltaFil, deltaCol, hayBotonDistinto = 0;
	char botonOrigen = tablero[origen.fila][origen.columna]; //Guardo el botón que está en origen
	char botonDestino = tablero[destino.fila][destino.columna]; //Guardo el botón que está en destino
	
	//Primero verifico que en origen y destino haya el mismo botón, porque si son distintos, no tiene sentido recorrer todo el camino, ya se sabe que las variedades son distintas
	if(botonOrigen == botonDestino)
	{
		//Calculo el sentido en que hago el recorrido, y recorro
		CalcularDeltasFilCol(direccion, &deltaFil, &deltaCol);
		for(fil = origen.fila + deltaFil, col = origen.columna + deltaCol; fil != destino.fila && col != destino.columna && !hayBotonDistinto; fil += deltaFil, col += deltaCol)
		{
			if(tablero[fil][col] != botonOrigen && tablero[fil][col] != '0')
				hayBotonDistinto = 1;
		}
		return hayBotonDistinto;
	}
	else 
		return 1; //Si el destino y el origen tienen distintos botones, retorno 1
}

int EfectuarCorte(TipoTablero tablero, tCoordenada origen, tCoordenada destino, int direccion)
{
	int fil, col, deltaFil, deltaCol;
	int botonesCortados = 2; //Lo inicializo en 2 porque de entrada corto los botones de origen y destino
	
	//Corto los botones de origen y destino
	tablero[origen.fila][origen.columna] = '0';
	tablero[destino.fila][destino.columna] = '0';
	
	//Calculo el sentido en que hago el corte, y corto contando la cantidad de botones cortados
	CalcularDeltasFilCol(direccion, &deltaFil, &deltaCol);
	for(fil = origen.fila + deltaFil, col = origen.columna + deltaCol; fil != destino.fila && col != destino.columna; fil += deltaFil, col += deltaCol)
	{
		//Si hay un botón en esa posición, lo corta e incrementa la variable de botones cortados
		if(tablero[fil][col] != '0')
		{
			tablero[fil][col] = '0';
			botonesCortados++;
		}
	}
	
	return botonesCortados;
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

void ReportarErrorPosicion(tCoordenada coordenada)
{
	printf("Error: No existe la posición [%d,%d]\n", coordenada.fila, coordenada.columna);
}

void ReportarErrorEspacioVacio(tCoordenada coordenada)
{
	printf("Error: La posición [%d,%d] no tiene ningún botón\n", coordenada.fila, coordenada.columna);
}

void ReportarErrorLineaRecta()
{
	printf("Error: El corte no forma una línea recta\n");
}

void ReportarErrorVariedades()
{
	printf("Error: El corte no tiene una única variedad de botones\n");
}



