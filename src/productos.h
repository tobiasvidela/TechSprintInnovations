#pragma once
#include "proveedores.h"

typedef enum {
  ELECTRONICA,
  MODA,
  HOGAR_DECORACION,
  ALIMENTOS_BEBIDAS
} TipoProducto;

typedef struct {
  int id;
  TipoProducto tipo;
  char nombre[50];
  float precio;
  Proveedor proveedor;
} Producto;

typedef struct NodoProducto {
  Producto producto;
  struct NodoProducto *siguiente;
} NodoProducto;

extern NodoProducto *ProductoPrimerNodo;
extern NodoProducto *ProductoUltimoNodo;

void cargarIDProducto(NodoProducto *nodoNuevo);
void liberarMemoriaProductos();
void cargarProductosEnMemoria();
void cargarProductosEnArchivo();
void listaDeProductos();