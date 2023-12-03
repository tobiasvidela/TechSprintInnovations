#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "../include/utilidades.h"
#include "../include/utilidades.c"
#include "menu.h"


void menu() {
    int opcion;
    do {
        limpiarConsola();
        titulo();
        imprimirOpciones();
        opcion = LeerEntero();
        submenu(opcion);
    } while (opcion != 0);

}

void titulo() {
    imprimirCadenaCentrada("\n");
    imprimirCadenaCentrada("Sistema Integral para TechSprint Innovations");
    imprimirCadenaCentrada("\n");
}

void imprimirOpciones() {
    printf("[1] Crear archivo binario para Empleados y Cargar Datos.\n");
    printf("[2] Crear archivo binario para Proveedores y Cargar Datos\n");
    printf("[3] Crear archivo binario para Recursos y Cargar Datos\n");
    printf("[4] Crear archivo binario para Ventas y Cargar Datos\n");
    printf("[0] Salir\n");
}

void submenu(int opcionELegida) {
    switch(opcionELegida) {
        case 1:{//Crear archivo binario para Empleados y Cargar Datos.
            continuar();
            break;
        }
        case 2:{//Crear archivo binario para Proveedores y Cargar Datos.
            continuar();
            break;
        }
        case 3:{//Crear archivo binario para Recursos y Cargar Datos.
            continuar();
            break;
        }
        case 4:{//Crear archivo binario para Ventas y Cargar Datos.
            continuar();
            break;
        }
        default:
            break;
    }
}