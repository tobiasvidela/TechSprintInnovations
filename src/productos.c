#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utilidades.h"
#include "proveedores.h"
#include "productos.h"

NodoProducto *ProductoPrimerNodo = NULL;
NodoProducto *ProductoUltimoNodo = NULL;

void cargarIDProducto(NodoProducto *nodoNuevo) {
  //  abrir el archivo
  FILE *productos = fopen("../../data/productos.dat","rb");
  //  si el archivo no existe
  if (productos == NULL) {
    nodoNuevo->producto.id = 1;
    //  si existen cargados en memoria
    if (ProductoUltimoNodo != NULL && nodoNuevo->producto.id <= ProductoUltimoNodo->producto.id) {
      //actualizar el id correctamente
      nodoNuevo->producto.id = ProductoUltimoNodo->producto.id + 1;
    }
    return;
  }
  //  si el archivo ya existe
  //  posicionar el puntero de lectura al inicio del último registro cargado
  fseek(productos, -sizeof(Producto), SEEK_END);
  //  leer el último registro cargado
  Producto ultimo;
  fread(&ultimo, sizeof(Producto), 1, productos);
  fclose(productos);
  nodoNuevo->producto.id = ultimo.id + 1;
  if (ProductoUltimoNodo != NULL && nodoNuevo->producto.id == ProductoUltimoNodo->producto.id) {
    nodoNuevo->producto.id = ProductoUltimoNodo->producto.id + 1;
  }
  return;
}

void liberarMemoriaProductos() {
  NodoProducto *NodoActual = ProductoPrimerNodo;
  while (NodoActual) {
    //almacenar empleado ya almacenado
    NodoProducto *Killer = NodoActual;
    //avanzar al siguiente empleado
    NodoActual = NodoActual->siguiente;
    //liberar memoria
    free(Killer);
  }
  //resetear lista enlazada
  ProductoPrimerNodo = NULL;
  ProductoUltimoNodo = NULL;
  printf("\nMemoria liberada.\n");
}

void cargarProductosEnMemoria() {
  //asignar memoria
  NodoProducto *NuevoProducto = malloc(sizeof(NodoProducto));
  if (!NuevoProducto) {
    printf("\nError al asignar memoria\n");
    return;
  }
  //validación de ID
  cargarIDProducto(NuevoProducto);
  //pedir y cargar datos
  printf("\nIndique el tipo de producto:\n");
  printf("\t[1] ELECTRONICA\n");
  printf("\t[2] MODA\n");
  printf("\t[3] HOGAR_DECORACION\n");
  printf("\t[4] ALIMENTOS_BEBIDAS\n");
  printf("\tTipo: ");
  do {
    NuevoProducto->producto.tipo = LeerEntero();
  } while (NuevoProducto->producto.tipo < 1 || NuevoProducto->producto.tipo > 4);
  printf("\nIngrese el nombre del producto: ");
  fgets(NuevoProducto->producto.nombre,sizeof(NuevoProducto->producto.nombre),stdin);
  limpiarBuffers();
  printf("\nIngrese el precio del producto (xxxx.xx): ");
  NuevoProducto->producto.precio = LeerFlotante();
  printf("\nIndique el proveedor del producto: ");
  listaDeProveedores();
  int totalProveedores = obtenerTotalProveedores();
  int idProveedorElegido;
  do {
    printf("\nProveedor Elegido: ");
    idProveedorElegido = LeerEntero();
  } while (idProveedorElegido < 0 || idProveedorElegido > totalProveedores);
  Proveedor proveedorElegido = copiarProveedorElegido(idProveedorElegido);
  NuevoProducto->producto.proveedor = proveedorElegido;
  
  //actualizar lista enlazada
  if (!ProductoPrimerNodo) {
    ProductoPrimerNodo = NuevoProducto;
    ProductoUltimoNodo = NuevoProducto;
    ProductoUltimoNodo->siguiente = NULL;
  } else {
    ProductoUltimoNodo->siguiente = NuevoProducto;
    ProductoUltimoNodo = NuevoProducto;
    ProductoUltimoNodo->siguiente = NULL;
  }
  //mensaje de finalización
  printf("\n\nDatos cargados en memoria listos para almacenar.\n");
}

void cargarProductosEnArchivo() {
  //abrir archivo o crearlo si no existía
  FILE *productos = fopen("../../data/productos.dat","ab");
  //verificar apertura/creación
  if (!productos) {
    printf("\nError al abrir/crear el archivo.\n");
    return;
  }
  //verificar que la lista no esté vacía
  if (!ProductoPrimerNodo) {
    printf("\nNo hay datos para almacenar.\n");
    return;
  }
  //cargar la lista en el archivo
  NodoProducto *nodoProductoActual = ProductoPrimerNodo;
  while (nodoProductoActual) {
    //almacenar registro desde el nodo en que se encuentra
    fwrite(&nodoProductoActual->producto,sizeof(Producto),1,productos);
    //avanzar al siguiente registro
    nodoProductoActual = nodoProductoActual->siguiente;
  }
  //aviso al usuario
  printf("\n\nDatos registrados en el archivo.\n");
  //cerrar archivo
  fclose(productos);
  liberarMemoriaProductos();
}

void listaDeProductos() {
  //abrir el archivo
  FILE *productos = fopen("../../data/productos.dat","rb");
  //verificar apertura
  if (!productos) {
    printf("\nError al abrir el archivo.\n");
    return;
  }
  //si está vacío
  fseek(productos,0,SEEK_END);
  if (ftell(productos) == 0) {
    printf("\nEl archivo está vacío.\n");
    return;
  }
  //si tiene información para mostrar
  fseek(productos,0,SEEK_SET);  //  colocar el puntero de lectura de nuevo al inicio
  //iterar y mostrar todos los registros, ordenándolos por id
  Producto productoActual;
  while (fread(&productoActual,sizeof(Producto),1,productos) == 1) {
    printf("\n[%d] %s",productoActual.id,productoActual.nombre);
  }
  //cerrar el archivo
  fclose(productos);
}
