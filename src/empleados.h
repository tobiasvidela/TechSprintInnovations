#pragma once

typedef enum {
    VENDEDOR,
    ASISTENTE,
    SUPERVISOR,
    GERENTE
} Cargo;

typedef struct {
    int id;
    char apellido[50];
    char nombre[50];
    Cargo cargo;
    float salario;
} Empleado;

typedef struct {
    Empleado empleado;
    Empleado *siguiente;
} NodoEmpleado;

extern NodoEmpleado *EmpleadoPrimerNodo;
extern NodoEmpleado *EmpleadoUltimoNodo;

void cargarIDEmpleado(NodoEmpleado *nodoNuevo);
void establecerSalarioBase(NodoEmpleado *empleadoNuevo);
void liberarMemoriaEmpleados();
void cargarEmpleadosEnMemoria();
void cargarEmpleadosEnArchivo();