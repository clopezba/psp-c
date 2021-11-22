#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    pid_t pidPadre, pidHijo1, pidHijo2, pidHijo3;
    pidPadre = getpid();

    pidHijo1 = fork();
    switch (pidHijo1)
    {
    case -1:
        printf("Error al crear el hijo1\n");
        exit(0);
        break;
    case 0:
        printf("Soy el hijo = 1, Mi padre es = %d, Mi PID= %d\n", getppid(), getpid());
        break;
    default:
        sleep(1);
        pidHijo2 = fork();
        switch (pidHijo2)
        {
        case -1:
            printf("Error al crear el hijo1\n");
            exit(0);
            break;
        case 0:
            printf("Soy el hijo = 2, Mi padre es = %d, Mi PID= %d\n", getppid(), getpid());
            break;
        default:
            sleep(1);
            pidHijo3 = fork();
            switch (pidHijo3)
            {
            case -1:
                printf("Error al crear el hijo1\n");
                exit(0);
                break;
            case 0:
                printf("Soy el hijo = 3, Mi padre es = %d, Mi PID= %d\n", getppid(), getpid());
                break;
            default:
                sleep(1);
                printf("Proceso PADRE = %d\n", pidPadre);
                break;
            }
            break;
        }
        break;
    }
    return 0;
}
