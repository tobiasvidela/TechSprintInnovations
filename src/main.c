#include <stdio.h>
#include <stdlib.h>

void limpiarConsola() {
    #ifdef __unix__  // Unix/Linux/MacOS
        system("clear");
    #else _WIN32  // Windows
        system("cls");
    #endif
}

void limpiarBuffers() {
    fflush(stdout);//  Vaciar el búfer de salida
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

int main(int argc, char const *argv[]) {
    limpiarConsola();
    continuar();
    printf("\nPrograma terminado.\n\n");
    return 0;
}
