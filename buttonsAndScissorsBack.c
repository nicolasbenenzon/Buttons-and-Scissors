#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "buttonsAndScissorsBack.h"
#include "rand.h"
#define BLOQUE 10
/*Busca botones del mismo tipo al inicial en la direccion de los incrementos y devuelve en su nombre la cantidad de blancos*/ 
int buscdir(tablero t,int modo,int fila,int columna,int incfil,int inccol,int *botones)
{
	*botones=1;
	int seguir=1,blancos=0;
	char boton=(t.tab)[fila][columna];
	while(seguir)
	{
		fila+=incfil;
		columna+=inccol;
		if(fila>=t.dim||fila<0||columna>=t.dim||columna<0||(((t.tab)[fila][columna]!=boton)&&((t.tab)[fila][columna]!='0')))
			seguir=0;
		else if(modo==1&&(*botones)==2)
			seguir=0;
		else if((t.tab)[fila][columna]==boton)
			(*botones)++;
		else
			blancos++;
	}
	return blancos;
}

/*Elije al azar una de las dos estrategias(maxima cantidad de botones y minima cantidad de botes) y elige el movimiento aleatoriamente de todos los posibles*/
int jugarAi(tablero* t,int *puntos)
{
	int direcciones[4][2]={{-1,0},{-1,1},{0,1},{1,1}};
	int i,j,k,cant=0,botones,dimension=0,maximo=2,modo=randInt(0,1),blancos;
	movimiento * cortes=NULL,resp;
	for(i=0;i<t->dim;i++)
	{
		for(j=0;j<t->dim;j++)
		{
			if((t->tab)[i][j]!='0')
			{for(k=0;k<4;k++)
				{
					if(modo==0)
					{
						blancos=buscdir(*t,modo,i,j,direcciones[k][0],direcciones[k][1],&botones);
						if(botones>=maximo)
						{
							if(botones>maximo)
							{
								maximo=botones;
								dimension=0;
							}

						}
						else
							botones=0;
					}
					else
						{
							blancos=buscdir(*t,modo,i,j,direcciones[k][0],direcciones[k][1],&botones);
							if(botones!=2)
								botones=0;
						}
					if(botones)
					{
						if(cant%BLOQUE==0)
						{
							if(validarMemoria((void**)&cortes,(cant+BLOQUE)*sizeof(*cortes)))
								return 1;
						}
						cortes[dimension].inicio.fila=i;
						cortes[dimension].inicio.columna=j;
						cortes[dimension].final.fila=i+direcciones[k][0]*(botones-1+blancos);
						cortes[dimension].final.columna=j+direcciones[k][1]*(botones-1+blancos);
						dimension++;
						if(dimension>cant)
							cant=dimension;
					}

				}	
			}
		}
	}
	
	if(validarMemoria((void**)&cortes,sizeof(*cortes)*dimension))
		return 1;
	resp=cortes[randInt(0,dimension-1)];
	free(cortes);
	resp.direccion=DireccionCorte(&resp);
	CalcularDeltasFilCol(&resp);
	*puntos=*puntos+EfectuarCorte(t->tab,&resp);
	return 0;
}

/*Devuelve 1 si no hay mas jugadas posibles para el jugador siguiente y 0 en caso contrario*/
int hayGanador(tablero t)
{
	int direcciones[4][2]={{-1,0},{-1,1},{0,1},{1,1}};
	int i,j,k,botones;
	for(i=0;i<t.dim;i++)
	{
		for(j=0;j<t.dim;j++)
		{
			if((t.tab)[i][j]!='0')
			{
				for(k=0;k<4;k++)
				{
					buscdir(t,1,i,j,direcciones[k][0],direcciones[k][1],&botones);
					if(botones==2)
						return 0;
				}
			}
		}
	}
	return 1;
}


int DireccionCorte(movimiento * mov)
{
	if((mov -> inicio).fila == (mov -> final).fila) //Si ambos están en la misma fila
	{
		if((mov -> inicio).columna < (mov -> final).columna) //Si el final está a la derecha del inicio
			return 0;
		else 
			if((mov -> inicio).columna > (mov -> final).columna) //Si el final está a la izquierda del inicio
				return 180;
	}
	else if((mov -> inicio).columna == (mov -> final).columna) //Si están en la misma columna
	{
		if((mov -> inicio).fila < (mov -> final).fila) //Si el final está por debajo del inicio
			return 270;
		return 90; //El destino está por encima del origen
	}
	//Si no se cumplieron las condiciones anteriores, ahora se fija por las diagonales
	else if(abs((mov -> inicio).fila - (mov -> final).fila) == abs((mov -> inicio).columna - (mov -> final).columna))
	{
		//Si se forma una línea recta en diagonal, entonces retorna la respectiva dirección
		if((mov -> inicio).fila > (mov -> final).fila)
		{
			if((mov -> inicio).columna < (mov -> final).columna)
				return 45;
			return 135;
		}
		if((mov -> inicio).columna < (mov -> final).columna)
			return 315;
		return 225;
	}
	return -1; //En caso de no haber cumplido ninguna condición, significa que no forma una línea recta y retorna -1
}

