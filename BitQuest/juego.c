#include <ctype.h>
#include <math.h>
#include <stdbool.h>
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

void imprimir_objeto(char caracter, float oscuro) {
    color_rgb(255 * oscuro, 255 * oscuro, 255 * oscuro);
    fondo_rgb(0, 0, 0);
    switch (caracter) {
    case '#':
        color_rgb(255 * oscuro, 255 * oscuro, 255 * oscuro);
        printf("%c%c", 219, 219);
        break;

    case '.':
        printf("  ");
        break;

    case 'P':
        printf("()");
        break;

    case 'M':
        color_rgb(255 * oscuro, 192 * oscuro, 128 * oscuro);
        printf("$ ");
        break;

    case 'K':
        color_rgb(192 * oscuro, 192 * oscuro, 224 * oscuro);
        printf("O%c", 170);
        break;

    case 'D':
        color_rgb(255 * oscuro, 170 * oscuro, 90 * oscuro);
        fondo_rgb(175 * oscuro, 95 * oscuro, 20 * oscuro);
        printf(" %c", 170);
        break;

    case 'E':
        color_rgb(0, 0, 0);
        fondo_rgb(250 * oscuro, 55 * oscuro, 15 * oscuro);
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

void dibujar_mapa(char** mapa, int ren, int col, Jugador j) {
    int min_x, min_y, max_x, max_y;

    //Ajustar ventana visible
    //En horizontal/ X
    //El jugador está más a la izquierda
    if (j.x < MAX_VISIBLE_X / 2) {
        min_x = 0; max_x = MAX_VISIBLE_X;
    }
    //Más a la derecha
    else if (j.x > ren - MAX_VISIBLE_X / 2) {
        min_x = ren - MAX_VISIBLE_X; max_x = ren;
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
    else if (j.y > col - MAX_VISIBLE_Y / 2 - 1) {
        min_y = col - MAX_VISIBLE_Y - 1; max_y = col;
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
            imprimir_objeto(mapa[x][y], 1);
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

void dibujar_informacion(Jugador j, int max_coins, int nivel) {
    fondo_rgb(16, 48, 24);
    color_rgb(8, 255, 32);

    printf(_CONSOLA(3m));
    for (int i = 17; i > 0; i--) printf(" ");
    printf("NIVEL %d", nivel);
    for (int i = 18; i > 0 && pow(10, i) > nivel; i--) printf(" ");
    printf("\n");

    printf(" $ ");
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

void dibujar_resultados(char** mapa, Jugador j, int max_coins, int puntuacion, int espacios, int pasos) {
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

        //Títulos
        if (x == 3) {
            printf("          << FIN DEL NIVEL >>           ");
        }
        //CANTIDAD DE PASOS
        else if (x == MAX_VISIBLE_X / 2 - 4) {
            printf("        Cantidad de pasos: %d", pasos);

            //Imprime la cantidad necesaria de espacios
            for (int i = 12; i > 0 && pow(10, i) > pasos; i--) {
                printf(" ");
            }
        }
        //TOTAL DE MONEDAS CONSEGUIDAS
        else if (x == MAX_VISIBLE_X / 2 - 3) {
            bool monedas_cero = false;
            printf("      Monedas conseguidas: %d/ %d", j.monedas, max_coins);
            if (j.monedas == 0) {
                j.monedas = 1;
                monedas_cero = true;
            }

            //Imprime la cantidad necesaria de espacios
            for (int i = 9; i > 0 && pow(10, i) > j.monedas * max_coins; i--) {
                printf(" ");
            }

            if (monedas_cero) j.monedas = 0;
        }
        //PORCENTAJE DE MONEDAS RECOLECTADAS
        else if (x == MAX_VISIBLE_X / 2 - 2) {
            float relacion = 0;
            //Evita explosiones
            if (max_coins > 0) {
                relacion = (float)(j.monedas) / max_coins * 100;
            }
            printf("      Relacion de monedas: %.2f%%", relacion);

            //Imprime la cantidad necesaria de espacios
            for (int i = 8; i > 0 && pow(10, i) > relacion; i--) {
                printf(" ");
            }
        }
        //CELDAS VACÍAS
        else if (x == MAX_VISIBLE_X / 2 - 1) {
            printf("  Celdas vacias del nivel: %d", espacios);

            //Imprime la cantidad necesaria de espacios
            for (int i = 12; i > 0 && pow(10, i) > espacios; i--) {
                printf(" ");
            }
        }
        //PUNTAJE NIVEL
        else if (x == MAX_VISIBLE_X / 2) {
            printf("         Puntuacion final: %d", puntuacion);

            //Imprime la cantidad necesaria de espacios
            for (int i = 12; i > 0 && pow(10, i) > puntuacion; i--) {
                printf(" ");
            }
        }
        //MONEDAS TOTALES
        else if (x == MAX_VISIBLE_X / 2 + 3) {
            printf("         Total de monedas: %d", j.total_monedas);

            //Imprime la cantidad necesaria de espacios
            for (int i = 12; i > 0 && pow(10, i) > j.total_monedas; i--) {
                printf(" ");
            }
        }
        //PUNTAJE TOTAL
        else if (x == MAX_VISIBLE_X / 2 + 4) {
            printf("         Puntuacion total: %d", j.puntaje);

            //Imprime la cantidad necesaria de espacios
            for (int i = 12; i > 0 && pow(10, i) > j.puntaje; i--) {
                printf(" ");
            }
        }
        //MENSAJE CONTINUAR
        else if (x == MAX_VISIBLE_X - 3) {
            printf("  [PRESIONA UNA TECLA PARA CONTINUAR]   ");
        }
        //Dibujado
        else {
            for (int y = 0; y < MAX_VISIBLE_Y; y++) {
                imprimir_objeto(mapa[x][y], 0.45);
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

void dibujar_final(Jugador j, int max_coins, int nivel) {
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

        //Títulos
        if (x == 3) {
            printf("          << FIN DEL JUEGO >>           ");
        }
        //TOTAL DE MONEDAS CONSEGUIDAS
        else if (x == MAX_VISIBLE_X / 2 - 3) {
            bool monedas_cero = false;
            printf("          Monedas totales: %d/ %d", j.total_monedas, max_coins);
            if (j.total_monedas == 0) {
                j.total_monedas = 1;
                monedas_cero = true;
            }

            //Imprime la cantidad necesaria de espacios
            for (int i = 9; i > 0 && pow(10, i) > j.total_monedas * max_coins; i--) {
                printf(" ");
            }

            if (monedas_cero) j.total_monedas = 0;
        }
        //PORCENTAJE DE MONEDAS RECOLECTADAS
        else if (x == MAX_VISIBLE_X / 2 - 2) {
            float relacion = 0;
            //Evita explosiones
            if (max_coins > 0) {
                relacion = (float)(j.total_monedas) / max_coins * 100;
            }
            printf("      Relacion de monedas: %.2f%%", relacion);

            //Imprime la cantidad necesaria de espacios
            for (int i = 8; i > 0 && pow(10, i) > relacion; i--) {
                printf(" ");
            }
        }
        //CANTIDAD DE PASOS
        else if (x == MAX_VISIBLE_X / 2 - 1) {
            printf("        Cantidad de pasos: %d", j.cant_pasos);

            //Imprime la cantidad necesaria de espacios
            for (int i = 12; i > 0 && pow(10, i) > j.cant_pasos; i--) {
                printf(" ");
            }
        }
        //TOTAL DE NIVELES
        else if (x == MAX_VISIBLE_X / 2) {
            printf("      Niveles completados: %d", nivel);

            //Imprime la cantidad necesaria de espacios
            for (int i = 12; i > 0 && pow(10, i) > nivel; i--) {
                printf(" ");
            }
        }
        //PUNTAJE TOTAL
        else if (x == MAX_VISIBLE_X / 2 + 1) {
            printf("         Puntuacion total: %d", j.puntaje);

            //Imprime la cantidad necesaria de espacios
            for (int i = 12; i > 0 && pow(10, i) > j.puntaje; i--) {
                printf(" ");
            }
        }
        //MENSAJE CONTINUAR
        else if (x == MAX_VISIBLE_X - 3) {
            printf("  [PRESIONA UNA TECLA PARA CONTINUAR]   ");
        }
        //Dibujado
        else {
            for (int y = 0; y < MAX_VISIBLE_Y; y++) {
                color_rgb(0, 0, 0);
                fondo_rgb(0, 0, 0);
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