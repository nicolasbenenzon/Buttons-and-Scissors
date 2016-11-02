#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "buttonsAndScissorsBack.h"
#define BLOQUE 10
/*typedef struct 
{
	char tab[5][5];
	int dim;
}tablero;*/
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
		if(fila>=t.dim||fila<0||columna>=t.dim||columna<0||(((t.tab)[fila][columna]!=boton)&&((t.tab)[fila][columna]!=' ')))
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
void imprimircortes(movimiento* cortes,int dim)
{
	int i;
	for(i=0;i<dim;i++)
	{
			printf("fila1=%d\tcolumna1=%d\n",cortes[i].inicio.fila,cortes[i].inicio.columna);
			printf("fila2=%d\tcolumna2=%d\n",cortes[i].final.fila,cortes[i].final.columna);
			printf("\n\n");
	}
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
			if((t->tab)[i][j]!=' ')
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
	//*puntos=*puntos+efectuar_corte(resp);
	imprimircortes(cortes,dimension);

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
			if((t.tab)[i][j]!=' ')
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

void imprimir(tablero tabjuego)
{
	int i,j;
	
	
		for(i=0;i<2;i++)
		{
			printf("\t");
			for(j=0;j<tabjuego.dim;j++)
			{
				if(i==0)
				{
					if(j<10)
						printf("%d  ",j);
					else
						printf("%d ",j);
				}
				else
					printf("---");
			}
			printf("\n");
		}
		for(i=0;i<tabjuego.dim;i++)
		{
				if(tabjuego.dim<10)
					printf("%d|\t",i);
				else
				{
					if(i<10)
						printf("%d |\t",i);
					else
						printf("%d|\t",i);
				}
			for(j=0;j<tabjuego.dim;j++)
			{
					printf("%c  ",(tabjuego.tab)[i][j]);
			}
			printf("\n");
		}
		printf("\n\n");
}

/*int main(void)
{
	srand(time(NULL));
	tablero t={{{'A','B','B',' ','D'},{'D',' ','A','B',' '},{'C','D','A','B','D'},{'C','B','E','C','D'},{'E','E','E','D','A'}},5};
	//tablero t={{{'A','B','A','C','D'},{'D','B','A','C','E'},{'C','D','A','E','D'},{'C','B','E','C','E'},{'E','E','E','D','A'}},5};
	int puntos=0;
	imprimir(t);
	JugarAi(&t,&puntos);
	return 0;
}*/
int main(void)
{
	tablero t={{{' ',' ',' ',' ',' '},{' ',' ',' ',' ',' '},{' ',' ',' ',' ',' '},{' ',' ',' ',' ',' '},{' ',' ',' ',' ',' '}},5};
	imprimir(t);
	/*int puntos;
	jugarAi(&t,&puntos);
	*/
	printf("%d\n",hayGanador(t));
	return 0;
}