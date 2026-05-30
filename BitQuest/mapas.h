#pragma once
#include <stdio.h>

char** cargar_mapa(int* ren, int* col, char* nombre_archivo) {
	FILE* archivo;
	char** mapa;
	char caracter;
	int ren_arch, col_arch, max_col;
	bool linea_fin = false;

	archivo = fopen(nombre_archivo, "r");
	if (archivo == NULL) {
		printf("No existe o no se pudo carcar %s", nombre_archivo);
		return NULL;
	}

	ren_arch = 1;
	col_arch = 0;
	max_col = -1;

	while ((caracter = fgetc(archivo)) != -1) {
		col_arch++;
		linea_fin = false;
		if (caracter == '\n') {
			ren_arch++;

			//Hace que las columnas sean el mayor número posible
			if (col_arch > max_col) {
				max_col = col_arch;
			}
			col_arch = 0;
			linea_fin = true;
		}
	}
	fclose(archivo);
	archivo = fopen(nombre_archivo, "r");

	if (linea_fin) ren_arch--;

	//Nuevos renglones y columnas
	*ren = ren_arch;
	*col = max_col;

	//Copiar el mapa del archivo a memoria
	mapa = malloc(sizeof(char*) * ren_arch);
	for (int x = 0; x < ren_arch; x++) {
		mapa[x] = malloc(sizeof(char) * max_col);
		for (int y = 0; y < max_col; y++) {
			mapa[x][y] = '#';
		}
		fgets(mapa[x], max_col, archivo);
		fgetc(archivo);		//Se come el salto de línea
	}

	fclose(archivo);
	return mapa;
}