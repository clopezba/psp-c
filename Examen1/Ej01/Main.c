#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    int caramelos = 6;
    printf("Valor inicial de la varaible: %d\n", caramelos);
    pid_t pid = fork();
    switch (pid)
    {
    case -1:
        perror("Se ha producido un error al crear al hijo\n");
        exit(0);
        break;
    case 0:
        caramelos -= 5;
        printf("Variable en Proceso Hijo: %d\n", caramelos);
        break;
    default:
        caramelos += 5;
        printf("Variable en Proceso Padre: %d\n", caramelos);    
        break;
    }

    return 0;
}
