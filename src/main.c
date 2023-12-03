#include <stdio.h>
#include <stdlib.h>

#include "../include/utilidades.h" //Ruta relativa
#include "../include/utilidades.c" //Ruta relativa
#include "menu.h" //Ruta relativa
#include "menu.c" //Ruta relativa

int main(void) {
    limpiarConsola();
    menu();
    continuar();
    printf("\nPrograma terminado.\n\n");
    return 0;
}
