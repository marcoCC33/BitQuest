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

    for (int x = min_x; x < max_x; x++) {
        for (int y = min_y; y < max_y; y++) {
            printf(_LIMPIAR);
            switch (toupper(mapa[x][y])) {
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
                printf("%c ", 184);
                break;

            case 'K':
                color_rgb(96, 96, 112);
                printf("O%c", 170);
                break;

            case 'D':
                color_rgb(0, 0, 0);
                fondo_rgb(96, 96, 112);
                printf("%c%c", 204, 185);
                break;

            case 'E':
                color_rgb(0, 0, 0);
                fondo_rgb(64, 255, 192);
                printf("[]");
                break;

            default:
                color_rgb(255, 0, 255);
                fondo_rgb(0, 255, 0);
                printf("ER");
                break;
            }
        }
        printf("\n");
    }
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
}