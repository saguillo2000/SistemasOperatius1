#!/bin/bash

# Comprobamos que se han pasado el número correcto de parámetros
if [ $# -ne 2 ]
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

#Crear un nuevo directorio donde guardar los ficheros
mkdir fitxersEx4 


# Para cada fichero con la extensión pasada por parámetro
for fichero in $( ls $1 )
do 
    
    if [ ${fichero##*.} = $2 -a ! -d $fichero ]
    then
        cp $1/$fichero fitxersEx4
    fi
done


# Si el directorio lo creamos y no se ha copiado nada, saltará un error y
# eliminaremos el directorio automáticamente
if [  ! "$( ls fitxersEx4 )" ]
then
    echo "El directorio no contiene ningún fichero con la extensión especificada."
    rmdir fitxersEx4
    exit 1
fi

# Si no hay errores comprimimos los fichero con la extensión intruducida 
#por teclado en un formato tar.gz
tar -czf fitxersEx4.tar.gz fitxersEx4

echo "Se han comprimido todos los ficheros .$2 en fitxersEx4.tar.gz"

# Para poder  eliminar el directorio primero debemos eliminar todo su contenido
for fichero in $( ls fitxersEx4 )
do
    rm fitxersEx4/$fichero

done

# Por último, eliminamos el directorio
rmdir fitxersEx4

exit 0
