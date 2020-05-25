#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>


#define SIZE 100

// VARIABLES
int retS, retM, retH,segons = 0,minuts = 0,hores = 0;
int fds[2],fdm[2],fdh[2];
char buffer [SIZE];

// FUNCIONS
void sigusr1(int signo) {}

void sigusr2(int signo) {}

void sigalarm(int signo) {}

void sigterm(int signo){
    
    kill(retS, SIGTERM);
    kill(retM, SIGTERM);
    kill(retH, SIGTERM);
    kill(getpid(),SIGKILL);
    
}

void cerrarPipesS() {
    // Tanquem les canonades del fill segons
    close(fds[0]);
    close(fds[1]);
    exit(0);
    
}

void cerrarPipesM() {
    // Tanquem les canonades del fill minuts
    close(fdm[0]);
    close(fdm[1]);
    exit(0);
}

void cerrarPipesH() {
    // Tanquem les canonades del fill hores
    close(fdh[0]);
    close(fdh[1]);
    exit(0);
}




int main(void){

    // CANONADES
    pipe(fds);      //canonda per segons
    pipe(fdm);      //canonada per minuts
    pipe(fdh);      //canonada per hores
    

    sprintf(buffer,"L'identificador del procés és %d\n", getpid());
    write(1, buffer, strlen(buffer));

    // Creem al fill Hores
    retH = fork();
    
    if(retH == 0) { 
        signal(SIGUSR2, sigusr2);
        signal(SIGTERM, cerrarPipesH);
        while(1) {
            pause();
            hores ++;
            write(fdh[1], &hores, sizeof(int));
        }
        
    }
   
   
    // Creem al fill Minuts
    retM = fork();

    if(retM == 0) {     
        signal(SIGUSR2, sigusr2);
        signal(SIGTERM, cerrarPipesM);
        while(1) {
            pause();
            minuts++;
        
            if(minuts == 60) {
                minuts = 0;
                kill(retH, SIGUSR2);
            }
        
            write(fdm[1], &minuts, sizeof(int));
        }
        
    }

    // Creem al fill Segons 
    retS = fork();

    if(retS == 0) { 
        signal(SIGUSR1, sigusr1);
        pause();
        signal(SIGALRM, sigalarm);
        signal(SIGTERM, cerrarPipesS);
        
        while(1) {
            alarm(1);
            pause();
            segons++; 
            
            if(segons == 60) {
                segons = 0;
                kill(retM, SIGUSR2); //Enviem la señal al fill Minuts
        	}
        	
        	write(fds[1], &segons, sizeof(int));
            
        }
        
        
    }

    
    // Tenim el proces pare
    
    else { 
        
        // Senyals a rebre
        signal(SIGUSR1, sigusr1);
        signal(SIGTERM,sigterm);
        pause();
        
        sprintf(buffer,"Comença temporitzador!!\n");
        write(1,buffer,strlen(buffer));
        
        kill(retS,SIGUSR1); //Enviem la senyal SIGUSR1 al fill Segons
        
        while(1) {
            
            // Imprimim el temporitzador cada cop que es modifiqui
        	sprintf(buffer,"%02d:%02d:%02d\n", hores, minuts, segons);
        	write(1,buffer,strlen(buffer));
            
            read(fds[0], &segons, sizeof(int));
            
            if(segons == 0) {
                read(fdm[0], &minuts,sizeof(int));
                
            }
            
            if(segons == 0 && minuts == 0) {
                read(fdh[0], &hores, sizeof(int));
                
            }
            
        }
        
    }
    
    return 0;

}
