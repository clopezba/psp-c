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
<<<<<<< HEAD
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
        signal(SIGUSR1, manejadorPadre); //el tratamiento de la señal SIGUSR1 se hará con el manejador padre
        printf("[Proceso: %d]: Manejador activado.\n", getpid());
        pause();
        pid_t pid_hijo = wait(NULL);
    }
=======
>>>>>>> f77cf9fa721cb6c36c8956a44db0b9cc4fb00907
    
    return 0;
}

<<<<<<< HEAD
//implementamos los manejadores
void manejadorHijo(int num_senyal){
    printf("Soy el manejador de la señal del hijo");
}

void manejadorPadre(int num_senyal){
    printf("Soy el manejador de la señal del padre");
}
=======
void manejadorHijo(int num_senyal){

}
void manejadorPadre(int num_senyal){
    
};
>>>>>>> f77cf9fa721cb6c36c8956a44db0b9cc4fb00907
