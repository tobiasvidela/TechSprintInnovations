#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utilidades.h"
#include "proveedores.h"


NodoProveedor *ProveedorPrimerNodo = NULL;
NodoProveedor *ProveedorUltimoNodo = NULL;

void cargarIDProveedor(NodoProveedor *nodoNuevo) {
  //  abrir el archivo
  FILE *proveedores = fopen("./../data/proveedores.dat","rb");
  //  si el archivo no existe
  if (proveedores == NULL) {
    nodoNuevo->proveedor.id = 1;
    //  si existen cargados en memoria
    if (ProveedorUltimoNodo != NULL && nodoNuevo->proveedor.id <= ProveedorUltimoNodo->proveedor.id) {
      //actualizar el id correctamente
      nodoNuevo->proveedor.id = ProveedorUltimoNodo->proveedor.id + 1;
    }
    return;
  }
  //  si el archivo ya existe
  //  posicionar el puntero de lectura al inicio del último registro cargado
  fseek(proveedores, -sizeof(Proveedor), SEEK_END);
  //  leer el último registro cargado
  Proveedor ultimo;
  fread(&ultimo, sizeof(Proveedor), 1, proveedores);
  fclose(proveedores);
  nodoNuevo->proveedor.id = ultimo.id + 1;
  if (ProveedorUltimoNodo != NULL && nodoNuevo->proveedor.id == ProveedorUltimoNodo->proveedor.id) {
    nodoNuevo->proveedor.id = ProveedorUltimoNodo->proveedor.id + 1;
  }
  return;
}

void liberarMemoriaProveedores() {
  NodoProveedor *NodoActual = ProveedorPrimerNodo;
  while (NodoActual != NULL) {
    NodoProveedor *NodoAEliminar = NodoActual;
    NodoActual = NodoActual->siguiente;
    free(NodoAEliminar);
  }
  //resetear lista enlazada
  ProveedorPrimerNodo = NULL;
  ProveedorUltimoNodo = NULL;
  printf("\nMemoria liberada.\n");
}

void cargarProveedoresEnMemoria() {
  //asignar memoria
  NodoProveedor *NuevoProveedor = malloc(sizeof(NodoProveedor));
  if (!NuevoProveedor) {
    printf("\nError al asignar memoria\n");
    return;
  }
  //validación de ID
  cargarIDProveedor(NuevoProveedor);
  //pedir y cargar datos
  limpiarBuffers();
  printf("\nIngrese el nombre del proveedor: ");
  LeerCadena(NuevoProveedor->proveedor.nombre, sizeof(NuevoProveedor->proveedor.nombre));
  printf("\nIngrese la direccion del proveedor: ");
  LeerCadena(NuevoProveedor->proveedor.direccion, sizeof(NuevoProveedor->proveedor.direccion));
  printf("\nIngrese el telefono del proveedor: ");
  LeerCadena(NuevoProveedor->proveedor.telefono, sizeof(NuevoProveedor->proveedor.telefono));
  //actualizar lista enlazada
  if (!ProveedorPrimerNodo) {
    ProveedorPrimerNodo = NuevoProveedor;
    ProveedorUltimoNodo = NuevoProveedor;
    ProveedorUltimoNodo->siguiente = NULL;
  } else {
    ProveedorUltimoNodo->siguiente = NuevoProveedor;
    ProveedorUltimoNodo = NuevoProveedor;
    ProveedorUltimoNodo->siguiente = NULL;
  }
  //mensaje de finalización
  printf("\n\nDatos cargados en memoria listos para almacenar.\n");
  NodoProveedor *actual = ProveedorPrimerNodo;
  while (actual) {
    printf("\n[%d]",actual->proveedor.id);
    printf(" %s",actual->proveedor.nombre);
    printf("\f%s",actual->proveedor.direccion);
    printf("\f%s",actual->proveedor.telefono);
    printf("\n");
    actual = actual->siguiente;
  }
}

