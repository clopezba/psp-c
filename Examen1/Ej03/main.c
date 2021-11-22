#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

void manejadorPadre(int senyal)
{
    if (senyal == SIGUSR1)
    {
        printf("Padre recibe señal...%d\n", senyal);
    }
}

int main(int argc, char const *argv[])
{
    signal(SIGUSR1, manejadorPadre);
    
    int pid_padre = getpid();
    printf("[Padre]: Mi PID es: %d\n", pid_padre);
    
    int pidHijo = fork();

    switch (pidHijo)
    {
    case -1:
        perror("Se ha producido un error al crear el hijo\n");
        exit(-1);
        break;
    case 0:

        for (size_t i = 0; i < 3; i++)
        {
            printf("[Hijo]: Envío señal %d al padre %d.\n", i+1, getppid());  
            kill(pid_padre, SIGUSR1);
        }
        printf("[Hijo]: Envío señal de fin al padre\n");
        sleep(4);
        kill(pid_padre, SIGKILL);

    default:
        sleep(2);
        pause();
        sleep(2);
        break;
    }

    return 0;
}
