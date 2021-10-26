//Crear un programa que usando 2 bucles cree 5 hijos definidos en una constante N_HIJOS.
//Cada uno de los hijos (el padre NO) debe imprimir su pid y el de su padre y esperar un segundo con sleep
//Después de crear los hijos el padre (sólo el padre) se quedará esperando en otro bucle
//al mismo número de hijos a que terminen.
//Al final el padre (sólo el padre) imprimirá un mensaje "soy PID, todos mis hijos han terminado"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

#define N_HIJOS 5 //constante 

int main(int argc, char const *argv[])
{
    int estado_proc;
    pid_t pid_padre = getpid();
    for (int i = 0; i < N_HIJOS; i++)
    {
        if(getpid() == pid_padre){
            fork();
        }
    }
    if(getpid()!= pid_padre){   
            printf("[Hijo]: Nº PID %d, PID padre %d\n", getpid(), getppid());  
            sleep(1);
        }
    for (int i = 0; i < N_HIJOS; i++)
    {
        wait(&estado_proc);
    }
    if(getpid() == pid_padre){
        printf("[Padre]: Soy %d, todos mis hijos han terminado", getpid());
    }
    

    return 0;
}
