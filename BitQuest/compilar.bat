@echo off
setlocal enabledelayedexpansion

REM comentario
:: comentario

:: Obtener el nombre de la carpeta actual
for %%I in (.) do set "CARPETA=%%~nxI"

echo .
echo Compilando el proyecto
echo .

::compilar todos los asm a obj
::%%F = en el folder actual
for %%F in (*.asm) do (
	echo [NASM] compilando %%F ...
	nasm -f win64 "%%F" -o "%%~nF.obj"
	if errorlevel 1 (
		echo Error al compilar %%F
		exit /b 1
	)
)

set "OBJS="
for %%F in (*.obj) do (
	set "OBJS=!OBJS! %%F"
)

set "CSRC="
for %%F in (*.c) do (
	set "CRSC=!CRSC! %%F"
)

::Enlazar con GCC

gcc %CSRC% %OBJS% -o "%CARPETA%.exe"
if errorlevel 1 (
	echo Error en el enlace
	exit /b 1
)

echo .
echo Compilacion Terminada
echo .

endlocal
pause
