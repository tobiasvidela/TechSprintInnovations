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
    scanf("%*[^\n]%*c");
    /* se le dice a scanf primero que ignore (uso de *) cualquier número de no 
    caracteres en blanco (distinto a tabulador '\t', espacio ' ' o salto de línea '\n') 
    con el especificador %*[^\n] hasta que encuentre un carácter en blanco (el salto de línea),
    en cuyo caso lo ignora con el %*c. */
}

void continuar() {
    printf("\nPresiona Enter para continuar...");
    limpiarBuffers();
    getchar();//  Esperar a que el usuario presione Enter
}
