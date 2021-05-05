
INTRODUCCION

El TP1 cuenta con tres archivos: 
main.c, evento_pesca.c y evento_pesca.h

En el evento_pesca.c implementamos cinco funciones principales más dos que son para liberar memoria.

La primer función crear_arrecife recibe por parámetro un archivo (arrecife.txt) que se encarga de abrir,leer,reservar memoria y cerrar dicho archivo, devolviendo el arrecife con los datos del archivo.

La segunda crear_acuario no recibe nada por parámetro, y crea un acuario vacio (que apunta a NULL) y cantidad 0.

Dada unas condicones especificadas, la función trasladar_pokemon, saca del arrecife a los que cumplen la condición de la función pasada por parámetro.

La cuarta función imprime en pantalla la cantidad de pokemones que contiene.
El ultimo guarda en un archivo los pokemones que contiene.
Para finalizar, se liberan menoria tanto del acuario como el arrecife, se vale aclarar que ante cualquier comportamiento no esperado se validan algunas funciones para que liberen la memoria reservada.

EXPLICACION
La función crear_arrecife y trasladar pokemon me costaron más, mi algoritmo de trasladar pokemonn lo pense primero recorriendo el vector de
pokemones y verificando que tuviera la cantidad de pokemones seleccionados.
Despues redimensione la cantidad de vectores de pokeones del acuario.


Compilar:

gcc *.c -Wall -Werror -Wconversion -std=c99 -o evento_pesca

valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./evento_pesca


Ejecutar:

./evento_pesca

1.-Punteros.
    Es una manera de señalar y acceder a la direccion de memoria y al valor de esa memoria por cada variable declarada con su tipo.
2.-Aritmética de punteros.
    Es la matemática que usas para poder manejarte en los distintos espacios de memoria del heap y stack.
3.-Punteros a funciones.
   Se llaman por parámetro para poder usarlo en la función deseada, es un puntero a la función con un tipo y un parametro a su vez.
4.-Malloc y Realloc.
    Malloc es la función que se encarga de reservar memoria en el heap, para poder trabajar de manera dinámica. 
    Realloc se usa una vez ya reservamos memoria con malloc, redimensiona la memoria reservada por malloc y 
    recibe como parametros el puntero a malloc y la cantidad de memoria a la que voy a cambiar.


