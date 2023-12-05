#pragma once

// Estructura para almacenar la información de un proveedor
typedef struct {
    int id;
    char nombre[50];
    char direccion[100];
    char telefono[20];
} Proveedor;
typedef struct NodoProveedor {
    Proveedor proveedor;
    struct NodoProveedor *siguiente;
} NodoProveedor;

extern NodoProveedor *ProveedorPrimero;
extern NodoProveedor *ProveedorUltimo;

void cargarIDProveedor(NodoProveedor *nodoNuevo);
void liberarMemoriaProveedores();
void cargarProveedoresEnMemoria();
void cargarProveedoresEnArchivo();