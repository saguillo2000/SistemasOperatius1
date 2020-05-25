#!/bin/bash

#Comprobamos que se han pasado el número correcto de parámetros
if [ $# -ne 1 ]
then 
    echo "Número incorrecto de parámetros."
    exit 1
fi

# Variables
cadena=$1
palindrom=$cadena

# Recorremos la cadena del final al principio y creamos el palindrom

for (( i = ${#cadena} - 2; i >= 0; i-- ))
do   
    palindrom+=${cadena:$i:1}
    
done
    
# Imprimimos los resultados
echo "Palindrom: $palindrom"
exit 0

