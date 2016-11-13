#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "buttonsAndScissorsBack.h"
#include "buttonsAndScissorsFront.h"
#include "BackTestSuite.h"

static void cargarTablero(tablero* t, char orig[][5])
{
	int i,j;
	t->tab=malloc(sizeof(char*)*t->dim);
	for(i=0;i<t->dim;i++)
	{
		t->tab[i]=malloc(sizeof(char)*t->dim);
		for(j=0;j<t->dim;j++)
			t->tab[i][j]=orig[i][j];
	}
}

void hayGanadorTest(CuTest * cuTest)
{
	tablero t;
	t.dim=5;
	
	char tprueba1[5][5]={{'0','0','0','0','0'},{'0','0','0','0','0'},{'0','0','0','0','0'},{'0','0','0','0','0'},{'0','0','0','0','0'}};
	cargarTablero(&t,tprueba1);
	int actual = hayGanador(t);
	int esperado = 1;
	CuAssertIntEquals_Msg(cuTest,"Deberia haber ganador, pues el tablero esta vacio.\n", esperado, actual);
	
	char tprueba2[5][5]={{'0','A','0','0','0'},{'0','0','A','0','0'},{'0','0','0','A','0'},{'0','0','0','0','0'},{'0','0','0','0','0'}};
	cargarTablero(&t,tprueba2);
	actual = hayGanador(t); 
	esperado = 0;
	CuAssertIntEquals_Msg(cuTest,"No deberia haber ganador, pues hay jugadas validas.\n", esperado, actual);
	
	char tprueba3[5][5]={{'A','B','B','0','D'},{'D','0','A','B','0'},{'C','D','A','B','D'},{'C','B','E','A','D'},{'E','E','E','D','A'}};
	cargarTablero(&t,tprueba3);
	actual = hayGanador(t); 
	esperado = 0;
	CuAssertIntEquals_Msg(cuTest,"No deberia haber ganador, pues hay jugadas validas.\n", esperado, actual);
	
	char tprueba4[5][5]={{'0','A','C','0','0'},{'0','0','B','0','0'},{'0','0','D','A','0'},{'D','0','0','0','0'},{'0','B','0','D','0'}};
	cargarTablero(&t,tprueba4);
	actual = hayGanador(t); 
	esperado = 1;
	CuAssertIntEquals_Msg(cuTest,"Deberia haber ganador, pues no hay jugadas validas.\n", esperado, actual);
	
}



void EfectuarCorteTest(CuTest * cuTest) 
{
	//int EfectuarCorte(TipoTablero tablero, movimiento * mov)
	
	tablero t;
	t.dim = 5;
	movimiento mov;
	
	char tprueba1[5][5]={{'0','A','0','0','B'},{'0','0','0','0','D'},{'0','0','B','0','0'},{'0','B','D','C','A'},{'B','0','0','0','0'}};
	cargarTablero(&t,tprueba1);
	mov.inicio.fila = 4;
	mov.inicio.columna = 0;
	mov.final.fila = 0;
	mov.final.columna = 4;
	mov.direccion = 45;
	mov.deltaFil = -1;
	mov.deltaCol = 1;
	int actual = EfectuarCorte(t.tab, &mov);
	int esperado = 4;
	char * mensaje = "Los valores de respuesta no coinciden";
	CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);

	char tprueba2[5][5]={{'0','A','C','C','B'},{'0','0','0','0','D'},{'0','0','B','0','0'},{'0','B','D','C','A'},{'B','0','0','0','0'}};
	cargarTablero(&t,tprueba2);
	mov.inicio.fila = 0;
	mov.inicio.columna = 2;
	mov.final.fila = 0;
	mov.final.columna = 3;
	mov.direccion = 0;
	mov.deltaFil = 0;
	mov.deltaCol = 1;
	actual = EfectuarCorte(t.tab, &mov);
	esperado = 2;
	mensaje = "Los valores de respuesta no coinciden";
	CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
	
	char tprueba3[5][5]={{'A','B','0','B','D'},{'D','0','A','B','0'},{'C','D','A','B','D'},{'C','B','E','A','D'},{'E','E','E','D','A'}};
	cargarTablero(&t,tprueba3);
	mov.inicio.fila = 2;
	mov.inicio.columna = 3;
	mov.final.fila = 0;
	mov.final.columna = 3;
	mov.direccion = 90;
	mov.deltaFil = -1;
	mov.deltaCol = 0;
	actual = EfectuarCorte(t.tab, &mov);
	esperado = 3;
	mensaje = "Los valores de respuesta no coinciden";
	CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
	
}



void JugadaValidaTest(CuTest * cuTest) 
{
	tablero t;
	t.dim = 5;
	movimiento mov;
	int error;
	char tprueba1[5][5]={{'0','A','0','0','0'},{'0','0','0','B','D'},{'0','0','B','A','0'},{'0','C','D','C','A'},{'B','0','0','0','0'}};
	cargarTablero(&t,tprueba1);
	
	mov.inicio.fila = 0;
	mov.inicio.columna = 1;
	mov.final.fila = 3;
	mov.final.columna = 4;
	int actual = JugadaValida(&t, &mov, &error);
	int esperado = 315;
	char *mensaje = "Los valores de respuesta no coinciden";
	CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
	
	mov.inicio.fila = 5;
	mov.inicio.columna = 0;
	mov.final.fila = 1;
	mov.final.columna = 3;
	actual = JugadaValida(&t, &mov, &error);
	esperado = -1;
	mensaje = "Los valores de respuesta no coinciden";
	CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
	
	mov.inicio.fila = 4;
	mov.inicio.columna = 0;
	mov.final.fila = 1;
	mov.final.columna = 3;
	actual = JugadaValida(&t, &mov, &error);
	esperado = -1;
	mensaje = "Los valores de respuesta no coinciden";
	CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
	
	mov.inicio.fila = 2;
	mov.inicio.columna = 2;
	mov.final.fila = 1;
	mov.final.columna = 3;
	actual = JugadaValida(&t, &mov, &error);
	esperado = 45;
	mensaje = "Los valores de respuesta no coinciden";
	CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
}

CuSuite * BackTestSuite()
{
	CuSuite * cuSuite = CuSuiteNew();
	SUITE_ADD_TEST(cuSuite, hayGanadorTest);
	SUITE_ADD_TEST(cuSuite, EfectuarCorteTest);
	SUITE_ADD_TEST(cuSuite, JugadaValidaTest);
	return cuSuite;
}



