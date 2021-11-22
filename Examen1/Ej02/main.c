#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd[2];
    pid_t pid;
    char saludoHijo[] = "Buenos días padre.\0";
    char buffer[80];

    pipe(fd);
    pid = fork();

    switch (pid)
    {
    case -1:
        perror("Ha habido un error creando el hijo\n");
        exit(0);
        break;
    case 0:
        close(fd[0]);
        write(fd[1], saludoHijo, strlen(saludoHijo));
        printf("\tEl hijo envía algo al pipe.\n");
        wait(NULL);
        break;
    default:
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        printf("El padre recibe algo del pipe: %s\n", buffer);
        break;
    }

    return 0;
}