void cargarProveedoresEnArchivo() {
  //abrir archivo o crearlo si no existía
  FILE *proveedores = fopen("../../data/proveedores.dat","ab");
  //verificar apertura/creación
  if (!proveedores) {
    printf("\nError al abrir/crear el archivo.\n");
    return;
  }
  //verificar que la lista no esté vacía
  if (!ProveedorPrimerNodo) {
    printf("\nNo hay datos para almacenar.\n");
    return;
  }
  //cargar la lista en el archivo
  NodoProveedor *nodoProveedorActual = ProveedorPrimerNodo;
  while (nodoProveedorActual) {
    //almacenar registro desde el nodo en que se encuentra
    fwrite(&nodoProveedorActual->proveedor,sizeof(Proveedor),1,proveedores);
    //avanzar al siguiente registro
    nodoProveedorActual = nodoProveedorActual->siguiente;
  }
  //aviso al usuario
  printf("\n\nDatos registrados en el archivo.\n");
  //cerrar archivo
  fclose(proveedores);
  liberarMemoriaProveedores();
}

void listaDeProveedores() {
  //abrir el archivo
  FILE *proveedores = fopen("../../data/proveedores.dat","rb");
  //verificar apertura
  if (!proveedores) {
    printf("\nError al abrir el archivo.\n");
    return;
  }
  //si está vacío
  fseek(proveedores,0,SEEK_END);
  if (ftell(proveedores) == 0) {
    printf("\nEl archivo está vacío.\n");
    return;
  }
  //si tiene información para mostrar
  fseek(proveedores,0,SEEK_SET);  //  colocar el puntero de lectura de nuevo al inicio
  //iterar y mostrar todos los registros, ordenándolos por id
  Proveedor proveedorActual;
  while (fread(&proveedorActual,sizeof(Proveedor),1,proveedores) == 1) {
    printf("\n[%d] %s",proveedorActual.id,proveedorActual.nombre);
  }
  //cerrar el archivo
  fclose(proveedores);
}

int obtenerTotalProveedores() {
  //abrir el archivo
  FILE *proveedores = fopen("../../data/proveedores.dat","rb");
  //verificar apertura
  if (!proveedores) {
    printf("\nError al abrir el archivo.\n");
    return 0;
  }
  //si está vacío
  fseek(proveedores,0,SEEK_END);
  if (ftell(proveedores) == 0) {
    return 0;
  }
  //si tiene información
  //colocar el puntero de lectura al principio del último registro
  fseek(proveedores,(-1)*sizeof(Proveedor),SEEK_END);
  //leemos el último registro y lo guardamos en una variable
  Proveedor ultimoProveedor;
  fread(&ultimoProveedor,sizeof(Proveedor),1,proveedores);
  //cerrar el archivo
  fclose(proveedores);
  //devoler el id del último registro
  return ultimoProveedor.id;
}

Proveedor copiarProveedorElegido(int idProveedorElegido) {
  Proveedor proveedorElegido;
  //abrir el archivo
  FILE *proveedores = fopen("../../data/proveedores.dat","rb");
  //verificar apertura
  if (!proveedores) {
    printf("\nError al abrir el archivo.\n");
    return proveedorElegido;
  }
  //si está vacío
  fseek(proveedores,0,SEEK_END);
  if (ftell(proveedores) == 0) {
    printf("\nEl archivo está vacío.\n");
    return proveedorElegido;
  }
  //si tiene información
  //posicionarse al PRINCIPIO del registro elegido utilizando el id
  fseek(proveedores,(idProveedorElegido-1)*sizeof(Proveedor),SEEK_SET);
  //copiar el registro en una variable temporal
  fread(&proveedorElegido,sizeof(Proveedor),1,proveedores);
  //cerrar el archivo
  fclose(proveedores);
  //devolver el registro
  return proveedorElegido;
}