#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

#include "./funciones.h"

#define MIN 1
#define MAX 5

bool final = false;

void gestor_senyal(int senyal)
{
    if (senyal == SIGUSR2)
    {
        final = true;
    }
}

int main()
{
    pid_t productor;

    signal(SIGUSR1, gestor_senyal); //registramos el tratamiento de SIGUSR1
    signal(SIGUSR2, gestor_senyal); //registramos el tratamiento de SIGUSR2

    int static fd1;
    char *myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);

    char str1[80], str2[80];
    fd1 = open(myfifo, O_WRONLY);
    
    unsigned int monedas_producidas = 0;
    printf("[Productor]: Iniciando producción bajo demanda... Esperando señal de producción\n");
    pause();
    while (!final)
    {
        printf("[Productor]: Produciendo monedas, tardaré 3 segundos en producir entre %d y %d monedas.\n", MIN, MAX);
        //genero monedas
        sleep(3);
        monedas_producidas = int_aleatorio(MIN, MAX);
        printf("[Productor]: Producidas %u monedas.\n", monedas_producidas);
        //escribo las monedas en el pipe
        write(fd1, &monedas_producidas, sizeof(unsigned int));
        //notifico al consumidor que hay monedas disponibles para leer
        kill(consumidor, SIGUSR1);
        printf("[Productor]: Consumidor notificado. Esperando señal para continuar...\n");
        pause();
    }
    //cerrar pipe
    close(fd1);
}
