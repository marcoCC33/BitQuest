#pragma once
#include <stdio.h>

#define MAX_VISIBLE_X 20
#define MAX_VISIBLE_Y 20

// Definición de códigos de color ANSI para la consola
#define RESET       "\x1b[0m"
#define NEGRO        "\x1b[30m"
#define RED         "\x1b[31m"
#define GREEN       "\x1b[32m"
#define YELLOW      "\x1b[33m"
#define BLUE        "\x1b[34m"
#define PURPLE      "\x1b[35m"
#define CYAN        "\x1b[36m"
#define WHITE        "\x1b[37m"
#define GRIS        "\x1b[90m"
#define ROJO        "\x1b[91m"
#define VERDE       "\x1b[92m"
#define YELLOW_B    "\x1b[93m"
#define AZUL        "\x1b[94m"
#define MORADO      "\x1b[95m"
#define AZUL_B      "\x1b[96m"
#define B_WHITE     "\x1b[47m"

//Definiciones para jugar con la consola de CUALQUIER LADO
#define _LIMPIAR    "\ec\e[?25l"
#define _CONSOLA(ordenes) "\x1b[" #ordenes
#define _RGB(r, g, b) "\x1b[38;2;"#r";"#g";"#b"m"
#define _FRGB(r, g, b) "\x1b[48;2;"#r";"#g";"#b"m"

typedef struct {
	int x, y;
	int monedas;
	int llaves;
	int cant_pasos;
} Jugador;

void dibujar_informacion(Jugador, int);
void dibujar_mapa(char**, int, int, Jugador);

Jugador encontrar_jugador(char**, int, int);
// funciones para  rutinas.ASM
int verificar_jugador(char*, int max_col, int x, int y);						// Verifica la posicion propuesta de movimiento y retorna un 1 si es valida o un 0 si no
int nivel_completado(char** mapa, int x, int y, int salida_x, int salida_y);	//Podría ser en asm (verificaría si el jugador llegó a la salida)
int cantidad_caracter(char*, int, int);											//ASM (devolvería la cantidad de 'caracter' en el mapa)
int calcular_puntuaje(int, int, int);											//ASM
int verificar_objeto(char*, int, int, int, int);								// Devuelve un 1 si está el objeto o un 0 si no está, verifica si existe un determinado objeto
int celdas_libres(char*, int);													//ASM
void encontrar_salida(char*, int*, int*, int, int);
void mover_jugador(char* mapa, int x1, int y1, int x2, int y2);				//(movería al player)

//Dibujado etcétera
void color_rgb(int, int, int);
void fondo_rgb(int, int, int);
void ajustar_cursor(int, int);