int EfectuarCorte(TipoTablero tabler, movimiento * mov)
{
	int fil, col;
	int botonesCortados = 1; //Lo inicializo en 1 porque de entrada corto el boton de origen
	
	//Corto los botones de inicio y final
	tabler[(mov -> inicio).fila][(mov -> inicio).columna] = '0';
	if(tabler[(mov -> final).fila][(mov -> final).columna]!='0')//por si es llamado por la funcion AI en la cual la ultima cordenada puede ser '0'
	{	
		tabler[(mov -> final).fila][(mov -> final).columna] = '0';
		botonesCortados++;
	}
	
	//Calculo el sentido en que hago el corte, y corto contando la cantidad de botones cortados
	//CalcularDeltasFilCol(direccion, &deltaFil, &deltaCol);
	for(fil = (mov -> inicio).fila + mov -> deltaFil, col = (mov -> inicio).columna + mov -> deltaCol; fil != (mov -> final).fila || col != (mov -> final).columna; fil += mov -> deltaFil, col += mov -> deltaCol)
	{
		//Si hay un botón en esa posición, lo corta e incrementa la variable de botones cortados
		if(tabler[fil][col] != '0')
		{
			tabler[fil][col] = '0';
			botonesCortados++;
		}
	}
	
	return botonesCortados;
}

void CalcularDeltasFilCol(movimiento * mov)
{
	switch(mov -> direccion)
	{
		case 0:
			mov -> deltaFil = 0;
			mov -> deltaCol = 1;
		break;
		
		case 45:
			mov -> deltaFil = -1;
			mov -> deltaCol = 1;
		break;
		
		case 90:
			mov -> deltaFil = -1;
			mov -> deltaCol = 0;
		break;
		
		case 135:
			mov -> deltaFil = -1;
			mov -> deltaCol = -1;
		break;
		
		case 180:
			mov -> deltaFil = 0;
			mov -> deltaCol = -1;
		break;
		
		case 225:
			mov -> deltaFil = 1;
			mov -> deltaCol = -1;
		break;
		
		case 270:
			mov -> deltaFil = 1;
			mov -> deltaCol = 0;
		break;
		
		case 315:
			mov -> deltaFil = 1;
			mov -> deltaCol = 1;
		break;
	}
}	

/*Recibe la direccion de memoria del puntero al que quiero asignarle memoria y la cantidad de bytes que quiero asignarle*/
int validarMemoria(void **punt,unsigned int bytes)
{
	void *aux;
	aux=realloc(*punt,bytes);
	if(aux==NULL)
		return 1;
	*punt=aux;
	return 0;
}

/*Libera el Tablero*/
void liberarTablero(tablero * t)
{
	int i;
	for(i=0;i<t->dim;i++)
	{
		free(t->tab[i]);
	}
	free(t->tab);
}








int JugadaValida(tablero * t, movimiento * mov, int * error)
{
	mov -> direccion = -1;
	
	//Verifico que exista la posición de origen, en caso negativo reporta el error y retorna 0
	if(ExistePosicion(mov -> inicio, t -> dim))
	{
		//En caso de existir la posición de origen, ahora verifico si existe la posición de destino, en caso negativo reporta el error y retorna 0
		if(ExistePosicion(mov -> final, t -> dim))
		{
			//Ahora verifico que tanto en el origen como en el destino haya algún botón, en caso negativo reporta el error y retorna 0
			if(!EstaVacio(t -> tab, mov -> inicio) && !EstaVacio(t -> tab, mov -> final))
			{
				//Luego verifico si el corte determinado por el origen y el destino forma efectivamente una línea recta
				if((mov -> direccion = DireccionCorte(mov)) != -1)
				{
					//Finalmente, se valida que no haya otras variedades de botones en esa dirección
					if(! HayOtrasVariedades(t -> tab, mov))
					{
						//En caso de haber cumplido con todos los requisitos, se efectúa el corte y guarda la cantidad de botones cortados
						return mov -> direccion;
					}
					else
					{
						*error = 6;//Como hay más de una variedad de botones en esa dirección, reporta el error
					}
				}
				else
				{
					*error = 5;//Como el origen y destino no forman una línea recta, reporta el error
				}
			}
			else
			{
				//Si alguno de las 2 coordenadas es un espacio vacio entonces ve cuál es y reporta el error
				if(EstaVacio(t -> tab, mov -> inicio)) *error = 3;
				else *error = 4;
			}
		}
		else
		{
			//Como no existe la posición de destino, reporta el error
			*error = 2;
		}
	}
	else
	{
		//Como no existe la posición de origen, reporta el error
		*error = 1;
	}
	
	return -1;
}

int ExistePosicion(tCoordenada coordenada, int dim)
{
	return (coordenada.fila >= 0 && coordenada.fila < dim && coordenada.columna >= 0 && coordenada.columna < dim);
}

int EstaVacio(TipoTablero tablero, tCoordenada coordenada)
{
	return (tablero[coordenada.fila][coordenada.columna] == '0');
}

int HayOtrasVariedades(TipoTablero tablero, movimiento * mov)
{
	int fil, col, hayBotonDistinto = 0;
	char botonOrigen = tablero[(mov -> inicio).fila][(mov -> inicio).columna]; //Guardo el botón que está en inicio
	char botonDestino = tablero[(mov -> final).fila][(mov -> final).columna]; //Guardo el botón que está en final
	
	//Primero verifico que en inicio y final haya el mismo botón, porque si son distintos, no tiene sentido recorrer todo el camino, ya se sabe que las variedades son distintas
	if(botonOrigen == botonDestino)
	{
		//Calculo el sentido en que hago el recorrido(se guarda en deltaFil y deltaCol), y recorro
		CalcularDeltasFilCol(mov);
		for(fil = (mov -> inicio).fila + mov -> deltaFil, col = (mov -> inicio).columna + mov -> deltaCol; (fil != (mov -> final).fila || col != (mov -> final).columna) && !hayBotonDistinto; fil += mov -> deltaFil, col += mov -> deltaCol)
		{
			if(tablero[fil][col] != botonOrigen && tablero[fil][col] != '0')
				hayBotonDistinto = 1;
		}
		return hayBotonDistinto;
	}
	else 
		return 1; //Si el destino y el origen tienen distintos botones, retorno 1
}
