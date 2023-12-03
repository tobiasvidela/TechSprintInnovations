#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "../include/utilidades.h"
#include "../include/utilidades.c"
#include "empleados.h" //Ruta relativa
#include "empleados.c" //Ruta relativa
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
            limpiarConsola();
            submenuEmpleados();
            continuar();
            break;
        }
        case 2:{//Crear archivo binario para Proveedores y Cargar Datos.
            limpiarConsola();
            continuar();
            break;
        }
        case 3:{//Crear archivo binario para Recursos y Cargar Datos.
            limpiarConsola();
            continuar();
            break;
        }
        case 4:{//Crear archivo binario para Ventas y Cargar Datos.
            limpiarConsola();
            continuar();
            break;
        }
        default:
            break;
    }
}

void submenuEmpleados() {
    int opcion;
    printf("\n");
    imprimirCadenaCentrada("Sub Menu Empleados");
    printf("\n");
    printf("¿Desea agregar un empleado?");
    printf("\n\t[1] SI\t[0] NO\n");
    do {
        printf("R: ");
        opcion = LeerEntero();
    } while (opcion < 0 || opcion > 1);
    if (opcion == 0) { return; }
    //cargar tantos empleados como desee el usuario
    do {
        limpiarConsola();
        printf("Nuevo Empleado:\n");
        cargarEmpleadosEnMemoria();
        printf("\n¿Desea seguir cargando empleados?\n");
        printf("\n\t[1] SI\t[0] NO\n");
        do {
            printf("R: ");
            opcion = LeerEntero();
        } while (opcion < 0 || opcion > 1);
    } while (opcion != 0);
    //decidir si se van a almacenar o perder los datos cargados
    do {
        printf("\n¿Desea almacenar los empleados cargados?\n");
        printf("\n\t[1] Guardar datos\t[0] Perder datos\n");
        do {
            printf("R: ");
            opcion = LeerEntero();
        } while (opcion < 0 || opcion > 1);
        if (opcion == 1) {
            cargarEmpleadosEnArchivo();
        }
        if (opcion == 0) {
            liberarMemoriaEmpleados();
        }
    } while (opcion < 0 || opcion > 1);
}