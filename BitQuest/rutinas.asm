bits 64

default rel

global verificar_jugador, cantidad_caracter, calcular_puntuaje, verificar_objeto, celdas_libres

section .text

;Funcion cantidad_caracter
;Contar monedas/caracteres
cantidad_caracter:
    xor eax, eax            ; total_coincidencias = 0
    test rcx, rcx           ; Verificar si el puntero del mapa es NULL
    jz .fin_cantidad
    
    xor r10d, r10d          ; r10d = i indice de filas

.loop_ren:
    cmp r10d, edx
    jge .fin_cantidad

    xor r11d, r11d
.loop_col:
    cmp r11d, r8d
    jge .sig_ren

    mov r12d, r10d
    imul r12d, r8d
    add r12d, r11d

    mov r13b, byte [rcx + r12]
    
    cmp r13b, r9b
    jne .no_match
    inc eax                 ; total_coincidencias++

.no_match:
    inc r11d                ; j++
    jmp .loop_col

.sig_ren:
    inc r10d                ; i++
    jmp .loop_ren

.fin_cantidad:
    ret

; Funcion calcular_putaje
; calcula el score: (moendas * 100) + (niveles * 500) - (pasos * 2)
calcular_puntuaje:
    imul ecx, ecx, 100      ; monedas * 100
    imul r8d, r8d, 500      ; niveles * 500
    imul edx, edx, 2        ; pasos * 2

    add ecx, r8d            ; suma parcial
    sub ecx, edx            ; menos penalización por pasos

    mov eax, ecx
    cmp eax, 0              ; El puntaje nunca debe ser negativo
    jge .fin_puntuaje
    xor eax, eax

.fin_puntuaje:
    ret

; Funcion verificar_jugador
; recibe: char**, int, int, int
; devuelve 1 si es valido, 0 si no esta bloqueado
; Parámetros:
;   RCX = char* mapa
;   RDX = int col         Columnas totales de la matriz
;   R8  = int sig_x       Fila a la que se quiere mover
;   R9  = int sig_y       Columna a la que se quiere mover
verificar_jugador:
    ; Validar límites inferiores
    cmp r8d, 0
    jl .bloqueado
    cmp r9d, 0
    jl .bloqueado
    
    ; EDX para checar los limites
    cmp r9d, edx
    jge .bloqueado

    mov r10d, r8d
    imul r10d, edx
    add r10d, r9d

    ; Obtener el carácter
    mov al, byte [rcx + r10]

    cmp al, '#'             ; Pared
    je .bloqueado

    mov eax, 1              ; Movimiento aprobado
    ret

.bloqueado:
    mov eax, 0              ; Movimiento denegado
    ret

; Funcion verificar_objeto
; Que hace? Verifica en el mapa que exista un determinado objeto
; recibe: char**, int, int, int, int
; devuelve 1 si lo encontro, 0 si no lo encontro
; Parámetros:
;   RCX = char* mapa
;   RDX = int col         Ancho total de columnas
;   R8  = int x           fila
;   R9  = int y           columna
;   [RSP+40] = int obj    El carácter buscado viene en el espacio de la pila
verificar_objeto:
    mov r10d, r8d
    imul r10d, edx
    add r10d, r9d

    mov al, byte [rcx + r10]
    mov r11d, [rsp + 40]

    cmp al, r11b            ; comparar para ver si es el objeto
    jne .no_es

    mov eax, 1              ; Verdadero
    ret

.no_es:
    mov eax, 0              ; Falso
    ret

; Funcion celdas_libres
; Cuenta cuantos caminos '.' quedan limpios
; Parámetros:
;   RCX = char* mapa
;   RDX = int ren
;   R8  = int col
celdas_libres:
    xor eax, eax
    xor r10d, r10d

.l_ren:
    cmp r10d, edx
    jge .l_fin

    xor r11d, r11d          ; j = 0 (columnas)
.l_col:
    cmp r11d, r8d
    jge .l_sig_ren

    mov r12d, r10d
    imul r12d, r8d
    add r12d, r11d

    mov r13b, byte [rcx + r12]
    cmp r13b, '.'            ; camino
    jne .no_libre
    inc eax                 ; total_libres++

.no_libre:
    inc r11d                ; j++
    jmp .l_col

.l_sig_ren:
    inc r10d                ; i++
    jmp .l_ren

.l_fin:
    ret
