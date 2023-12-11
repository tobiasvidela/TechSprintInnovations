#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "../include/utilidades.h" //Ruta relativa
#include "../include/utilidades.c" //Ruta relativa
#include "empleados.h" //Ruta relativa
#include "empleados.c" //Ruta relativa
#include "proveedores.h" //Ruta relativa
#include "proveedores.c" //Ruta relativa
#include "productos.h" //Ruta relativa
#include "productos.c" //Ruta relativa
#include "menu.h"


void menu() {
    //imprimir menu principal
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
    imprimirCadenaCentradaEnConsola("\n");
    imprimirCadenaCentradaEnConsola("Sistema Integral para TechSprint Innovations");
    imprimirCadenaCentradaEnConsola("\n");
}

void imprimirOpciones() {
    printf("[1] Gestion de Inventarios\n");
    printf("[2] Administracion de Recursos\n");
    printf("[3] Procesamiento de Transacciones\n");
    printf("[4] Herramientas de Analisis\n");
    printf("[0] Salir\n");
}

void submenu(int opcionELegida) {
    //imprimir submenu elegido
    int opcion;
    switch(opcionELegida) {
        case 1:{
            //menu Gestion de Inventarios
            limpiarConsola();
            continuar();
            break;
        }
        case 2:{
            //menu Administracion de Recursos
            do {
                limpiarConsola();
                imprimirCadenaCentradaEnConsola("Administracion de Recursos");
                menuAdministracionRecursos();
                do {
                    printf("\tOpcion: ");
                    opcion = LeerEntero();
                } while (opcion < 0 || opcion > 8);
                submenuAdministracionRecursos(opcion);
            } while (opcion != 0);
            continuar();
            break;
        }
        case 3:{
            //menu Procesamiento de Transacciones
            limpiarConsola();
            continuar();
            break;
        }
        case 4:{
            //menu Herrameintas de Analisis
            limpiarConsola();
            continuar();
            break;
        }
        default:
            break;
    }
}

void menuAdministracionRecursos() {
    //imprimir opciones del submenu elegido
    printf("[1] Cargar y almacenar nuevos Empleados\n");
    printf("[2] Ver lista de Empleados almacenados\n");
    printf("[3] Cargar y almacenar nuevos Proveedores\n");
    printf("[4] Ver lista de Proveedores almacenados\n");
    printf("[5] Cargar y almacenar nuevos Productos\n");
    printf("[6] Ver lista de Productos almacenados\n");
    printf("[7] Cargar y almacenar nuevas Ventas\n");
    printf("[8] Ver lista de Ventas almacenadas\n");
    printf("[0] Salir\n");
}

void submenuAdministracionRecursos(int opcionELegida) {
    //imprimir submenu elegido
    switch(opcionELegida) {
        case 1:{
            limpiarConsola();
            submenuEmpleados();
            continuar();
            break;
        }
        case 2:{
            limpiarConsola();
            listaDeEmpleados();
            continuar();
            break;
        }
        case 3:{
            limpiarConsola();
            submenuProveedores();
            continuar();
            break;
        }
        case 4:{
            limpiarConsola();
            listaDeProveedores();
            continuar();
            break;
        }
        case 5:{
            limpiarConsola();
            submenuProductos();
            continuar();
            break;
        }
        case 6:{
            limpiarConsola();
            listaDeProductos();
            continuar();
            break;
        }
        case 7:{
            limpiarConsola();
            continuar();
            break;
        }
        case 8:{
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
    imprimirCadenaCentradaEnConsola("Sub Menu Empleados");
    printf("\n");
    printf("¿Desea agregar un empleado?");
    printf("\n\t[1] SI\t[0] NO\n");
    do {
        printf("R: ");
        opcion = LeerEntero();
    } while (opcion < 0 || opcion > 1);
    if (opcion == 0) { return; }
    //cargar tantos registros como desee el usuario
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

void submenuProveedores() {
    int opcion;
    printf("\n");
    imprimirCadenaCentradaEnConsola("Sub Menu Proveedores");
    printf("\n");
    printf("¿Desea agregar un proveedor?");
    printf("\n\t[1] SI\t[0] NO\n");
    do {
        printf("R: ");
        opcion = LeerEntero();
    } while (opcion < 0 || opcion > 1);
    if (opcion == 0) { return; }
    //cargar tantos registros como desee el usuario
    do {
        limpiarConsola();
        printf("Nuevo Proveedor:\n");
        cargarProveedoresEnMemoria();
        printf("\n¿Desea seguir cargando proveedores?\n");
        printf("\n\t[1] SI\t[0] NO\n");
        do {
            printf("R: ");
            opcion = LeerEntero();
        } while (opcion < 0 || opcion > 1);
    } while (opcion != 0);
    //decidir si se van a almacenar o perder los datos cargados
    do {
        printf("\n¿Desea almacenar los proveedores cargados?\n");
        printf("\n\t[1] Guardar datos\t[0] Perder datos\n");
        do {
            printf("R: ");
            opcion = LeerEntero();
        } while (opcion < 0 || opcion > 1);
        if (opcion == 1) {
            cargarProveedoresEnArchivo();
        }
        if (opcion == 0) {
            liberarMemoriaProveedores();
        }
    } while (opcion < 0 || opcion > 1);
}

void submenuProductos() {
    int opcion;
    printf("\n");
    imprimirCadenaCentradaEnConsola("Sub Menu Productos");
    printf("\n");
    printf("¿Desea agregar un producto?");
    printf("\n\t[1] SI\t[0] NO\n");
    do {
        printf("R: ");
        opcion = LeerEntero();
    } while (opcion < 0 || opcion > 1);
    if (opcion == 0) { return; }
    //cargar tantos registros como desee el usuario
    do {
        limpiarConsola();
        printf("Nuevo Producto:\n");
        cargarProductosEnMemoria();
        printf("\n¿Desea seguir cargando productos?\n");
        printf("\n\t[1] SI\t[0] NO\n");
        do {
            printf("R: ");
            opcion = LeerEntero();
        } while (opcion < 0 || opcion > 1);
    } while (opcion != 0);
    //decidir si se van a almacenar o perder los datos cargados
    do {
        printf("\n¿Desea almacenar los productos cargados?\n");
        printf("\n\t[1] Guardar datos\t[0] Perder datos\n");
        do {
            printf("R: ");
            opcion = LeerEntero();
        } while (opcion < 0 || opcion > 1);
        if (opcion == 1) {
            cargarProductosEnArchivo();
        }
        if (opcion == 0) {
            liberarMemoriaProductos();
        }
    } while (opcion < 0 || opcion > 1);
}
