#include <stdio.h>
#include <stdlib.h>

#include "utilidades.h" //Ruta relativa

void limpiarConsola() {
    #ifdef __unix__  // Unix/Linux/MacOS
        system("clear");
    #else   // Windows
        system("cls");
    #endif
}

void limpiarBuffers() {
    fflush(stdout);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        //  Descartar caracteres restantes en el búfer de entrada
    }
}

void continuar() {
    printf("\nPresiona Enter para continuar...");
    limpiarBuffers();
    getchar();//  Esperar a que el usuario presione Enter
}
