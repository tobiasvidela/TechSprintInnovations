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


int leerEntero() {
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

float leerFloat() {
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

void imprimirCadenaCentrada(char *cadena, int ancho) {
  int longitudCadena = strlen(cadena);
  int espacios = (ancho - longitudCadena) / 2;
  int margenIzq = espacios;
  int margenDer = espacios;

  if ((ancho - longitudCadena) % 2 != 0) {margenDer++;}

  printf("%*s%s%*s",margenIzq,"",cadena,margenDer,"");
}