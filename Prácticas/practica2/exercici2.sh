#!/bin/bash

#Comprobamos que se han pasado el número correcto de parámetros
if [ $# -ne 3 ]
then 
    echo "Número incorrecto de parámetros."
    exit 1
fi

# Comprobamos que el primer parametro es un directorio
if [ ! -d $1 ]
then
    echo "Error en el directorio especificado."
    exit 1
fi


# Buscamos todos los ficheros disponicles en el directorio
ficheros=$(find $1 -name "*.txt" -type f | sort )

# Para cada fichero
for elem in $ficheros
do
    # Calculamos el número de palabras que contienen las 2 cadenas
    num=$(grep -o "[^[:space:]]*$2[^[:space:]]*$3[^[:space:]]*" $elem | wc -l) 
    
    # Mientras haya alguna palabra con las condiciones,
    if [ $num -ne 0 ]
    then
        # Imprimimos el fichero actual y el numero de palabras encontradas 
        echo "${elem##*/}: $num"

    fi


done

exit 0
