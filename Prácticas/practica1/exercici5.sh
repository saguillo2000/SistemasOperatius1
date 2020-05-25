#!/bin/bash

# Comprobamos que se han pasado el número correcto de parámetros (mayor o igual a 2)

if [ $# -lt 2 ]
then 
    echo "Número incorrecto de parámetros."
    exit 1
fi

# Comprobamos que el primer parametro es un directorio
if [ ! -d $1 ]
then
    echo "El parametro 1 no es un directorio."
    exit 1
fi
contador=0

# Si no hay errores comenzamos a buscar el numero de ficheros con las extensiones dadas
echo "Directorio: $1"

for elem in $*
do
    if [ ! -d $elem ]
    then
        for fichero in $( ls $1 )
        do 

            if [ ${fichero##*.} = $elem -a ! -d $fichero ]
            then
                contador=$(($contador+1))
                
            fi
            if [ -d $1/$fichero ]
            then
                ./exercici5.sh $1/$fichero $*
            fi
        done
        echo " $elem: $contador"
        contador=0
    fi
    
done
    
exit 0
