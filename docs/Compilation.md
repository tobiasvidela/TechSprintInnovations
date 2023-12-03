# ¿Cómo compilar el sistema?

Para compilar el sistema integral debe tenerse en cuenta el entorno en el que será compilado y ejecutado el programa. Esto es diferente para sistemas *unix* y sistemas *windows*.

## Instrucciones Paso a Paso (Windows)

1. Comprobar que el compilador `MinGW`, o alguno para C, esté instalado. De lo contrario, realizar la descarga e instalación.
1. Debe irse a la carpeta donde está ubicado el archivo `main.c` y abrir una terminal allí.
1. Ejecutar el comando `gcc main.c -o main.exe` para compilar el programa y darle 'main.exe' como nombre al ejecutable.
1. Finalmente ejecutar desde la terminal el archivo `main.exe` con, por ejemplo: `./main.exe`
1. Ante cualquier inconveniente contactar con el equipo de desarrollo.

## Instrucciones Paso a Paso (Linux)

1. Comprobar que el compilador `gcc` o semejante está instalado. De lo contrario, realizar la descarga e instalación.
1. Dirigirse a la carpeta donde está el archivo `main.c` y abrir una terminal allí.
1. Ejecutar el comando `gcc main.c -o main && ./main` para compilar y ejecutar el programa.
1. Ante cualquier inconveniente contactar con el equipo de desarrollo.
