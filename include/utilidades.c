#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __unix__
    #include <sys/ioctl.h>
    #include <unistd.h>
#else
    #include <windows.h>
#endif

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
  /* "se le dice a scanf primero que ignore (uso de *) cualquier número de no 
  caracteres en blanco (distinto a tabulador '\t', espacio ' ' o salto de línea '\n') 
  con el especificador %*[^\n] hasta que encuentre un carácter en blanco (el salto de línea),
  en cuyo caso lo ignora con el %*c."
  Source: https://es.stackoverflow.com/a/81435
  */
}

void continuar() {
  printf("\nPresiona Enter para continuar...");
  limpiarBuffers();
  getchar();//  Esperar a que el usuario presione Enter
}

int LeerEntero() {
  int entero, control;
  do {
    if (scanf("%d", &entero) != 1){
      limpiarBuffers();
      control = 1;
    } else {
      control = 0;
    }
  } while (control);
  return entero;
}

float LeerFlotante() {
  float numero;
  int control;
  do {
    if (scanf("%f", &numero) != 1) {
      limpiarBuffers();
      control = 1;
    } else {
      control = 0;
    }
  } while (control);
  return numero;
}

void imprimirCadenaCentrada(const char *cadena) {
  int ancho_consola;
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        ancho_consola = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    #else
        struct winsize size;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        ancho_consola = size.ws_col;
    #endif

    int longitud_texto = strlen(cadena);
    int espacios = (ancho_consola - longitud_texto) / 2;

    for (int i = 0; i < espacios; ++i) {
        putchar(' ');
    }
    printf("%s\n", cadena);
}