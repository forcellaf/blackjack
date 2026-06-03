@echo off
REM Build script for Raylib library only

setlocal enabledelayedexpansion

set RAYLIB_SRC=external\raylib\src
set CC=gcc
set CFLAGS=-std=c99 -O2 -w -DPLATFORM_DESKTOP -Iexternal\raylib\src -Iexternal\raylib\src\external\glfw\include

echo Building Raylib library...

%CC% -c %CFLAGS% %RAYLIB_SRC%\rcore.c -o obj_raylib\rcore.o
%CC% -c %CFLAGS% %RAYLIB_SRC%\rshapes.c -o obj_raylib\rshapes.o
%CC% -c %CFLAGS% %RAYLIB_SRC%\rtextures.c -o obj_raylib\rtextures.o
%CC% -c %CFLAGS% %RAYLIB_SRC%\rtext.c -o obj_raylib\rtext.o
%CC% -c %CFLAGS% %RAYLIB_SRC%\rmodels.c -o obj_raylib\rmodels.o
%CC% -c %CFLAGS% %RAYLIB_SRC%\raudio.c -o obj_raylib\raudio.o

ar rcs libraylib.a obj_raylib\*.o

echo Raylib library built successfully!

endlocal
