#include "evento_pesca.h"
#include <string.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
/*

* Funciones que determinan los Pokémon que serán movidos al acuario:
* - Como mínimo es necesario crear 5.
* - Ejemplos:
* - - Sólo pokémon pertenecientes a la especie "Magikarp ".
* - - Sólo pokémon que tengan color rojo y velocidad menor a 10.
* - - Etc. sean creativos!
*/
bool peso_igual_320(pokemon_t* pokemon){
	int peso = pokemon->peso;
	if(peso ==320){
		return TRUE;
	}
	return FALSE;
}

bool velocidad_igual_50(pokemon_t* pokemon){
	int velocidad=pokemon->velocidad;
	if (velocidad==50){
		return TRUE;
	}
	return FALSE;
}

bool peso_velocidad_mayor_23(pokemon_t* pokemon){
	int peso = pokemon->peso, velocidad = pokemon->velocidad;
	if (peso > 23 && velocidad > 23){
		return TRUE;
	}
	return FALSE;
}

bool peso_menor_10(pokemon_t* pokemon){
	int peso = pokemon->peso;
	if(peso>=10){
		return FALSE;
	}
	return TRUE;
}

bool velocidad_mayor_20(pokemon_t* pokemon){
	int velocidad = pokemon->velocidad;
	if (velocidad>20){
		return TRUE;
	}
	return FALSE;
}

void mostrar_pokemon(pokemon_t* pokemon){
	printf("%s;%d;%d;%s\n",pokemon->especie,pokemon->velocidad,pokemon->peso,pokemon->color);
}

int main (){
	/* Crear las estructuras a utilizar */
	arrecife_t* arrecife = crear_arrecife("arrecife.txt");
	if(!arrecife){
		return 0;
	}
	acuario_t* acuario = crear_acuario();
	
	/* Trasladar por 1ra vez con cierta función */
	int traslado_exitoso = trasladar_pokemon(arrecife,acuario,peso_menor_10,1);
	if (traslado_exitoso){ //con -1 entra
		liberar_acuario(acuario);
		liberar_arrecife(arrecife);
		return 0;
	}
	/* Listar a los pokémon que continúan en el arrecife */
	censar_arrecife(arrecife, mostrar_pokemon);
	/* Trasladar por 2da vez con cierta función */
	traslado_exitoso = trasladar_pokemon(arrecife,acuario,velocidad_mayor_20,2);
	if (traslado_exitoso){
		liberar_acuario(acuario);
		liberar_arrecife(arrecife);
		return 0;
	}
	/* Listar a los pokémon que continúan en el arrecife */
	censar_arrecife(arrecife, mostrar_pokemon);

	/* Trasladar por N-écima vez con cierta función */
	traslado_exitoso = trasladar_pokemon(arrecife,acuario,peso_velocidad_mayor_23,1);
	if (traslado_exitoso){
		liberar_acuario(acuario);
		liberar_arrecife(arrecife);
		return 0;
	}
	/* Listar a los pokémon que continúan en el arrecife */
	censar_arrecife(arrecife, mostrar_pokemon);

	/* Guardar los pokémon del acuario */
	int guardado_exitoso = guardar_datos_acuario(acuario,"acuario.txt");
	printf("Guardado_exitoso: %d\n",guardado_exitoso);
	/* Liberar memoria */
	liberar_acuario(acuario);
	liberar_arrecife(arrecife);
	return 0;
}

