#!/bin/bash

# Comprobamos que se han pasado el número correcto de parámetros
if [ $# -ne 1 ]
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

#Imprimirmos el directorio actual y los 3 ficheros mas grandes
echo "Directorio: "${1##*/}
fitx=$(find $1 -maxdepth 1 -type f -printf  "%s %P\n" | sort -rn | head -3 )
echo "$fitx"
echo " "


# En caso de haber subdirectorios, nos metemos y realizamos el mismo
# proceso en ellos

for directorio in $( find $1 -mindepth 1 -type d | sort )
do
    ./exercici1.sh $directorio 
    
done

exit 0
