#include <stdio.h>
#include "buttonsAndScissorsBack.h"
#include "CuTest.h"

void JugadaValidaTest(CuTest * cuTest);
void EfectuarCorteTest(CuTest * cuTest);

CuSuite * 
BackTestSuite(void) 
{
	CuSuite * cuSuite = CuSuiteNew();
	SUITE_ADD_TEST(cuSuite, JugadaValidaTest);
	SUITE_ADD_TEST(cuSuite, EfectuarCorteTest);
	return cuSuite;
}

void 
JugadaValidaTest(CuTest * cuTest) 
{
	tablero t;
	movimiento mov;
	int error;
	
	t.tab = malloc(5 * sizeof(char*));
	for(int i = 0; i < 5; i++)
	{
		t.tab[i] = malloc(5);
	}
	t.tab[0][0] = '0'; t.tab[0][1] = 'A'; t.tab[0][2] = '0'; t.tab[0][3] = '0'; t.tab[0][4] = '0';
	t.tab[1][0] = '0'; t.tab[1][1] = '0'; t.tab[1][2] = '0'; t.tab[1][3] = 'B'; t.tab[1][4] = 'D';
	t.tab[2][0] = '0'; t.tab[2][1] = '0'; t.tab[2][2] = 'B'; t.tab[2][3] = '0'; t.tab[2][4] = '0';
	t.tab[3][0] = '0'; t.tab[3][1] = 'C'; t.tab[3][2] = 'D'; t.tab[3][3] = 'C'; t.tab[3][4] = 'A';
	t.tab[4][4] = 'B'; t.tab[4][1] = '0'; t.tab[4][2] = '0'; t.tab[4][3] = '0'; t.tab[4][4] = '0';
	
	t.dim = 5;
	mov.inicio.fila = 0;
	mov.inicio.columna = 0;
	mov.final.fila = 4;
	mov.final.columna = 4;
	int actual = JugadaValida(&t, &mov, &error);
	int esperado = 0;
	char * mensaje = "Los valores de respuesta no coinciden";
	CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
}

void 
EfectuarCorteTest(CuTest * cuTest) 
{
	//int EfectuarCorte(TipoTablero tablero, movimiento * mov)
	
	TipoTablero tablero;
	movimiento mov;
	tablero = malloc(5 * sizeof(char*));
	for(int i = 0; i < 5; i++)
	{
		tablero[i] = malloc(5);
	}
	tablero[0][0] = '0'; tablero[0][1] = 'A'; tablero[0][2] = '0'; tablero[0][3] = '0'; tablero[0][4] = 'B';
	tablero[1][0] = '0'; tablero[1][1] = '0'; tablero[1][2] = '0'; tablero[1][3] = '0'; tablero[1][4] = 'D';
	tablero[2][0] = '0'; tablero[2][1] = '0'; tablero[2][2] = 'B'; tablero[2][3] = '0'; tablero[2][4] = '0';
	tablero[3][0] = '0'; tablero[3][1] = 'B'; tablero[3][2] = 'D'; tablero[3][3] = 'C'; tablero[3][4] = 'A';
	tablero[4][4] = 'B'; tablero[4][1] = '0'; tablero[4][2] = '0'; tablero[4][3] = '0'; tablero[4][4] = '0';
	
	mov.inicio.fila = 4;
	mov.inicio.columna = 0;
	mov.final.fila = 0;
	mov.final.columna = 4;
	mov.direccion = 45;
	mov.deltaFil = -1;
	mov.deltaCol = 1;
	
	int actual = EfectuarCorte(tablero, &mov);
	int esperado = 4;
	char * mensaje = "Los valores de respuesta no coinciden";
	CuAssertIntEquals_Msg(cuTest, mensaje, esperado, actual);
}
