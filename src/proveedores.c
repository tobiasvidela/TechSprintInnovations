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
  FILE *proveedores = fopen("proveedores.dat","rb");
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
  while (NodoActual) {
    //almacenar proveedor ya almacenado
    NodoProveedor *Killer = NodoActual;
    //avanzar al siguiente proveedor
    NodoActual = NodoActual->siguiente;
    //liberar memoria
    free(Killer);
  }
  printf("\nMemoria liberada.\n");
}

void cargarProveedoresEnMemoria() {
  //asignar memoria
  NodoProveedor *NuevoNodo = malloc(sizeof(NodoProveedor));
  if (!NuevoNodo) {
    printf("\nError al asignar memoria\n");
    return;
  }
  //validación de ID
  cargarIDProveedor(NuevoNodo);
  //pedir y cargar datos
  printf("\nIngrese el nombre del proveedor: ");
  fgets(NuevoNodo->proveedor.nombre,sizeof(NuevoNodo->proveedor.nombre),stdin);
  limpiarBuffers();
  printf("\nIngrese la direccion del proveedor: ");
  fgets(NuevoNodo->proveedor.direccion,sizeof(NuevoNodo->proveedor.direccion),stdin);
  printf("\nIngrese el telefono del proveedor: ");
  fgets(NuevoNodo->proveedor.telefono,sizeof(NuevoNodo->proveedor.telefono),stdin);
  //actualizar lista enlazada
  if (!ProveedorPrimerNodo) {
    ProveedorPrimerNodo = NuevoNodo;
    ProveedorUltimoNodo = NuevoNodo;
    ProveedorUltimoNodo->siguiente = NULL;
  } else {
    ProveedorUltimoNodo->siguiente = NuevoNodo;
    ProveedorUltimoNodo = NuevoNodo;
    ProveedorUltimoNodo->siguiente = NULL;
  }
  //mensaje de finalización
  printf("\n\nDatos cargados en memoria listos para almacenar.\n");
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
  liberarMemoriaProveedores();
}
