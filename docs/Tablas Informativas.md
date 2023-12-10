# Tablas Informativas

Estas tablas se utilizan para brindar la información requerida para un cierto tipo de registros con el fin de optimizar la lectura de la información más relevante de dichos registros. En este sistema, se aplican a los registros requeridos y utilizados por la empresa.

## Estructura de una tabla

Una tabla debe tener la siguiente estructura, siguiendo el pensamiento anterior, al verse impresa por consola:

``````
| ETIQUETA 1 | ETIQUETA 2 |   ETIQUETA 3   | ... |
|------------|------------|----------------|-----|
| DATOS      |      DATOS |   OTROS DATOS  | ... |
| DATOS      |      DATOS |   OTROS DATOS  | ... |
|------------|------------|----------------|-----|
``````

> [!TIP]
> La alineación de los datos puede adecuarse según las características de la información representada. Ej.: IDs alineados a la izq, precios alineados a la derecha, nombres centrados, etc.

### Ejemplo a seguir para mostrar la información de los registros

- La información más importante es el **ID**
- Generalmente el nombre del registro es el siguiente dato más importante
- En las siguientes columnas de la tabla deben mostrarse los datos más esenciales del tipo de registro.
- Finalmente, en las últimas comlumnas, los datos de otros tipos de registros asociados al tipo de registro en cuestión.

### Ejemplo visual (de Productos)

``````
| ID |       TIPO        |     NOMBRE    |  PRECIO  |PROVEEDOR|
|----|-------------------|---------------|----------|---------|
|1   |    ELECTRONICA    |  Samsung G15  |  12456.67|   ID    |
|2   | ALIMENTOS_BEBIDAS | Gaseosa Brics |    250.00|   ID    |
|... | ................. | ............. | xxxxxx.xx|   ...   |
|----|-------------------|---------------|----------|---------|
``````