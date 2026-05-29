#pragma once
#include <stdio.h>

#define MAX_VISIBLE_X 20
#define MAX_VISIBLE_Y 20

struct Jugador {
	int x, y;
	int monedas;
	int llaves;
	int cant_pasos;
};

void dibujar_informacion(Jugador, int);
void dibujar_mapa(char*, int, int, Jugador);

void mover_jugador(char*, int, int, int, int);			//Podría ser en asm (movería al player)
bool verificar_jugador(char*, int, int, int);			//ASM (verificaría la posición del jugador y si es válida)
bool nivel_completado(char*, int, int);					//Podría ser en asm (verificaría si el jugador llegó a la salida)
int cantidad_caracter(char*, int, int);					//ASM (devolvería la cantidad de 'caracter' en el mapa)
int calcular_puntuaje(int, int, int);					//ASM
bool verificar_objeto(char*, int, int, int, int);		//ASM
int celdas_libres(char*, int);							//ASM
