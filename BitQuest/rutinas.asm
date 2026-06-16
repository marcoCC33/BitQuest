bits 64

default rel

global verificar_jugador, cantidad_caracter, calcular_puntuaje, verificar_objeto, celdas_libres, mover_jugador, encontrar_jugador

section .text

; ==============================================================================
; Funcion: cantidad_caracter
; Que hace? Contar monedas u otros elementos
; C prototipo: int cantidad_caracter(char** mapa, int ren, int col, int caracter);
; Parámetros:
;   RCX = char** mapa
;   RDX = int ren         Limitador de filas
;   R8  = int col         Límitador de columnas
;   R9  = int caracter    Carácter buscado promovido a entero
; ==============================================================================
cantidad_caracter:
    xor eax, eax            ; total_coincidencias = 0
    test rcx, rcx           ; Validar que la dirección base no sea NULL
    jz .fin_cantidad
    
    xor r10d, r10d          ; r10d = i (índice de filas) = 0

.loop_ren:
    cmp r10d, edx
    jge .fin_cantidad

    ; Cargar la dirección de la fila actual: mapa[i]
    mov r11, [rcx + r10 * 8]
    test r11, r11           ; Si la fila es NULL, saltar
    jz .sig_ren

    xor r12d, r12d          ; r12d = j (índice de columnas) = 0
.loop_col:
    cmp r12d, r8d
    jge .sig_ren

    ; Leer el byte exacto desde la fila cargada: mapa[i][j]
    mov r13b, byte [r11 + r12]
    
    cmp r13b, r9b           ; Caracter buscado
    jne .no_match
    inc eax                 ; total_coincidencias++

.no_match:
    inc r12d                ; j++
    jmp .loop_col

.sig_ren:
    inc r10d                ; i++
    jmp .loop_ren

.fin_cantidad:
    ret


; ==============================================================================
; Funcion verificar_jugador
; Que hace? Validar si el movimiento choca con pared
; C prototipo: int verificar_jugador(char** mapa, int col, int sig_x, int sig_y);
; Parámetros:
;   RCX = char** mapa
;   RDX  = int sig_x      (Fila propuesta)
;   R8  = int sig_y       (Columna propuesta)
;   R9 = int* llave       (Cantidad de llaves)
; ==============================================================================
verificar_jugador:
    XOR eax, eax

    ; Validar límites inferiores
    cmp rdx, 0
    jl .bloqueado
    cmp r8d, 0
    jl .bloqueado

    ; Obtener la dirección base de la fila propuesta: mapa[sig_x]
    mov r11, [rcx + rdx * 8]
    test r11, r11           ; Verificar que la fila exista en memoria
    jz .bloqueado

    ; Obtener el carácter de la celda destino: mapa[sig_x][sig_y]
    mov al, byte [r11 + r8]

    cmp al, '#'             ; Pared
    je .bloqueado
    
    cmp al, 'D'             ; Puerta
    je .puerta

    mov eax, 1              ; Movimiento permitido
    ret

    ;Se encuentra con un puerta, si hay llaves se deja pasar, si no, nel
.puerta:
    ; Recupera la cantidad de llaves
    cmp dword [r9], 0
    jle .bloqueado
    mov eax, 1              ; Se mueve
    dec dword [r9]               ; Reduce la cantidad de llaves
    ret

.bloqueado:
    mov eax, 0              ; Movimiento denegado
    ret


; ==============================================================================
; Funcion: calcular_puntuaje (Obligatoria: Multiplicaciones y score final)
; C prototipo: int calcular_puntuaje(int monedas, int pasos, int niveles);
; Formula: (monedas * 100) + (niveles * 500) - (pasos * 2)
; ==============================================================================
calcular_puntuaje:
    imul ecx, ecx, 100      ; monedas * 100
    imul r8d, r8d, 500      ; niveles * 500
    imul edx, edx, 2        ; pasos * 2

    add ecx, r8d            ; suma parcial de bonos
    sub ecx, edx            ; restar penalización por pasos

    mov eax, ecx
    cmp eax, 0              ; Proteger para que el score nunca baje de 0
    jge .fin_puntuaje
    xor eax, eax

.fin_puntuaje:
    ret


