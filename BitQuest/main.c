/*
    MAIN.C
        - FUNCIÓN PRINCIPAL
        - MENÚ INICIAL
        - CONTROL GENERAL DEL JUEGO
*/

#define _CRT_SECURE_NO_WARNINGS // Para omitir las advertencias de scanf inseguro o unsafe
#include <stdio.h>
#include <stdlib.h>
#include "mapas.h"
#include "juego.h"
#include "juego.c"

//---------- Definición de Input para evitar usar ENTER - para Windows, Linux y con suerte Mac ---------//
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
    #define espera(tiempo) Sleep(tiempo)

#else
    #include <unistd.h>
    #include <termios.h>
    #include <sys/select.h>

    //Configuración que encontré por internet
    int _kbhit() {
        struct termios oldattr, newattr;
        struct timeval tv;
        fd_set rfds;
        int retval;

        tcgetattr(STDIN_FILENO, &oldattr);
        newattr = oldattr;
        newattr.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

        FD_ZERO(&rfds);
        FD_SET(STDIN_FILENO, &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 0;

        retval = select(STDIN_FILENO + 1, &rfds, NULL, NULL, &tv);
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

        return retval > 0;
    }

    //Configuración que encontré por internet, también
    int _getch() {
        struct termios oldattr, newattr;
        int ch;
        tcgetattr(STDIN_FILENO, &oldattr);
        newattr = oldattr;
        newattr.c_lflag &= ~(ICANON | ECHO);

        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);

        return ch;
    }

    void espera(long tiempo) {
        usleep(tiempo * 1000);
    }
#endif

#define pausa()   printf("Presiona una tecla para continuar... "); _getch()


void imprimir_acercade_1();
void imprimir_acercade_2();
// void menu();

int main() {
    Jugador j;
    int opcion;

    j = encontrar_jugador(mapa, 60, 60);

    do {
        // Limpieza de consola
        printf(_LIMPIAR);
        // Título y Subtítulo con colores
        printf(_RGB(170, 50, 230));
        printf("==================================================\n");
        printf("                    BIT  QUEST                    \n");
        printf("==================================================\n" RESET);
        printf(_RGB(16, 16, 16) _FRGB(235, 125, 20) _CONSOLA(3m));
        printf(">Hecho por Juan, Rodrigo, Alejandro y Marco (JRAM)\n\n" RESET);

        // Menú de 4 opciones
        printf(VERDE "[1]" RESET " JUGAR\n");
        printf(VERDE "[2]" RESET " OP2\n");
        printf(VERDE "[3]" RESET " ACERCA DEL JUEGO\n");
        printf(ROJO  "[4]" RESET " SALIR DEL JUEGO\n\n");

        printf("INGRESE UNA OPCION (1-4)\n");

        // Leer la entrada del usuario
        opcion = _getch() - '0';
        printf(RESET "\n");

        // Evaluar la opción seleccionada
        switch (opcion) {
        case 1:
            //Por qué cargaría un juego rancio de consola que pesa como 3 kilobytes???
            printf(CYAN "CARGANDO JUEGO...\n" RESET);
            dibujar_mapa(mapa, 60, 60, j);
            espera(3000);
            break;
        case 2:
            printf(CYAN "Has seleccionado la Opción 2\n" RESET);
            espera(1000);
            break;
        case 3:
            imprimir_acercade_1();
            pausa();
            imprimir_acercade_2();
            pausa();
            break;
        case 4:
            printf(YELLOW "GRACIAS POR JUGAR!\n- JRAM\n" RESET);
            // No hay pause aquí para que el programa termine directamente
            break;
        default:
            printf(ROJO "> OPCION INVALIDA,\n  SELECCIONA DEL 1 AL 4.\n  PRESIONA ENTER PARA REGRESAR\n" RESET);
            while (_getch() != '\r');
            break;
        }

    } while (opcion != 4); // El bucle se repite hasta que el usuario elija 4

    return 0;
}

// Función para imprimir información
void imprimir_acercade_1() {
    // Limpiar pantalla
    printf(_LIMPIAR);
    
    // Título
    printf(_RGB(170, 50, 230));
    printf("====================================================\n");
    printf("\tACERCA DE BIT QUEST" _RGB(190, 105, 220) _CONSOLA(3m) " Programado por JRAM" _CONSOLA(0m) _RGB(170, 50, 230));
    printf("\n=========================================");
    printf(_FRGB(170, 50, 230) NEGRO " PARTE 1/2 \n" RESET);

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
    // Limpiar pantalla
    printf(_LIMPIAR);

    // Título
    printf(_RGB(170, 50, 230));
    printf("====================================================\n");
    printf("\tACERCA DE BIT QUEST" _RGB(190, 105, 220) _CONSOLA(3m) " Programado por JRAM" _CONSOLA(0m) _RGB(170, 50, 230));
    printf("\n=========================================");
    printf(_FRGB(170, 50, 230) NEGRO " PARTE 2/2 \n" RESET);

    // Explicación niveles
    printf("\n" MORADO "NIVELES:\n" VERDE "[NIVEL #]" MORADO ":" RESET " Descripcion del nivel.\n");
    printf("\n" VERDE "[Nivel 1]" MORADO ":" RESET " Laberinto sencillo, no hay dificultad.");
    printf("\n" VERDE "[Nivel 2]" MORADO ":" RESET " Mas caminos y monedas, intermedio.");
    printf("\n" VERDE "[Nivel 3]" MORADO ":" RESET " Enorme y confuso, explotador.\n");

    // Creditos
    printf("\n" MORADO "\n> " NEGRO B_WHITE " Universidad Autonoma de Aguascalientes                          " RESET);
    printf("\n" MORADO "\n> " NEGRO B_WHITE " Ingenieria en Sistemas Computacionales                          " RESET);
    printf("\n" MORADO "\n> " NEGRO B_WHITE " Lenguaje Ensamblador: Proyecto Final                            " RESET);
    printf("\n" MORADO "\n> " NEGRO B_WHITE " Juan Robles, Rodrigo Garcia, Eduardo Organista y Marco Corrales " RESET);
    printf("\n" MORADO "\n> " NEGRO B_WHITE " Programado en C + NASM de 64 bits                               " RESET "\n\n");
}