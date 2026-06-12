#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "juego.h"

//Funciones para jugar con el color del texto en consola
void color_rgb(int r, int g, int b) {
    //Decide dibujar un color[38], luego especifica su rango[2] y su RGB
    printf("\x1b[38;2;%d;%d;%dm", r, g, b);
}

void fondo_rgb(int r, int g, int b) {
    //Decide dibujar un fondo[48], luego especifica su rango[2] y su RGB
    printf("\x1b[48;2;%d;%d;%dm", r, g, b);
}

void ajustar_cursor(int x, int y) {
    printf("\x1b[%d;%dH", x, y);
}

void dibujar_mapa(char** mapa, int ren, int col, Jugador j) {
    int min_x, min_y, max_x, max_y;

    //Ajustar ventana visible
    //En horizontal/ X
    //El jugador está más a la izquierda
    if (j.x < MAX_VISIBLE_X / 2) {
        min_x = 0; max_x = MAX_VISIBLE_X;
    }
    //Más a la derecha
    else if (j.x > col - MAX_VISIBLE_X / 2) {
        min_x = col - MAX_VISIBLE_X; max_x = col;
    }
    //Enmedio
    else {
        min_x = j.x - MAX_VISIBLE_X / 2;
        max_x = j.x + MAX_VISIBLE_X / 2;
    }

    //En vertical/ Y
    //El jugador está más a arriba
    if (j.y < MAX_VISIBLE_Y / 2) {
        min_y = 0; max_y = MAX_VISIBLE_Y;
    }
    //Más a abajo
    else if (j.y > ren - MAX_VISIBLE_Y / 2) {
        min_y = ren - MAX_VISIBLE_Y; max_y = ren;
    }
    //Enmedio
    else {
        min_y = j.y - MAX_VISIBLE_Y / 2;
        max_y = j.y + MAX_VISIBLE_Y / 2;
    }

    //Marcos tipo matrix
    fondo_rgb(16, 48, 24);
    color_rgb(8, 255, 32);
    printf("%c", 201);
    for (int y = 0; y < MAX_VISIBLE_Y; y++) {
        printf("%c%c", 205, 205);
    }
    printf("%c\n", 187);

    for (int x = min_x; x < max_x; x++) {
        //Marco izquierdo
        fondo_rgb(16, 48, 24);
        color_rgb(8, 255, 32);
        printf("%c", 186);

        for (int y = min_y; y < max_y; y++) {
            color_rgb(255, 255, 255);
            fondo_rgb(0, 0, 0);
            switch (mapa[x][y]) {
            case '#':
                color_rgb(255, 255, 255);
                printf("%c%c", 219, 219);
                break;

            case '.':
                printf("  ");
                break;

            case 'P':
                printf("()");
                break;

            case 'M':
                color_rgb(192, 128, 32);
                printf("$ ", 184);
                break;

            case 'K':
                color_rgb(192, 192, 224);
                printf("O%c", 170);
                break;

            case 'D':
                color_rgb(255, 170, 90);
                fondo_rgb(175, 95, 20);
                printf(" %c", 170);
                break;

            case 'E':
                color_rgb(0, 0, 0);
                fondo_rgb(250, 55, 15);
                printf("[]");
                break;

            case '\0':
                printf("");
                break;

            default:
                color_rgb(255, 0, 255);
                printf("ER");
                break;
            }
        }
        //Marco derecho
        fondo_rgb(16, 48, 24);
        color_rgb(8, 255, 32);
        printf("%c", 186);
        //Salto de línea sin dibujar de más
        color_rgb(255, 255, 255);
        fondo_rgb(0, 0, 0);
        printf("\n");
    }

    //Marco inf tipo matrix
    fondo_rgb(16, 48, 24);
    color_rgb(8, 255, 32);
    printf("%c", 200);
    for (int y = 0; y < MAX_VISIBLE_Y; y++) {
        printf("%c%c", 205, 205);
    }
    printf("%c\n", 188);
}

