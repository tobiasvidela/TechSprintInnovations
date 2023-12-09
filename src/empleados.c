#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utilidades.h"
#include "empleados.h"


NodoEmpleado *EmpleadoPrimerNodo = NULL;
NodoEmpleado *EmpleadoUltimoNodo = NULL;

void cargarIDEmpleado(NodoEmpleado *nodoNuevo) {
  //  abrir el archivo
  FILE *empleados = fopen("../../data/empleados.dat","rb");
  //  si el archivo no existe
  if (empleados == NULL) {
    nodoNuevo->empleado.id = 1;
    //  si existen cargados en memoria
    if (EmpleadoUltimoNodo != NULL && nodoNuevo->empleado.id <= EmpleadoUltimoNodo->empleado.id) {
      //actualizar el id correctamente
      nodoNuevo->empleado.id = EmpleadoUltimoNodo->empleado.id + 1;
    }
    return;
  }
  //  si el archivo ya existe
  //  posicionar el puntero de lectura al inicio del último registro cargado
  fseek(empleados, -sizeof(Empleado), SEEK_END);
  //  leer el último registro cargado
  Empleado ultimo;
  fread(&ultimo, sizeof(Empleado), 1, empleados);
  fclose(empleados);
  nodoNuevo->empleado.id = ultimo.id + 1;
  if (EmpleadoUltimoNodo != NULL && nodoNuevo->empleado.id == EmpleadoUltimoNodo->empleado.id) {
    nodoNuevo->empleado.id = EmpleadoUltimoNodo->empleado.id + 1;
  }
  return;
}

void establecerSalarioBase(NodoEmpleado *empleadoNuevo) {
  switch(empleadoNuevo->empleado.cargo) {
    case VENDEDOR: {
      empleadoNuevo->empleado.salario = 5000;
      break;
    }
    case ASISTENTE: {
      empleadoNuevo->empleado.salario = 7500;
      break;
    }
    case SUPERVISOR: {
      empleadoNuevo->empleado.salario = 10000;
      break;
    }
    case GERENTE: {
      empleadoNuevo->empleado.salario = 15000;
      break;
    }
    default: {
      empleadoNuevo->empleado.salario = 1000;
      break;
    }
  }
}

void liberarMemoriaEmpleados() {
  NodoEmpleado *NodoActual = EmpleadoPrimerNodo;
  while (NodoActual != NULL) {
    NodoEmpleado *NodoAEliminar = NodoActual;
    NodoActual = NodoActual->siguiente;
    free(NodoAEliminar);
  }
  //resetear lista enlazada
  EmpleadoPrimerNodo = NULL;
  EmpleadoUltimoNodo = NULL;
  printf("\nMemoria liberada.\n");
}

void cargarEmpleadosEnMemoria() { 
  //asignar memoria
  NodoEmpleado *NuevoEmpleado = malloc(sizeof(NodoEmpleado));
  if (!NuevoEmpleado) {
    printf("\nError al asignar memoria\n");
    return;
  }
  //validación de ID
  cargarIDEmpleado(NuevoEmpleado);
  //pedir y cargar datos
  limpiarBuffers();
  printf("\nIngrese el apellido del empleado: ");
  LeerCadena(NuevoEmpleado->empleado.apellido, sizeof(NuevoEmpleado->empleado.apellido));
  printf("\nIngrese el nombre del empleado: ");
  LeerCadena(NuevoEmpleado->empleado.nombre, sizeof(NuevoEmpleado->empleado.nombre));
  printf("\nIndique el cargo del empleado:\n");
  printf("\t[1] VENDEDOR\n");
  printf("\t[2] ASISTENTE\n");
  printf("\t[3] SUPERVISOR\n");
  printf("\t[4] GERENTE\n");
  printf("\tCargo: ");
  do {
    NuevoEmpleado->empleado.cargo = LeerEntero();
  } while (NuevoEmpleado->empleado.cargo < 1 || NuevoEmpleado->empleado.cargo > 4);
  limpiarBuffers();
  establecerSalarioBase(NuevoEmpleado);
  //actualizar lista enlazada
  if (!EmpleadoPrimerNodo) {
    EmpleadoPrimerNodo = NuevoEmpleado;
    EmpleadoUltimoNodo = NuevoEmpleado;
    EmpleadoUltimoNodo->siguiente = NULL;
  } else {
    EmpleadoUltimoNodo->siguiente = NuevoEmpleado;
    EmpleadoUltimoNodo = NuevoEmpleado;
    EmpleadoUltimoNodo->siguiente = NULL;
  }
  //mensaje de finalización
  printf("\n\nDatos cargados en memoria listos para almacenar.\n");
}

void cargarEmpleadosEnArchivo() {
  //abrir archivo o crearlo si no existía
  FILE *empleados = fopen("../../data/empleados.dat","ab");
  //verificar apertura/creación
  if (!empleados) {
    printf("\nError al abrir/crear el archivo.\n");
    return;
  }
  //verificar que la lista no esté vacía
  if (!EmpleadoPrimerNodo) {
    printf("\nNo hay datos para almacenar.\n");
    return;
  }
  //cargar la lista en el archivo
  NodoEmpleado *nodoEmpleadoActual = EmpleadoPrimerNodo;
  while (nodoEmpleadoActual) {
    //almacenar registro desde el nodo en que se encuentra
    fwrite(&nodoEmpleadoActual->empleado,sizeof(Empleado),1,empleados);
    //avanzar al siguiente registro
    nodoEmpleadoActual = nodoEmpleadoActual->siguiente;
  }
  //aviso al usuario
  printf("\n\nDatos registrados en el archivo.\n");
  //cerrar el archivo
  fclose(empleados);
  liberarMemoriaEmpleados();
}

void listaDeEmpleados() {
  //abrir el archivo
  FILE *empleados = fopen("../../data/empleados.dat","rb");
  //verificar apertura
  if (!empleados) {
    printf("\nError al abrir el archivo.\n");
    return;
  }
  //si está vacío
  //fseek(empleados,0,SEEK_END);
  //if (ftell(empleados) == 0) {
  //  printf("\nEl archivo está vacío.\n");
  //  return;
  //}
  //si tiene información para mostrar
  fseek(empleados,0,SEEK_SET);  //  colocar el puntero de lectura de nuevo al inicio
  //iterar y mostrar todos los registros, ordenándolos por id
  Empleado empleadoActual;
  while (fread(&empleadoActual,sizeof(Empleado),1,empleados) == 1) {
    printf("\n[%d] ",empleadoActual.id);
    printf("%s ",empleadoActual.nombre);
    printf("%s ",empleadoActual.apellido);
    printf("%.2f ",empleadoActual.salario);
    printf("%d ",empleadoActual.cargo);
  }
  //cerrar el archivo
  fclose(empleados);
}
