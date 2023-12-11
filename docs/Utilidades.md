# UTILIDADES GENERALES

Aquí deben documentarse todas las utilidades generales agregadas al proyecto, de manera clara, concisa, detallada y completa.

## Limpiar Consola / Pantalla

Al ser un programa CLI, este proyecto necesita de una función que se encargue de limpiar la pantalla de la terminal donde se esté ejecutando el programa, indistintamente del sistema en que se esté ejecutando.

- **limpiarConsola()**

    Esta función se encarga de limpiar la pantalla de la consola o terminal donde se esté ejecutando el programa. Utiliza la biblioteca estándar `system()` para enviar comandos específicos según el sistema operativo en el que se esté ejecutando el programa.

    Esta función es útil cuando se desea limpiar la pantalla de la consola para proporcionar una presentación más limpia o mejorar la legibilidad del texto en un programa que se ejecuta en la terminal.

    ``````
    void limpiarConsola() {
      #ifdef __unix__  // Unix/Linux/MacOS
        system("clear");
      #else   // Windows
        system("cls");
      #endif
    }
    ``````

    1. Directivas de preprocesador (#ifdef, #else, #endif):

        Estas directivas condicionales verifican si el programa está siendo compilado en un sistema operativo tipo Unix/Linux/MacOS o en Windows.
        `#ifdef __unix__` comprueba si se está compilando en un sistema operativo Unix, que incluye Linux y MacOS.
        Si el sistema es tipo Unix, se ejecuta el comando `"clear"` usando la función `system()`.
        Si no es un sistema tipo Unix (es decir, es un sistema Windows), se ejecuta el comando `"cls"` usando `system()`.

    2. `system()`:
    
        Esta función pertenece a la biblioteca estándar de C (stdlib.h) y se utiliza para ejecutar comandos del sistema operativo desde el programa en C.
        En sistemas Unix ("clear"): El comando `"clear"` borra la pantalla de la terminal o consola, eliminando todo el texto y devolviendo la posición del cursor al inicio.
        En sistemas Windows ("cls"): El comando `"cls"` también limpia la pantalla de la consola, eliminando el texto y colocando el cursor en la parte superior izquierda de la ventana de la consola.

> [!WARNING]
> 
> El uso de `system()` para ejecutar comandos del sistema puede tener implicaciones de seguridad, ya que ejecuta comandos directamente en la terminal. Se debe tener cuidado al utilizar `system()` con comandos proporcionados por el usuario para evitar posibles vulnerabilidades de seguridad.

## Limpieza de Buffers

Para un manejo adecuado de entradas y lecturas de datos, es crucial realizar un manejo correcto de los buffers de entrada y salida. Eliminando los residuos para que no interfieran en lecturas posteriores.

- **limpiarBuffers()**

    Esta función está diseñada para limpiar o vaciar los buffers de entrada del programa.

    ``````
    void limpiarBuffers() {
      fflush(stdout);
      char c;
      while((c = getchar()) != '\n' && c != EOF){};
    }
    ``````

    1. `fflush(stdout)` se utiliza para asegurarse de que cualquier texto en el buffer de salida (stdout) se imprima en la consola antes de continuar con la ejecución del programa.
    2. El bucle while con `getchar()` se utiliza para limpiar o descartar cualquier entrada pendiente en el buffer de entrada (stdin), es decir, se lee y descarta cualquier carácter que quede en el buffer hasta que se encuentra un salto de línea ('\n') o se alcanza el final del archivo (EOF).

    > - `fflush()` es una función de la biblioteca estándar de C (stdio.h) que se usa para limpiar el buffer de salida del programa.
    > - `getchar()` es una función de la biblioteca estándar de C (stdio.h) que se usa para leer caracteres desde la entrada estándar (stdin).

> [!IMPORTANT]
>
> Esta función, `limpiarBuffers()`, debe utilizarse antes de la lectura de datos con `LeerCadena()` y pude ser útil después de pedir datos numéricos desde el teclado (stdin) con `LeerEntero()` y `LeerFlotante()`. Su uso queda a criterio del programador en el último caso.

## Pausa del Programa

Todo programa necesita la opción de pausar su ejecución hasta que el usuario presione la tecla "Enter", por ejemplo. Con el fin de dar una espera antes de continuar con la ejecución normal de la aplicación.

- **continuar()**

    ``````
    void continuar() {
      printf("\nPresiona Enter para continuar...");
      //limpiar Buffers
      char c;
      while((c = getchar()) != '\n' && c != EOF){};
      scanf("%*[^\n]%*c");
      getchar();//  Esperar a que el usuario presione Enter
    }
    ``````

    - **printf("\nPresiona Enter para continuar...");**:

        Utiliza `printf()` para mostrar un mensaje en la consola que indica al usuario que debe presionar la tecla "Enter" para continuar.

    - **char c; while((c = getchar()) != '\n' && c != EOF){};**:

        Este bucle while se encarga de limpiar o vaciar el buffer de entrada (stdin) descartando cualquier carácter que quede en él hasta que se encuentre un salto de línea ('\n') o se alcance el final del archivo (EOF). Esto asegura que no haya entrada pendiente que pueda interferir con la próxima operación de entrada.

    - **scanf("%*[^\n]%*c");**:

        `scanf()` es una función utilizada para leer datos de la entrada estándar (stdin).

        **'%*[^\n]'** especifica que se debe ignorar cualquier número de caracteres que no sean saltos de línea ('\n') en el buffer de entrada.

        __'%*c'__ se utiliza para ignorar el carácter de salto de línea en el buffer de entrada después de haber leído los caracteres anteriores. Esto es para asegurar que el salto de línea se elimine del buffer y no interfiera con la siguiente entrada.

    - **getchar();**:

        `getchar()` espera a que el usuario presione la tecla "Enter" para continuar. Esta función lee un carácter de la entrada estándar (stdin) y espera hasta que se ingrese una tecla. En este caso, se usa para esperar específicamente hasta que se presione la tecla "Enter" antes de continuar la ejecución del programa.
    
- En resumen:

    1. La función `continuar()` muestra un mensaje que indica al usuario que debe presionar "Enter".
    1. Luego, se limpian los buffers de entrada para descartar cualquier entrada adicional.
    1. Se utiliza `scanf()` para ignorar cualquier entrada adicional que no sea un salto de línea ('\n').
    1. Finalmente, `getchar()` se utiliza para esperar a que el usuario presione "Enter", lo que permite que el programa continúe su ejecución.

> [!NOTE]
>
> Se realiza de esta manera porque utilizar la función `limpiarBuffers()` generaba algunos conflictos durante la ejecución en esta u otras aplicaciones. Por lo que se optó por realizar este arreglo interno para esta función y dejar la otra función para los usos indicados en su documentación.

## Control de Entradas

El control de las entradas es fundamental para prevenir errores y lecturas incorrectas que puedan romper el funcionamiento del sistema. De manera que si se pide ingresar un tipo de dato y el usuario ingresa uno diferente, el programa no se bloquee o no tome como válidos tales tipos o formatos de datos incorrectos. Por lo que es imperativo el uso de funciones que cumplan con el control de entradas pedido.

A continuación, se presentan y explican el uso y funcionamiento de las funciones de lectura de entradas típicas.

- ### **LeerEntero()**

    Esta función está diseñada para leer un número entero desde la entrada estándar (stdin).

    ``````
    int LeerEntero() {
      int entero, control;
      do {
        if (scanf("%d", &entero) != 1){
          limpiarBuffers();
          control = 1;
        } else {
          control = 0;
        }
      } while (control);
      return entero;
    }
    ``````

    1. **Variables utilizadas**:

        `int entero, control;`: Declara dos variables, entero para almacenar el número entero leído y control para controlar el bucle.

    1. **Bucle do-while**:

        `do { ... } while (control);`: Este bucle se ejecuta al menos una vez y seguirá ejecutándose siempre que control sea 'verdadero' (no sea cero). Esto permite la repetición del proceso de lectura hasta que se ingrese un número entero válido.

    1. **Condicional if dentro del bucle**:

        `if (scanf("%d", &entero) != 1) { ... }`: Intenta leer un número entero usando `scanf()` desde la entrada estándar (stdin). Si `scanf()` no puede leer un entero correctamente (devuelve un valor distinto de 1, que indica que no se ha leído un solo número entero), se ejecuta el bloque de código dentro del if.

    1. **Control de flujo en el if**:

        `limpiarBuffers();`: Si `scanf()` no lee un número entero correctamente, se llama a la función `limpiarBuffers()` para limpiar el buffer de entrada y eliminar la entrada inválida que ha causado el fallo en la lectura.
        `control = 1;`: Establece control en 1 para indicar que se ha producido un error en la lectura del entero.

    1. **Control de flujo en el else**:

        Si `scanf()` lee correctamente un número entero, se establece control en 0 para salir del bucle do-while.

    1. **Retorno del entero leído**:

        Finalmente, una vez que se ha leído con éxito un número entero, el valor almacenado en entero se devuelve como resultado de la función `LeerEntero()`.
    
    ### Forma de uso (en general):

        int entero;
        entero = LeerEntero();

- ### **LeerFlotante()**

    Esta función está diseñada para leer un número de punto flotante (número decimal) desde la entrada estándar (stdin).

    ``````
    float LeerFlotante() {
      float numero;
      int control;
      do {
        if (scanf("%f", &numero) != 1) {
          limpiarBuffers();
          control = 1;
        } else {
          control = 0;
        }
      } while (control);
      return numero;
    }

    ``````

    1. **Variables utilizadas**:

        `float numero; int control;`: Declara dos variables, numero para almacenar el número flotante leído y control para controlar el bucle.

    1. **Bucle do-while**:

        `do { ... } while (control);`: Este bucle se ejecuta al menos una vez y seguirá ejecutándose siempre que control sea verdadero (no sea cero). Esto permite la repetición del proceso de lectura hasta que se ingrese un número de punto flotante válido.

    1. **Condicional if dentro del bucle**:

        `if (scanf("%f", &numero) != 1) { ... }`: Intenta leer un número de punto flotante utilizando `scanf()` desde la entrada estándar (stdin). Si `scanf()` no puede leer un número flotante correctamente (devuelve un valor distinto de 1, indicando que no se ha leído un solo número flotante), se ejecuta el bloque de código dentro del if.

    1. **Control de flujo en el if**:

        `limpiarBuffers();`: Si `scanf()` no lee un número flotante correctamente, se llama a la función `limpiarBuffers()` para limpiar el buffer de entrada y eliminar la entrada inválida que ha causado el fallo en la lectura.
        `control = 1;`: Establece control en 1 para indicar que se ha producido un error en la lectura del número flotante.

    1. **Control de flujo en el else**:

        Si `scanf()` lee correctamente un número flotante, se establece control en 0 para salir del bucle do-while.

    1. **Retorno del número flotante leído**:

        Una vez que se ha leído con éxito un número flotante, el valor almacenado en numero se devuelve como resultado de la función `LeerFlotante()`.

    ### Forma de uso (en general):

        float flotante;
        flotante = LeerFlotante();

- ### **LeerCadena()**

    Esta función está diseñada para leer una cadena de caracteres desde la entrada estándar (stdin) y almacenarla en un array de caracteres proporcionado (char *cadena). Esta función permite un manejo más limpio y preciso de la entrada de texto (por parte del usuario).

    ``````
    void LeerCadena(char *cadena, int longitud) {

      fgets(cadena, longitud, stdin); // Leer la cadena con fgets

      // Eliminar el carácter de salto de línea si está presente
      cadena[strcspn(cadena, "\n")] = '\0';
    }
    ``````

    1. **Parámetros**:

        `char *cadena`: Es un puntero que apunta al array de caracteres donde se almacenará la cadena leída.
        `int longitud`: Especifica la longitud máxima de la cadena que se puede leer y almacenar en cadena para evitar desbordamientos de memoria.

    1. **fgets(cadena, longitud, stdin);**:

        Utiliza la función `fgets()` para leer una línea de texto desde la entrada estándar (stdin) y almacenarla en el array de caracteres cadena.
        `fgets()` lee como máximo longitud - 1 caracteres o hasta que se encuentre un salto de línea ('\n') o el final del archivo (EOF). Almacena la línea leída en cadena, incluyendo el salto de línea si es leído y si el tamaño de la línea no excede la longitud proporcionada menos uno (para dejar espacio para el carácter nulo \0 al final de la cadena).

    1. **Eliminar el carácter de salto de línea**:

        `cadena[strcspn(cadena, "\n")] = '\0';`: Esta línea se encarga de eliminar el carácter de salto de línea ('\n') de la cadena, si está presente.
        `strcspn()` busca la posición del primer carácter coincidente con '\n' en cadena. Si lo encuentra, lo reemplaza con el carácter nulo '\0', lo que acorta la cadena para que termine antes del salto de línea.

    ### Forma de uso (en general):

        char cadena[];
        limpiarBuffers();
        LeerCadena(cadena,sizeof(cadena);)

## Imprimir Cadenas Centradas

La implementación de funciones para imprimir cadenas centradas en consola, o en un determinado ancho, resulta importante y útil para trabajar con textos centrados dentro del programa según se requiera.

- ### imprimirCadenaCentradaEnAncho(char *cadena, int ancho)

    Esta función está diseñada para imprimir una cadena de caracteres (char *cadena) centrada dentro de un ancho especificado (int ancho), de manera que se pueda lograr un centrado visualmente equilibrado.

    ``````
    void imprimirCadenaCentradaEnAncho(char *cadena, int ancho) {
      int longitudCadena = strlen(cadena);
      int espacios = (ancho - longitudCadena) / 2;
      int margenIzq = espacios;
      int margenDer = espacios;

      if ((ancho - longitudCadena) % 2 != 0) {margenDer++;}

      printf("%*s%s%*s",margenIzq,"",cadena,margenDer,"");
    }
    ``````

    1. **Parámetros**:

        `char *cadena`: Es un puntero que apunta a la cadena de caracteres que se imprimirá centrada.
        `int ancho`: Especifica el ancho total en el que se centrará la cadena.

    1. **Determinar la longitud de la cadena**:

        `int longitudCadena = strlen(cadena);`: Utiliza la función `strlen()` para calcular la longitud de la cadena de entrada.

    1. **Calcular espacios marginales**:

        `int espacios = (ancho - longitudCadena) / 2;`: Calcula la cantidad de espacios a insertar antes y después de la cadena para centrarla. Divide la diferencia entre el ancho total y la longitud de la cadena entre dos para distribuir los espacios de manera equitativa a ambos lados de la cadena.
        `int margenIzq = espacios;`: Establece la cantidad de espacios para el margen izquierdo.
        `int margenDer = espacios;`: Establece la cantidad de espacios para el margen derecho.

    1. **Ajuste de los márgenes si el ancho no es par**:

        `if ((ancho - longitudCadena) % 2 != 0) {margenDer++;}`: Si la diferencia entre el ancho total y la longitud de la cadena no es divisible exactamente por 2 (es decir, si el ancho no es par), se agrega un espacio extra al margen derecho para mantener la cadena centrada.

    1. **Imprimir la cadena centrada**:

        `printf("%*s%s%*s",margenIzq,"",cadena,margenDer,"");`: Utiliza `printf()` para imprimir la cadena centrada dentro del ancho especificado.
        - %*s: Especifica un número variable de espacios en blanco (margenIzq) antes de la cadena para centrarla.
        - %s: Imprime la cadena de caracteres (cadena) en su posición centrada.
        - %*s: Especifica un número variable de espacios en blanco (margenDer) después de la cadena para completar el centrado.

- ### imprimirCadenaCentradaEnConsola(const char *cadena)

    Esta función tiene como objetivo imprimir una cadena de caracteres centrada horizontalmente en la consola. Determina el ancho actual de la consola según el sistema operativo. Luego, calcula la cantidad de espacios necesarios para centrar horizontalmente la cadena dentro de la consola. Y, finalmente, imprime los espacios seguidos de la cadena proporcionada, logrando que esta última aparezca centrada en la consola.

    Es útil para presentar mensajes o texto en la consola de manera más estéticamente agradable y centrada, mejorando la legibilidad y el aspecto visual de la salida del programa.

    ``````
    void imprimirCadenaCentradaEnConsola(const char *cadena) {
      int ancho_consola;
      #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        ancho_consola = csbi.srWindow.Right - csbi.srWindow.Left + 1;
      #else
        struct winsize size;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        ancho_consola = size.ws_col;
      #endif

      int longitud_texto = strlen(cadena);
      int espacios = (ancho_consola - longitud_texto) / 2;

      for (int i = 0; i < espacios; ++i) {
        putchar(' ');
      }
      printf("%s\n", cadena);
    }
    ``````

    1. **Determinar el ancho de la consola**:

        En entornos Windows (_WIN32), se utiliza la función `GetConsoleScreenBufferInfo()` para obtener información sobre el búfer de la pantalla de la consola.
            `GetStdHandle(STD_OUTPUT_HANDLE)`: Obtiene el identificador del búfer de salida estándar.
            `ancho_consola = csbi.srWindow.Right - csbi.srWindow.Left + 1;`: Calcula el ancho de la consola restando la coordenada del borde derecho (Right) y la coordenada del borde izquierdo (Left) del área de la ventana de la consola y agrega 1 para obtener la cantidad total de columnas disponibles en la consola.
        En entornos Unix o similares, se utiliza `ioctl()` con `TIOCGWINSZ` para obtener el tamaño actual de la ventana del terminal en la estructura `winsize`, obteniendo el ancho de la consola a través de `size.ws_col`.

    1. **Calcular los espacios necesarios**:

        `int longitud_texto = strlen(cadena);`: Calcula la longitud de la cadena de texto proporcionada.
        `int espacios = (ancho_consola - longitud_texto) / 2;`: Calcula la cantidad de espacios necesarios para centrar la cadena dentro del ancho de la consola.

    1. **Imprimir la cadena centrada**:

        `for (int i = 0; i < espacios; ++i) { putchar(' '); }`: Imprime los espacios necesarios antes de la cadena para centrarla horizontalmente.
        `printf("%s\n", cadena);`: Imprime la cadena proporcionada seguida de un salto de línea para que la próxima salida comience en una nueva línea.
    
    ### Forma de uso (ejemplo):

        imprimirCadenaCentradaEnConsola("\n");
        imprimirCadenaCentradaEnConsola("Sistema Integral para TechSprint Innovations");
        imprimirCadenaCentradaEnConsola("\n");
        printf("[1] Gestion de Inventarios\n");
        printf("[2] Administracion de Recursos\n");
        printf("[3] Procesamiento de Transacciones\n");
        printf("[4] Herramientas de Analisis\n");
        printf("[0] Salir\n");
        ...

    ### Salida esperada por consola:

        |                                                     |
        |               Título del Menú/submenu               |
        |                                                     |
        |[1] Gestion de Inventarios                           |
        |[2] Administracion de Recursos                       |
        |[3] Procesamiento de Transacciones                   |
        |[4] Herramientas de Analisis                         |
        |[0] Salir                                            |
        ...

> [!IMPORTANT]
>
> Para el uso de esta función es necesario agregar la siguiente importación de librerías:
> ``````
>  #ifdef __unix__
>      #include <sys/ioctl.h>
>      #include <unistd.h>
>  #else
>      #include <windows.h>
>  #endif
> ``````