void dibujar_informacion(Jugador j, int max_coins) {
    fondo_rgb(16, 48, 24);
    color_rgb(8, 255, 32);
    printf(_CONSOLA(3m) " $ ");
    //Dibujar monedas sin romper el diseño
    if (j.monedas < 10)         printf("   %d", j.monedas);
    else if (j.monedas < 100)   printf("  %d", j.monedas);
    else if (j.monedas < 1000)  printf(" %d", j.monedas);
    else                        printf("%d", j.monedas);
    printf("/");
    if (max_coins < 10)         printf("   %d", max_coins);
    else if (max_coins < 100)   printf("  %d", max_coins);
    else if (max_coins < 1000)  printf(" %d", max_coins);
    else                        printf("%d", max_coins);

    printf(" %c POS ", 175);
    //Dibujar posición sin romper el diseño
    //en x
    if (j.x < 10)         printf("  %d", j.x);
    else if (j.x < 100)   printf(" %d", j.x);
    else                  printf("%d", j.x);
    printf(", ");
    //en y
    if (j.y < 10)         printf("  %d", j.y);
    else if (j.y < 100)   printf(" %d", j.y);
    else                  printf("%d", j.y);
    printf(" %c ", 174);
    //Dibujar las llaves
    for (int i = j.llaves > 5 ? 5: j.llaves; i > 0; i--) {
        printf("O%c", 170);

        //Último caracter, si son más llaves, se pone un +
        if (i == 1) {
            if (j.llaves > 5) {
                printf("+");
            }
            else {
                printf(" ");
            }
        }
    }
    //Espacio extra, de todas formas
    if (j.llaves == 0) {
        printf(" ");
    }
    //Espacios de llaves extra
    for (int i = 5 - j.llaves; i > 0; i--) {
        printf("  ");
    }
    printf(" \n" RESET);
}

void dibujar_resultados(Jugador j, int max_coins, int puntuacion, int espacios) {
    fondo_rgb(16, 48, 24);
    color_rgb(8, 255, 32);

    //Marcos tipo matrix
    fondo_rgb(16, 48, 24);
    color_rgb(8, 255, 32);
    printf("%c", 201);
    for (int y = 0; y < MAX_VISIBLE_Y; y++) {
        printf("%c%c", 205, 205);
    }
    printf("%c\n", 187);

    for (int x = 0; x < MAX_VISIBLE_X; x++) {
        //Marco izquierdo
        fondo_rgb(16, 48, 24);
        color_rgb(8, 255, 32);
        printf("%c", 186);

        if (x == MAX_VISIBLE_X / 2 - 1) {
            printf("        Cantidad de pasos: %d  ", j.cant_pasos);
        }
        else if (x == MAX_VISIBLE_X / 2) {
            printf("      Relacion de monedas: %.2f  ", ((float)j.monedas) / max_coins);
        }
        else if (x == MAX_VISIBLE_X / 2) {
            printf("  Celdas vacias del nivel: %d  ", espacios);
        }
        //Dibujado
        else {
            for (int y = 0; y < MAX_VISIBLE_Y; y++) {
                fondo_rgb(0, 0, 0);
                color_rgb(0, 0, 0);
                printf("  ");
            }
        }
        //Marco derecho
        fondo_rgb(16, 48, 24);
        color_rgb(8, 255, 32);
        printf("%c", 186);
        //Salto de línea sin dibujar de más
        color_rgb(255, 255, 255);
        fondo_rgb(0, 0, 0);
        printf("\n");
    }

    //Marco inf tipo matrix
    fondo_rgb(16, 48, 24);
    color_rgb(8, 255, 32);
    printf("%c", 200);
    for (int y = 0; y < MAX_VISIBLE_Y; y++) {
        printf("%c%c", 205, 205);
    }
    printf("%c\n", 188);
}

Jugador encontrar_jugador(char** mapa, int ren, int col) {
    Jugador new_jugador;

    for (int x = 0; x < ren; x++) {
        for (int y = 0; y < col; y++) {
            if (mapa[x][y] == 'P') {
                new_jugador.x = x;
                new_jugador.y = y;
                return new_jugador;
            }
        }
    }

    new_jugador.x = 0;
    new_jugador.y = 0;

    return new_jugador;
}

void mover_jugador(char** mapa, int x1, int y1, int x2, int y2) {
    char temp = mapa[x1][y1];
    mapa[x1][y1] = mapa[x2][y2];
    mapa[x2][y2] = temp;
}

int nivel_completado(char** mapa, int x, int y, int salida_x, int salida_y) {
    return x == salida_x && y == salida_y;
}