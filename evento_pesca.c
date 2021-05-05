#include "evento_pesca.h"
#include <stdlib.h>
#include <string.h>

#define CAMPOS_ESPERADOS 4
#define FORMATO_LECTURA "%99[^;];%i;%i;%[^\n]\n"
#define FORMATO_ESCRITURA "%s;%d;%d;%s\n"

arrecife_t* crear_arrecife(const char* ruta_entrada){
    FILE* archivo = fopen(ruta_entrada,"r"); 
    if (!archivo){
        return NULL;
	}
	pokemon_t pokemon;
    arrecife_t* arrecife = malloc(sizeof(arrecife_t)); 
    if (!arrecife){
        fclose(archivo);
        free(arrecife->pokemon);
        free(arrecife);
        return NULL;
	}
	arrecife->pokemon = NULL;
    arrecife->cantidad_pokemon = 0;

    int campos_leidos = fscanf(archivo,FORMATO_LECTURA,pokemon.especie,&pokemon.velocidad,&pokemon.peso,pokemon.color);
    if(campos_leidos!=4){
        fclose(archivo);
        free(arrecife->pokemon);
		free(arrecife);
        return NULL;
    }
    while(campos_leidos == CAMPOS_ESPERADOS){ 
        arrecife->cantidad_pokemon++;
        
        pokemon_t* auxiliar = realloc(arrecife->pokemon,(size_t)(arrecife->cantidad_pokemon)*sizeof(pokemon_t));
        if(!auxiliar) { 
            arrecife->cantidad_pokemon--;
            fclose(archivo);
            return NULL;
        }
        arrecife->pokemon = auxiliar;
        auxiliar[arrecife->cantidad_pokemon-1] = pokemon;
        campos_leidos = fscanf(archivo,FORMATO_LECTURA,pokemon.especie,&pokemon.velocidad,&pokemon.peso,pokemon.color);
    }
    fclose(archivo);
    return arrecife;
}

acuario_t* crear_acuario(){
    acuario_t* acuario = NULL;
	acuario = malloc(sizeof(acuario_t)); 
	if (!acuario)
		return NULL;

	acuario->pokemon = NULL;
	acuario->cantidad_pokemon = 0;
	return acuario;
}

int trasladar_pokemon(arrecife_t* arrecife, acuario_t* acuario, bool (*seleccionar_pokemon) (pokemon_t*), int cant_seleccion){
    if(!arrecife){
        return -1;
    }
    if(!acuario){
        return -1;
    }
    int i=0;
    int cant_pokemones_trasladables = 0;
    int pokemones_totales = arrecife->cantidad_pokemon;
    int cantidad_acuario = acuario->cantidad_pokemon; 

    while(cant_seleccion!=cant_pokemones_trasladables){
        if (i==pokemones_totales){
            return -1;
        }
        if (seleccionar_pokemon(arrecife->pokemon+i)){ 
            cant_pokemones_trasladables++;
        }
        i++;
    }
    if (cant_pokemones_trasladables==0){ 
        return 0;
    }
    pokemon_t* auxiliar = realloc(acuario->pokemon,(size_t)(cantidad_acuario+cant_seleccion)*sizeof(pokemon_t));
    if(!auxiliar){
        return -1;
    }
    acuario->pokemon = auxiliar;
    i=0;
    int n=0;
    //agrego al acuario y elimino del arrecife los pokemones que cumplen la condición
    while(i <= (pokemones_totales-cant_seleccion)){ 
        if(i==pokemones_totales-1 || cant_seleccion == n){ //para la última posicion del arreglo
            pokemon_t* auxiliar = realloc(arrecife->pokemon,(size_t)(pokemones_totales-cant_seleccion)*sizeof(pokemon_t));
            arrecife->pokemon = auxiliar;
            return 0;
        }
        if(seleccionar_pokemon(arrecife->pokemon+i)){ // false avanzo +i true no avanzo +i
            arrecife->cantidad_pokemon--;
            acuario->pokemon[acuario->cantidad_pokemon] = ((*arrecife).pokemon)[i]; //agregando
            acuario->cantidad_pokemon++;
            n++;
            for(int j=0;j<pokemones_totales-(i+1);j++){
                ((*arrecife).pokemon)[i+j] = ((*arrecife).pokemon)[i+j+1]; //eliminando 
            }
        }
        if(!seleccionar_pokemon(arrecife->pokemon+i)){
            i++;
        }
    }
    return -1;
}

void censar_arrecife(arrecife_t* arrecife, void (*mostrar_pokemon)(pokemon_t*)){
    int cantidad = arrecife->cantidad_pokemon;
    for(int i=0;i<cantidad;i++){
        mostrar_pokemon(arrecife->pokemon+i);
    }
}

int guardar_datos_acuario(acuario_t* acuario, const char* ruta_salida){
    FILE* archivo = fopen(ruta_salida,"w");
    if (!archivo){
		fclose(archivo);
        return -1;
	}
    int cantidad = acuario->cantidad_pokemon;
    for(int i=0;i<cantidad;i++){
        fprintf(archivo,FORMATO_ESCRITURA,acuario->pokemon[i].especie,acuario->pokemon[i].velocidad,acuario->pokemon[i].peso,acuario->pokemon[i].color);
    }
    fclose(archivo);
    return 0;
}

void liberar_acuario(acuario_t* acuario) {
    if(!acuario){
        free(acuario);
    }
    free(acuario->pokemon);
	free(acuario);
}

void liberar_arrecife(arrecife_t* arrecife){
    if(!arrecife){
        free(arrecife);
    }
	free(arrecife->pokemon);
	free(arrecife);
}