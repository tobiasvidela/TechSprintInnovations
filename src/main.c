#include <stdio.h>
#include <stdlib.h>

void limpiarConsola() {
    #ifdef __unix__  // Unix/Linux/MacOS
        system("clear");
    #else _WIN32  // Windows
        system("cls");
    #endif
}

int main(int argc, char const *argv[]) {
    limpiarConsola();
    printf("\nPrograma terminado.\n\n");
    return 0;
}
