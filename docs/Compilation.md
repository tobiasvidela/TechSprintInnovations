# ¿Cómo compilar y ejecutar el sistema?

Para compilar el sistema integral debe tenerse en cuenta el entorno en el que será compilado y ejecutado el programa. Esto es diferente para sistemas *unix* y sistemas *windows*.

## Instrucciones Paso a Paso (VS Code)

1. Instalar las extensiones C/C++ y C Copmiler y las demás que se crean necesarias por su criterio.
1. Teniendo en ventana activa el archivo `main.c`, presionar el botón triangular de compilación y ejecución arriba a la derecha, o también presionando `F6` o `Fn + F6`.
1. Esperar que compile y cargue el programa en la terminal integrada de Vs Code.
1. Ante cualquier inconveniente contactar con el equipo de desarrollo.

## Instrucciones Paso a Paso (Windows)

1. Comprobar que el compilador `MinGW`, o alguno para C, esté instalado. De lo contrario, realizar la descarga e instalación.
1. Debe irse a la carpeta donde está ubicado el archivo `main.c` y abrir una terminal allí.
1. Ejecutar el comando `gcc main.c -o main.exe` para compilar el programa y darle 'main.exe' como nombre al ejecutable.
1. Finalmente ejecutar el archivo `main.exe`. Por ejemplo, dando doble click al archivo.
1. Ante cualquier inconveniente contactar con el equipo de desarrollo.

## Instrucciones Paso a Paso (Linux)

1. Comprobar que el compilador `gcc` o semejante está instalado. De lo contrario, realizar la descarga e instalación.
1. Dirigirse a la carpeta donde está el archivo `main.c` y abrir una terminal allí.
1. Finalmente ejecutar el comando `gcc main.c -o main && ./main` para compilar y ejecutar el programa.
1. Ante cualquier inconveniente contactar con el equipo de desarrollo.
