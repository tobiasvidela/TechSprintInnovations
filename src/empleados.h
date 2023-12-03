#pragma once

typedef enum {
    VENDEDOR,
    ASISTENTE,
    SUPERVISOR,
    GERENTE
} Cargo;

typedef struct {
    int id;
    char nombre[50];
    char apellido[50];
    float salario;
    Cargo cargo;
} Empleado;