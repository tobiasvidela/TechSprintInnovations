#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utilidades.h"
#include "empleados.h"


Empleado *EmpleadoPrimero = NULL;
Empleado *EmpleadoUltimo = NULL;

void cargarIDEmpleado(Empleado *empleado) {
  //  abrir el archivo
  FILE *empleados = fopen("empleados.dat","rb");
  //  si el archivo no existe
  if (empleados == NULL) {
    empleado->id = 1;
    //  si existen cargados en memoria
    if (EmpleadoUltimo != NULL && empleado->id <= EmpleadoUltimo->id) {
      //actualizar el id correctamente
      empleado->id = EmpleadoUltimo->id + 1;
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
  empleado->id = ultimo.id + 1;
  if (EmpleadoUltimo != NULL && empleado->id == EmpleadoUltimo->id) {
    empleado->id = EmpleadoUltimo->id + 1;
  }
  return;
}

void establecerSalarioBase(Empleado *empleado) {
  switch(empleado->cargo) {
    case VENDEDOR: {
      empleado->salario = 5000;
      break;
    }
    case ASISTENTE: {
      empleado->salario = 7500;
      break;
    }
    case SUPERVISOR: {
      empleado->salario = 10000;
      break;
    }
    case GERENTE: {
      empleado->salario = 15000;
      break;
    }
    default: {
      empleado->salario = 1000;
      break;
    }
  }
}

void liberarMemoriaEmpleados() {
  Empleado *empleadoActual = EmpleadoPrimero;
  while (empleadoActual) {
    //almacenar empleado ya almacenado
    Empleado *Killer = empleadoActual;
    //avanzar al siguiente empleado
    empleadoActual = empleadoActual->siguiente;
    //liberar memoria
    free(Killer);
  }
  printf("\nMemoria liberada.\n");
}

void cargarEmpleadosEnMemoria() {
  //asignar memoria
  Empleado *NuevoEmpleado = malloc(sizeof(Empleado));
  if (!NuevoEmpleado) {
    printf("\nError al asignar memoria\n");
    return;
  }
  //validación de ID
  cargarIDEmpleado(NuevoEmpleado);
  //pedir y cargar datos
  printf("\nIngrese el apellido del empleado: ");
  fgets(NuevoEmpleado->apellido,sizeof(NuevoEmpleado->apellido),stdin);
  limpiarBuffers();
  printf("\nIngrese el nombre del empleado: ");
  fgets(NuevoEmpleado->nombre,sizeof(NuevoEmpleado->nombre),stdin);
  printf("\nIndique el cargo del empleado:\n");
  printf("\t[1] VENDEDOR\n");
  printf("\t[2] ASISTENTE\n");
  printf("\t[3] SUPERVISOR\n");
  printf("\t[4] GERENTE\n");
  printf("\tCargo: ");
  do {
    NuevoEmpleado->cargo = LeerEntero();
  } while (NuevoEmpleado->cargo < 1 || NuevoEmpleado->cargo > 4);
  establecerSalarioBase(NuevoEmpleado);
  //actualizar lista enlazada
  if (!EmpleadoPrimero) {
    EmpleadoPrimero = NuevoEmpleado;
    EmpleadoUltimo = NuevoEmpleado;
    EmpleadoUltimo->siguiente = NULL;
  } else {
    EmpleadoUltimo->siguiente = NuevoEmpleado;
    EmpleadoUltimo = NuevoEmpleado;
    EmpleadoUltimo->siguiente = NULL;
  }
  //mensaje de finalización
  printf("\n\nEmpleados cargados en memoria listos para almacenar.\n");
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
  if (!EmpleadoPrimero) {
    printf("\nNo hay datos para almacenar.\n");
    return;
  }
  //cargar la lista en el archivo
  Empleado *empleadoActual = EmpleadoPrimero;
  while (empleadoActual) {
    //almacenar empleado
    fwrite(empleadoActual,sizeof(Empleado),1,empleados);
    //avanzar al siguiente empleado
    empleadoActual = empleadoActual->siguiente;
  }
  //aviso al usuario
  printf("\n\nEmpleados registrados en el archivo.\n");
  liberarMemoriaEmpleados();
}
