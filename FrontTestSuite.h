#ifndef Front_Test_Suite_H
#define Front_Test_Suite_H

void lecturaTableroInicialTest(CuTest * cuTest);
void CargarArchivoTest(CuTest * cuTest);
void GuardarTest(CuTest * cuTest);
void LeerComandoTest(CuTest * cuTest);
void GenerarNombreTest(CuTest * cuTest);
CuSuite * FrontTestSuite(void);

#endif