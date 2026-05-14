/*
    
*/

#define _CRT_SECURE_NO_WARNINGS // Para omitir las advertencias de scanf inseguro o unsafe
#include <stdio.h>
#include <stdlib.h>

// Definición de códigos de color ANSI para la consola
#define RESET       "\x1b[0m"
#define CYAN        "\x1b[36m"
#define YELLOW      "\x1b[33m"
#define GREEN       "\x1b[32m"
#define RED         "\x1b[31m"
#define PURPLE      "\x1b[35m"
#define PURPLE_B    "\x1b[95m"
#define GRIS        "\x1b[90m"
#define ROJO        "\x1b[91m"
#define VERDE       "\x1b[92m"
#define YELLOW_B    "\x1b[93m"
#define AZUL        "\x1b[94m"
#define MORADO      "\x1b[95m"
#define AZUL_B      "\x1b[96m"
#define AUX    "\x1b[97m"
#define B_WHITE     "\x1b[47m"

void imprimir_acercade();

int main() {
    int opcion;

    do {
        // Limpiar la consola (Comando de Windows)
        system("cls");

        // Título y Subtítulo con colores
        printf(CYAN "========================================\n");
        printf("               BIT  QUEST               \n");
        printf("========================================\n" RESET);
        printf(YELLOW ">Hecho por Juan, Alejandro y Marco (JAM)         \n\n" RESET);

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
            imprimir_acercade();
            system("pause");
            break;
        case 4:
            printf(YELLOW "GRACIAS POR JUGAR!\n- JAM\n" RESET);
            // No hay pause aquí para que el programa termine directamente
            break;
        default:
            printf(ROJO "OPCION INVALIDA, SELECCIONA DEL 1 AL 4 y DA ENTER.\n" RESET);
            system("pause");
            break;
        }

    } while (opcion != 4); // El bucle se repite hasta que el usuario elija 4

    return 0;
}

// Función para imprimir información
void imprimir_acercade() {
    // Título
    printf(CYAN "\n========================================\n\tACERCA DE BIT QUEST\n========================================\n" RESET);
    printf("\n" PURPLE_B "MOVIMIENTO:" RESET VERDE " [W][A][S][D]" RESET);
    printf("\n" AUX "OBJETIVO: " YELLOW "[W][A][S][D]" RESET);
}