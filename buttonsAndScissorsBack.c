#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "buttonsAndScissorsBack.h"
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
void jugarAi(tablero* t,int *puntos)
{
	int direcciones[4][2]={{-1,0},{-1,1},{0,1},{1,1}};
	int i,j,k,cant=0,botones,dimension=0,maximo=2,modo=rand()%2,blancos;
	movimiento * cortes=NULL,*aux,resp;
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
							aux=realloc(cortes,(cant+BLOQUE)*sizeof(*cortes));
							if(aux!=NULL)
							{
								cortes=aux;
							}
							else exit(0);
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
	cortes=realloc(cortes,sizeof(*cortes)*dimension);
	resp=cortes[rand()%dimension];
	resp.direccion=DireccionCorte(&resp);
	CalcularDeltasFilCol(&resp);
	printf("fila1=%d\tcolumna1=%d\nfila2=%d\tcolumna2=%d\n",resp.inicio.fila,resp.inicio.columna,resp.final.fila,resp.final.columna);
	*puntos=*puntos+EfectuarCorte(t->tab,&resp);
	
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
	int botonesCortados = 2; //Lo inicializo en 2 porque de entrada corto los botones de origen y destino
	
	//Corto los botones de inicio y final
	tabler[(mov -> inicio).fila][(mov -> inicio).columna] = '0';
	tabler[(mov -> final).fila][(mov -> final).columna] = '0';
	
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