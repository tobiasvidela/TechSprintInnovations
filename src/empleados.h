#pragma once

typedef enum {
    VENDEDOR,
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
    struct Empleado *siguiente;
} Empleado;

extern Empleado *EmpleadoPrimero;
extern Empleado *EmpleadoUltimo;

void cargarIDEmpleado(Empleado *empleado);
void establecerSalarioBase(Empleado *empleado);
void liberarMemoriaEmpleados();
void cargarEmpleadosEnMemoria();
void cargarEmpleadosEnArchivo();