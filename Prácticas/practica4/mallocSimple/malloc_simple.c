#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "struct.h"

/* El fet de fer servir variables 'static' fa que les
 * variables que hi ha a continuacio nomes es puguin
 * fer servir des d'aquest fitxer. Implementeu tot el
 * codi en aquest fitxer! */
static p_meta_data first_element = NULL;
static p_meta_data last_element  = NULL;


/* La seguent variable es la que permet bloquejar un 
 * codi en cas que hi hagi multiples fils. Amb aixo ens
 * assegurem que nomes un fil pugui entrar dintre d'un
 * codi que es bloqueja. Se us demana no tocar la part
 * bloquejada si voleu provar el codi amb executables
 * com el kate, kwrite, ... */
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

#define ALIGN8(x) (((((x)-1)>>3)<<3)+8)
#define MAGIC     0x87654321


/* Aquesta funcio permet buscar dintre de la llista un block lliure
 * que tingui la mida especificada */
p_meta_data search_available_space(size_t size_bytes) {
    
    p_meta_data current = first_element;

    while (current && !(current->available && current->size_bytes >= size_bytes)) 
        current = current->next;

    return current;
}

/* Aquesta funcio es la que fa la crida a sistema sbrk per demanar
 * al sistema operatiu un determinat nombre de bytes. Al principi del
 * tot s'afegiran les metadades, que l'usuari no fa servir. */
p_meta_data request_space(size_t size_bytes) 
{
    p_meta_data meta_data;

    meta_data = (void *) sbrk(0);

    if (sbrk(SIZE_META_DATA + size_bytes) == (void *) -1)
        return (NULL);

    meta_data->size_bytes = size_bytes;
    meta_data->available = 0;
    meta_data->magic = MAGIC;
    meta_data->next = NULL;
    meta_data->previous = NULL;

    return meta_data;
}

/* Allibera un bloc. L'argument es el punter del bloc a alliberar.
 * La funcio free accedeix a les metadades per indicar que el bloc
 * es lliure. */
void free(void *ptr)
{
    p_meta_data meta_data;

    if (!ptr) 
        return;
    
    // Bloquegem perque nomes hi pugui entrar un fil
    pthread_mutex_lock(&mutex);

    meta_data = (p_meta_data) (ptr - SIZE_META_DATA);

    if (meta_data->magic != MAGIC) {
      fprintf(stderr, "ERROR free: value of magic not valid\n");
      exit(1);
    } 

    meta_data->available = 1;
    fprintf(stderr, "Free at %x: %zu bytes\n", meta_data, meta_data->size_bytes);
     
    // Desbloquegem aqui perque altres fils puguin entrar a la funcio
    pthread_mutex_unlock(&mutex);
    
}

/* La funcio malloc per demanar un determinat nombre de bytes. La
 * funcio busca primer a la seva llista si hi ha algun bloc lliure
 * de la mida demanada. Si el troba, el retorna a l'usuari. Si no
 * en troba cap de la mida demanada, fa una crida a request_space
 * la qual internament fa una crida a sistema. */
void *malloc(size_t size_bytes) 
{
    
    void *p, *ptr;
    p_meta_data meta_data;

    if (size_bytes <= 0) {
        return NULL;
    }

    /* Reservem una mida de memoria multiple de 8. Es
     * cosa de l'electronica de l'ordinador que requereix
     * que les dades estiguin alineades amb multiples de 8.*/
    size_bytes = ALIGN8(size_bytes);
    fprintf(stderr, "Malloc %zu bytes\n", size_bytes);

    // Bloquegem perque nomes hi pugui entrar un fil
    pthread_mutex_lock(&mutex);

    meta_data = search_available_space(size_bytes);

    /* Si trobem un bloque lliure, posem l'available a 1,
     * sino cal pedir mes espai. */
    if (meta_data) { 
        meta_data->available = 0;
        
    } else {     
        meta_data = request_space(size_bytes);
        if (!meta_data)
            return (NULL);
        
        // Si estem davant l'ultim element
        if (last_element) 
            last_element->next = meta_data;
        meta_data->previous = last_element;
        last_element = meta_data;

        // Si estem davant el primer element
        if (first_element == NULL) 
            first_element = meta_data;
  }

  p = (void *) meta_data;

  // Desbloquegem aqui perque altres fils puguin entrar a la funcio
  pthread_mutex_unlock(&mutex);

  // Retornem a l'usuari l'espai que podra fer servir
  ptr = p + SIZE_META_DATA;
  return ptr;
  
}


/* La funcio calloc ppermet reservar varis elements de memòria,
 * en concret nelem elements de mida elsize bytes, i els deixa 
 * inicialitzats a zero. Utilitza la funcio memset per inicialitzar
 * el bloc de dades a zero. 
 * La funció retorna un punter a la memòria reservada */
void *calloc(size_t nelem, size_t elsize){

    printf ("Fem un calloc de %zu bytes %zu vegades \n", elsize, nelem);

    void *ptr = malloc (nelem * elsize);

    if (ptr) {
        memset (ptr, 0, nelem * elsize);
    }

    return ptr;
}

/*La funció realloc reajusta la mida d’un bloc de memòria obtingut 
 * amb malloc a una nova mida. */
void *realloc(void *ptr, size_t size_bytes){
    // Si li passem un punter NULL, realloc actua com un malloc normal 
    if(!ptr) {
        printf ("Fem un realloc com a un malloc. \n");
        return malloc(size_bytes);
    }

    // Per poder saber si n'hi ha espai suficient espai, restem la MIDA per defecte
    p_meta_data meta_dades = (p_meta_data) (ptr- SIZE_META_DATA);

    // Si n'hi ha suficiente espai i el punter es no null, el retornem 
    if( meta_dades->size_bytes >= size_bytes){
        printf ("Fem un realloc. \n");
        return ptr;
    }

    void *new_ptr = malloc(size_bytes); 

    // Si no es pot fer el malloc, 
    if(!new_ptr){
       return NULL;
    }
 
    // Copiem el contingut de un punter al altre i
    memcpy(new_ptr, ptr, meta_dades->size_bytes);
    
    // alliberem la memoria dinamica, ja uqe no ens fara falta
    free (ptr);
    return new_ptr;
    

}
