/*
    MAIN.C
        - FUNCIÓN PRINCIPAL
        - MENÚ INICIAL
        - CONTROL GENERAL DEL JUEGO
*/

#define _CRT_SECURE_NO_WARNINGS // Para omitir las advertencias de scanf inseguro o unsafe
#include <stdio.h>
#include <stdlib.h>

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

void imprimir_acercade_1();
void imprimir_acercade_2();
// void menu();

int main() {
    int opcion;

    do {
        // Limpiar la consola (Comando de Windows)
        system("cls");

        // Título y Subtítulo con colores
        printf(CYAN "========================================\n");
        printf("               BIT  QUEST               \n");
        printf("========================================\n" RESET);
        printf(YELLOW ">Hecho por Juan, Alejandro y Marco (JAM)\n\n" RESET);

        // Menú de 4 opciones
        printf(VERDE "[1]" RESET " JUGAR\n");
        printf(VERDE "[2]" RESET " OP2\n");
        printf(VERDE "[3]" RESET " ACERCA DEL JUEGO\n");
        printf(ROJO "[4]" RESET " SALIR DEL JUEGO\n\n");

        printf("INGRESE UNA OPCION (1-4)\n" VERDE "> ");

        // Leer la entrada del usuario
        if (scanf("%d", &opcion) != 1) {
            // Limpiar el buffer si el usuario ingresa una letra en lugar de un número
            while (getchar() != '\n');
            opcion = 0;
        }

        printf(RESET "\n");

        // Evaluar la opción seleccionada
        switch (opcion) {
        case 1:
            printf(CYAN "CARGANDO JUEGO...\n" RESET);
            system("pause"); // Pausar para que el usuario pueda leer el mensaje
            break;
        case 2:
            printf(CYAN "Has seleccionado la Opción 2\n" RESET);
            system("pause");
            break;
        case 3:
            imprimir_acercade_1();
            system("pause");
            imprimir_acercade_2();
            system("pause");
            break;
        case 4:
            printf(YELLOW "GRACIAS POR JUGAR!\n- JAM\n" RESET);
            // No hay pause aquí para que el programa termine directamente
            break;
        default:
            printf(ROJO "> OPCION INVALIDA,\n  SELECCIONA DEL 1 AL 4 y DA ENTER.\n\n" RESET);
            system("pause");
            break;
        }

    } while (opcion != 4); // El bucle se repite hasta que el usuario elija 4

    return 0;
}

// Función para imprimir información
void imprimir_acercade_1() {
    // Limpiar pantalla (Windows)
    system("cls");
    
    // Título
    printf(CYAN "====================================================\n\tACERCA DE BIT QUEST"YELLOW " Programado por JAM" CYAN "\n===========================================");
    printf(NEGRO B_WHITE "PARTE 1/2\n" RESET);

    // Instrucciones de movimiento
    printf("\n" MORADO "MOVIMIENTO:\n" VERDE "[TECLA]" MORADO ":" RESET " DIRECCION DE MOVIMIENTO.\n");
    printf("\n" VERDE "[W]" MORADO ":" RESET " Mover hacia arriba.");
    printf("\n" VERDE "[A]" MORADO ":" RESET " Mover hacia la izquierda.");
    printf("\n" VERDE "[S]" MORADO ":" RESET " Mover hacia abajo.");
    printf("\n" VERDE "[D]" MORADO ":" RESET " Mover hacia la derecha.");
    printf("\n" VERDE "[Q]" MORADO ":" RESET " Salir del juego (dentro del juego).\n");
    
    // Objetivo del juego
    printf("\n" MORADO "OBJETIVO:" YELLOW " Recorrer el mapa, recolectar monedas,\n encontrar la llave y llegar a la salida.\n" RESET);
    printf("\n" MORADO "ELEMENTOS DEL MAPA:\n" GREEN "[SIMBOLO]" MORADO ":" RESET " SIGNIFICADO.\n");

    // Simbología del juego
    printf("\n" VERDE "[" AZUL_B "#" VERDE "]" MORADO ":" RESET " Pared, no se puede pasar.");
    printf("\n" VERDE "[" GRIS "." VERDE "]" MORADO ":" RESET " Camino libre, transitable.");
    printf("\n" VERDE "[" WHITE "P" VERDE "]" MORADO ":" RESET " Personaje.");
    printf("\n" VERDE "[" YELLOW_B "M" VERDE "]" MORADO ":" RESET " Moneda.");
    printf("\n" VERDE "[" GRIS "K" VERDE "]" MORADO ":" RESET " Llave.");
    printf("\n" VERDE "[" AZUL_B "D" VERDE "]" MORADO ":" RESET " Puerta, requiere llave.");
    printf("\n" VERDE "[" RED "E" VERDE "]" MORADO ":" RESET " Salida, terminar el nivel.\n\n\n");
}

void imprimir_acercade_2(){
    // Limpiar pantalla (Windows)
    system("cls");

    // Título
    printf(CYAN "====================================================\n\tACERCA DE BIT QUEST"YELLOW " Programado por JAM" CYAN "\n===========================================");
    printf(NEGRO B_WHITE "PARTE 2/2\n" RESET);

    // Explicación niveles
    printf("\n" MORADO "NIVELES:\n" VERDE "[NIVEL #]" MORADO ":" RESET " Descripcion del nivel.\n");
    printf("\n" VERDE "[Nivel 1]" MORADO ":" RESET " Laberinto sencillo, no hay dificultad.");
    printf("\n" VERDE "[Nivel 2]" MORADO ":" RESET " Mas caminos y monedas, intermedio.");
    printf("\n" VERDE "[Nivel 3]" MORADO ":" RESET " Enorme y confuso, retador.\n");

    // Creditos
    printf("\n" MORADO "\n> " NEGRO B_WHITE " Universidad Autonoma de Aguascalientes          " RESET);
    printf("\n" MORADO "\n> " NEGRO B_WHITE " Ingenieria en Sistemas Computacionales          " RESET);
    printf("\n" MORADO "\n> " NEGRO B_WHITE " Lenguaje Ensamblador: Proyecto Final            " RESET);
    printf("\n" MORADO "\n> " NEGRO B_WHITE " Juan Robles, Eduardo Organista y Marco Corrales " RESET);
    printf("\n" MORADO "\n> " NEGRO B_WHITE " Prgogramado en C + NASM de 64 bits              " RESET "\n\n");
}