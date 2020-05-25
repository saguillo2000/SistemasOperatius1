#!/bin/bash

# Comprobaremos si el número de parámetros es correcto

if [ $# -ne 1 ]
then 
    echo "Número incorrecto de parámetros."
    exit 1
fi

# Variables
encontrada=0
noencontrada=0

A=$1
lineas=$(cat $A)


# Comprobamos si el fichero existe y es o no un directorio
if [ ! -f A -a -d A ]
then
    echo "Fichero erróneo."
    exit 1
fi

# Si el fichero es correcto, para cada línea...
for i in $lineas
do
    if [ -f $i -o -d $i ]
    then
        encontrada=$(($encontrada+1))
    else
        noencontrada=$(($noencontrada+1))
    fi
done

# Imprimimos los resultados
echo "-> Ficheros encontrados: $encontrada"
echo "-> Ficheros no encontrados: $noencontrada"

exit 0