; ==============================================================================
; Funcion: verificar_objeto
; Que hace? Detectar qué objeto hay en una celda
; C prototipo: int verificar_objeto(char** mapa, int col, int x, int y, int obj);
; Parámetros:
;   RCX = char** mapa
;   RDX = int x           (Coordenada Fila)
;   R8  = int y           (Coordenada Columna)
;   R9  = int obj   
; ==============================================================================
verificar_objeto:
    ; Obtener la dirección de la fila mapa[x]
    mov r11, [rcx + rdx * 8]

    ; Cargar el carácter real de la celda mapa[x][y]
    mov al, byte [r11 + r8]

    cmp al, r9b            ; Caracter de la celda y el objetivo
    jne .no_es

    mov eax, 1              ; Sí es el objeto
    ret

.no_es:
    mov eax, 0              ; No es el objeto
    ret


; ==============================================================================
; Funcion celdas_libres
; Que hace? Contar caminos libres '.'
; C prototipo: int celdas_libres(char** mapa, int ren, int col); [cite: 233]
; Parámetros:
;   RCX = char** mapa
;   RDX = int ren
;   R8  = int col
; ==============================================================================
celdas_libres:
    xor eax, eax            ; total_libres = 0
    test rcx, rcx
    jz .l_fin

    xor r10d, r10d          ; r10d = i (índice de filas) = 0

.l_ren:
    cmp r10d, edx
    jge .l_fin

    ; Extraer la dirección de la fila actual: r11 = mapa[i]
    mov r11, [rcx + r10 * 8]
    test r11, r11           ; Si la fila es inválida o NULL, saltar
    jz .l_sig_ren

    xor r12d, r12d          ; r12d = j (índice de columnas) = 0
.l_col:
    cmp r12d, r8d
    jge .l_sig_ren

    ; Leer el caracter
    mov r13b, byte [r11 + r12]
    
    cmp r13b, '.'           ; Camino libre
    jne .no_libre
    inc eax                 ; total_libres++

.no_libre:
    inc r12d                ; j++
    jmp .l_col

.l_sig_ren:
    inc r10d                ; i++
    jmp .l_ren

.l_fin:
    ret

; ==============================================================================
; Funcion: mover_jugador
; Que hace? mueve al jugador
; C prototipo: int cantidad_caracter(char** mapa, int x1, int y1, int x2, int y2);
; Parámetros:
;          RCX = char** mapa
;          RDX = int renglón original
;          R8  = int columna original
;          R9  = int nuevo renglón
;   [RSP + 40] = int nueva columna
; ==============================================================================
mover_jugador:
    xor     r10, r10
    mov     r10d, [RSP + 40]         ;Carga la nueva columna en r10

    ;Obtiene el jugador
    mov     r11, [rcx + rdx * 8]    ;fila 
    mov     r12, [r11 + r8]
    mov     r13b, '.'
    mov     [r11 + r8], r13b

    ;Mueve el jugador
    mov     r11, [rcx + r9 * 8]     ;new fila
    mov     [r11 + r10], r12b

    ret

; ==============================================================================
; Funcion: encontrar_jugador
; Que hace? encuentra el jugador en el mapa y lo inicializa para el nuevo nivel
; C prototipo: void encontrar_jugador(char** mapa, int ren, int col, Jugador* j);
; Parámetros:
;          RCX = char** mapa
;          RDX = int renglones máximos
;          R8  = int columnas máximas
;          R9  = Jugador* puntero a jugador
; ==============================================================================
; Registros:
;       r10: puntero actual a la fila
;       r11: contador en X/ filas
;       r12: contador en Y/ columnas
; ==============================================================================
encontrar_jugador:
    xor     r11, r11        ; r11 es X
    xor     r12, r12        ; r12 es Y

    .loop_renglones:
        cmp     r11d, edx        ;Que no se salga de los renglones
        jge     .fin_busqueda
        mov     r10, [rcx + r11 * 8]    ;new renglón
        xor     r12, r12     ;Iniciar Y

        .loop_columnas:
            cmp     r12d, r8d            ;que no se salga de las columnas
            jge     .fin_columnas
            cmp     byte [r10 + r12], 'P'
            je      .fin_busqueda

            inc     r12
            jmp     .loop_columnas

        .fin_columnas:
        inc     r11
        jmp     .loop_renglones

    .fin_busqueda:
    ;Guarda la nueva posición del jugador
    ;[r9] = x   [r9 + 4] = y
    mov     [r9],     r11
    mov     [r9 + 4], r12

    ;limpia el resto de variables
    mov     dword [r9 + 8], 0     ;monedas
    mov     dword [r9 + 16], 0    ;llaves

    ret