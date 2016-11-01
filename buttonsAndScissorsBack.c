#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BLOQUE 10
typedef struct 
{
	int fila ;
	int columna ;
}tCoordenada ;
typedef struct
{
	tCoordenada inicio ;
	tCoordenada final ;
}movimiento ;
typedef struct 
{
	char tab[5][5] ;
	int dim ;
}tablero;
/*Busca botones del mismo tipo al inicial en la direccion de los incrementos y devuelve en su nombre la cantidad de blancos*/ 
int buscdir(tablero t,int modo,int fila,int columna,int incfil,int inccol,int *botones)
{
	*botones=1 ;
	int seguir=1,blancos=0 ;
	char boton=(t.tab)[fila][columna] ;
	while(seguir)
	{
		fila+=incfil ;
		columna+=inccol ;
		if(fila>=t.dim||fila<0||columna>=t.dim||columna<0||(((t.tab)[fila][columna]!=boton)&&((t.tab)[fila][columna]!=' ')))
			seguir=0 ;
		else if(modo==1&&(*botones)==2)
			seguir=0 ;
		else if((t.tab)[fila][columna]==boton)
			(*botones)++ ;
		else
			blancos++ ;
	}
	return blancos ;
}
/*Elije al azar una de las dos estrategias(maxima cantidad de botones y minima cantidad de botes) y elige el movimiento aleatoriamente de todos los posibles*/
void JugarAi(tablero* t,int *puntos)
{
	int direcciones[4][2]={{-1,0},{-1,1},{0,1},{1,1}} ;
	int i,j,k,cant=0,botones,dimension=0,maximo=2,modo=rand()%2 ;
	movimiento * cortes=NULL,*aux,resp ;
	for(i=0;i<t->dim;i++)
	{
		for(j=0;j<t->dim;j++)
		{
			if((t->tab)[i][j]!=' ')
			{for(k=0;k<4;k++)
				{
					if(modo==0)
					{
						blancos=buscdir(*t,modo,i,j,direcciones[k][0],direcciones[k][1],&botones) ;
						if(botones>=maximo)
						{
							if(botones>maximo)
							{
								maximo=botones ;
								dimension=0 ;
							}

						}
						else
							botones=0 ;
					}
					else
						{
							blancos=buscdir(*t,modo,i,j,direcciones[k][0],direcciones[k][1],&botones) ;
							if(botones!=2)
								botones=0 ;
						}
					if(botones)
					{
						if(cant%BLOQUE==0)
						{
							aux=realloc(cortes,(cant+BLOQUE)*sizeof(*cortes)) ;
							if(aux!=NULL)
							{
								cortes=aux ;
							}
							else exit(0) ;
						}
						cortes[dimension].inicio.fila=i ;
						cortes[dimension].inicio.columna=j ;
						cortes[dimension].final.fila=i+direcciones[k][0]*(botones-1+blancos) ;
						cortes[dimension].final.columna=j+direcciones[k][1]*(botones-1+blancos) ;
						dimension++ ;
						if(dimension>cant)
							cant=dimension ;
					}

				}	
			}
		}
	}
	cortes=realloc(cortes,sizeof(*cortes)*dimension) ;
	resp=cortes[rand()%dimension] ;
	//*puntos=*puntos+efectuar_corte(resp);
}

