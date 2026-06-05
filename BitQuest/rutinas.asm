bits 64

default rel

global verificar_jugador, cantidad_caracter, calcular_puntuaje, verificar_objeto, celdas_libres

section .text

; Funcion verificar_jugador
; recibe: char**, int, int, int
; devuelve 1 si es valido, 0 si no esta bloqueado
; RCX = mapa ; RDX = col (# max de col del mapa); R8 = sig_x (fila propuesta) ; R9 = sig_y (columna propuesta) 
verificar_jugador:
	;validar que r8 no sea negativo
	cmp r8d, 0
	jl .bloqueado
	;validar que r9 no sea negativo
	cmp r9d, 0
	jl .bloqueado

	;validar limite maximo de columnas
	cmp r9d, edx
	jge .bloqueado

	;obtener la fila propuesta mapa[sig_x]
	mov r11, [rcx + r8 * 8]
	test r11, r11
	jz .bloqueado

	;obtener el caracter en la posicion mapa[sig_x][sig_y]
	mov al, [r11 + r9]

	;si es una pared #, el movimiento no es valido
	cmp al, '#'
	je .bloqueado

	;si todo ok retornar 1
	mov eax, 1
	ret

	.bloqueado:
		mov eax, 0
ret

; Funcion verificar_objeto
; Que hace? Verifica en el mapa que exista un determinado objeto
; recibe: char**, int, int, int, int
; devuelve 1 si lo encontro, 0 si no lo encontro
; RCX = mapa ; RDX = col ; R8 = x ; R9 = y ; [RSP+40] = obj
verificar_objeto:
	mov r11, [rcx + r8 * 8]
	test r11, r11
	jz .falso

	;caracter actual en la celda
	mov al, [r11 + r9]

	; (5to parametro) 32 bytes + (Dir retorno) 8 bytes = 40 bytes
	mov r10d, [rsp + 40]

	cmp al, r10b	;es el objeto buscado?
	jne .falso

	mov eax, 1	;si es
	ret

	.falso:
		mov eax,0	;no es
ret
