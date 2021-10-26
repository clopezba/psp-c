#include <unistd.h> //para fork
#include <sys/types.h> //para pid_t
#include<sys/wait.h> //para el wait
#include <signal.h> //para señales
#include <stdio.h> //para printf
#include <stdlib.h> // para exit

//declaramos los manejadores de la señal 
//los dos están disponibles tanto para padre como para hijos porque se han creado antes del fork
void manejadorHijo(int num_senyal);
void manejadorPadre(int num_senyal);

int main(int argc, char const *argv[])
{
    pid_t pid;
    pid = fork();
    if (pid == -1){ //gestionamos un posible error
        perror("Error en el fork");
        exit(1);
    }
    if (pid==0){ //soy el proceso hijo
        signal(SIGUSR1, manejadorHijo); //no hay que poner la función (con ()) sino si nombre, porque si no se ejecuta
        printf("[Proceso: %d]: Manejador activado.\n", getpid());
        pause();
    }else{ //soy el padre
        signal(SIGUSR1, manejadorPadre);
        printf("[Proceso: %d]: Manejador activado.\n", getpid());
        pause();
        pid_t pid_hijo = wait(NULL);
    }
    
    return 0;
}

//implementamos los manejadores
void manejadorHijo(int num_senyal){
    printf("Soy el manejador de la señal del hijo");
}

void manejadorPadre(int num_senyal){
    printf("Soy el manejador de la señal del padre");
}
