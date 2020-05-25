#!/bin/bash

# Comprobamos que se han pasado el número correcto de parámetros
if [ $# -ne 1 ]
then 
    echo "Número incorrecto de parámetros."
    exit 1
fi

# Comprobamos que el parámetros pasado por teclado es un directorio
if [ ! -d $1 ]
then
    echo "NO es un directorio NO ES NO."
    exit 1
fi


# Por cada directorio y subdirectorio, contamos el número de ficheros
for directorio in $(find $1/ -type d)
do
  num_fitxers=$(find $directorio -type f | wc -l)
  echo "Directorio: " $directorio " nfiles: " $num_fitxers
done


exit 0
