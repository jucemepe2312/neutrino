#!/bin/sh
# install.sh - compila e instala Neutrino en /usr/local/bin
set -e

SRC="src/neutrino.c"
BIN="bin/neutrino"
DEST="/usr/local/bin/neutrino"

# Dependencias
command -v gcc >/dev/null 2>&1 || { echo "falta gcc"; exit 1; }

# Compilar
echo "compilando $SRC..."
mkdir -p bin
gcc -Wall -Wextra -O2 "$SRC" -o "$BIN"

# Instalar
echo "instalando en $DEST..."
install -Dm755 "$BIN" "$DEST"

echo "listo. prueba con: sudo neutrino"