#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXVALUE 1000

void sigusr1(int signo)
{
  printf("El pare ha rebut el SIGUSR1\n");
}

void sigusr2(int signo)
{
  printf("El fill ha rebut el SIGUSR2\n");
}


int main(void)
{
    /* VARIABLES */
    int i, num_values, value, sum, fd[2];
    int ret, parent_pid, child_pid;
    
    /* Creem la canonada amb la comanda pipe i el fill amb fork */
    pipe(fd);
    ret = fork();
    

    if (ret == 0) { // child
      
        /* Inserir codi aqui per gestionar senyals */
        signal(SIGUSR2, sigusr2);
        parent_pid = getppid();
       
        /* Esperar a rebre senyal del pare */
        pause();
	
        /* Llegir el nombre de valors que ens envia el pare */
        read(fd[0], &num_values, sizeof(int));
        
        i = 0;
        sum = 0;
        
        while (i < num_values) {
            /* Llegir valors de la canonada i fer la suma */
            read(fd[0], &value, sizeof(int));
            sum += value; 
            i++;
        }
        
        /* Imprimim el resultat de la suma */
        printf("El fill escriu el resultat: %d\n", sum);
        
        /* Escriure el valor de la suma a la canonada */
        write(fd[1], &sum, sizeof(int));
        
        /* Avisar al pare que s'han escrit els valors */ 
        printf("Envio SIGUSR1 al pare %d\n", parent_pid);
        kill(parent_pid, SIGUSR1);

        exit(0);
        

    } else { // parent

        /* Inserir codi aqui per gestionar senyals */
        signal(SIGUSR1, sigusr1);
        child_pid = ret;

        /* Random seed */
        srand(time(NULL));

        i = 0;
       
        /* Escriure aquest valor a la canonada */
        num_values = 1000;

        write(fd[1], &num_values, sizeof(int));
        
        while (i < num_values) {  
            /* Generar valor aleatori i inserir a la canonada */
            value = rand() % MAXVALUE + 1;
            write(fd[1], &value, sizeof(int));
            i++;
        }

        printf("El pare espera la suma...\n");

        /* Inserir codi aqui per esperar senyal del pare */
        printf("Envio SIGUSR2 al fill %d\n", child_pid);
        kill(child_pid, SIGUSR2);
        
        pause();

        /* Llegir el resultat */
        read(fd[0], &sum, sizeof(int));

        printf("El fill em diu que la suma es: %d\n", sum);

        wait(NULL);
        
    }

    return 0;
    
}
