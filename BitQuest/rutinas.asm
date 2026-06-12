bits 64

default rel

global verificar_jugador, cantidad_caracter, calcular_puntuaje, verificar_objeto, celdas_libres

section .text

;Funcion cantidad_caracter
;Contar monedas/caracteres
cantidad_caracter:
    xor eax, eax            ; Contador total = 0
    xor r10d, r10d          ; i = 0 (filas)
.loop_ren:
    cmp r10d, edx
    jge .fin_ren
    mov r11, [rcx + r10 * 8] ; r11 = mapa[i]
    test r11, r11
    jz .skip_ren

    push rdx                ; Preservar filas totales
    xor rdx, rdx            ; j = 0 (columnas)
.loop_col:
    cmp edx, r8d
    jge .fin_col
    mov r13b, byte [r11 + rdx]
    cmp r13b, r9b
    jne .no_match
    inc eax                 ; Encontrado, incrementar contador
.no_match:
    inc edx                 ; j++
    jmp .loop_col
.fin_col:
    pop rdx                 ; Restaurar filas totales
.skip_ren:
    inc r10d                ; i++
    jmp .loop_ren
.fin_ren:
    ret

; Funcion calcular_putaje
; calcula el score: (moendas * 100) + (niveles * 500) - (pasos * 2)
calcular_puntuaje:
    imul ecx, ecx, 100      ; monedas * 100
    imul r8d, r8d, 500      ; niveles * 500
    imul edx, edx, 2        ; pasos * 2

    add ecx, r8d            ; (monedas*100) + (niveles*500)
    sub ecx, edx            ; Puntuación final en ECX

    mov eax, ecx            ; Retornar en EAX
    cmp eax, 0              ; Evitar que el puntaje sea menor a 0
    jge .fin_score
    xor eax, eax
.fin_score:
    ret

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

; Funcion celdas_libres
; Cuenta cuantos caminos '.' quedan limpios
celdas_libres:
    xor eax, eax            ; total_libres = 0
    xor r10d, r10d          ; i = 0 (filas)
.l_ren:
    cmp r10d, edx
    jge .l_fin
    mov r11, [rcx + r10 * 8]
    test r11, r11
    jz .l_skip

    push rdx
    xor rdx, rdx            ; j = 0 (columnas)
.l_col:
    cmp edx, r8d
    jge .l_col_fin
    mov r9b, [r11 + rdx]
    cmp r9b, '.'            ; ¿Es camino libre?
    jne .no_libre
    inc eax
.no_libre:
    inc edx
    jmp .l_col
.l_col_fin:
    pop rdx
.l_skip:
    inc r10d
    jmp .l_ren
.l_fin:
    ret