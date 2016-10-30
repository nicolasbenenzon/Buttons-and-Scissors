#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BLOQUE 10
typedef struct 
{
	int fila;
	int columna;
}tCoordenada;
typedef struct
{
	tCoordenada inicio;
	tCoordenada final;
}movimiento;
typedef struct 
{
	char tab[5][5];
	int dim;
}tablero;
/*Busca botones del mismo tipo al inicial en la direccion de los incrementos y devuelve la cantidad*/ 
int buscdir(tablero t,int modo,int fila,int columna,int incfil,int inccol)
{
	int seguir=1,botones=1;
	char boton=(t.tab)[fila][columna];
	while(seguir)
	{
		fila+=incfil;
		columna+=inccol;
		if(fila>=t.dim||fila<0||columna>=t.dim||columna<0||(t.tab)[fila][columna]!=boton)
			seguir=0;
		else if(modo==1&&botones==2)
			seguir=0;
		else
			botones++;
	}
	return botones;
}
/*Elije al azar una de las dos estrategias(maxima cantidad de botones y minima cantidad de botes) y elige el movimiento aleatoriamente de todos los posibles*/
void JugarAi(tablero* t,int *puntos)
{
	int direcciones[4][2]={{-1,0},{-1,1},{0,1},{1,1}};
	int i,j,k,cant=0,botones,dimension=0,maximo=2,modo=rand()%2;
	movimiento * cortes=NULL,*aux,resp;
	for(i=0;i<t->dim;i++)
	{
		for(j=0;j<t->dim;j++)
		{
			for(k=0;k<4;k++)
			{
				if(modo==0)
				{
					if((botones=buscdir(*t,modo,i,j,direcciones[k][0],direcciones[k][1]))>=maximo)
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
						if(buscdir(*t,modo,i,j,direcciones[k][0],direcciones[k][1])==2)
							botones=2;
						else
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
					cortes[dimension].final.fila=i+direcciones[k][0]*(botones-1);
					cortes[dimension].final.columna=j+direcciones[k][1]*(botones-1);
					dimension++;
					if(dimension>cant)
						cant=dimension;
				}
			}	
		}
	}
	cortes=realloc(cortes,sizeof(*cortes)*dimension);
	resp=cortes[rand()%dimension];
	//*puntos=*puntos+efectuar_corte(resp);
}

