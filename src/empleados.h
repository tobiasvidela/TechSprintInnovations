#pragma once

typedef enum Cargo {
    VENDEDOR = 1,
    ASISTENTE,
    SUPERVISOR,
    GERENTE
} Cargo;

typedef struct Empleado {
    int id;
    char apellido[50];
    char nombre[50];
    Cargo cargo;
    float salario;
} Empleado;

typedef struct NodoEmpleado {
    Empleado empleado;
    struct NodoEmpleado *siguiente;
} NodoEmpleado;

extern NodoEmpleado *EmpleadoPrimerNodo;
extern NodoEmpleado *EmpleadoUltimoNodo;

void cargarIDEmpleado(NodoEmpleado *nodoNuevo);
void establecerSalarioBase(NodoEmpleado *empleadoNuevo);
void liberarMemoriaEmpleados();
void cargarEmpleadosEnMemoria();
void cargarEmpleadosEnArchivo();
void listaDeEmpleados();