int Menu();
void ImprimirMenu();

int Menu(){
    ImprimirMenu();
    int opcion=LeerOpcion();
}

void ImprimirMenu(){
    printf("MENÚ DEL JUEGO:\n");
    printf("1. Juego de dos jugadores\n");
    printf("2. Juego contra computadora\n");
    printf("3. Recuperar un juego grabado\n");
    printf("4. Terminar\n");
}
