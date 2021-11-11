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

bool final = false;

void gestor_senyal(int senyal)
{
    if (senyal == SIGUSR2)
    { //La señal 2 la usaremos para finalizar.
        final = true;
    }
}

int main()
{
    pid_t consumidor;

    signal(SIGUSR1, gestor_senyal); //registramos el tratamiento de SIGUSR1
    signal(SIGUSR2, gestor_senyal); //registramos el tratamiento de SIGUSR2

    int fd;
    char *myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);
    consumidor = fork();
    if (consumidor == -1)
    {
        perror("Error creando al consumidor.");
        exit(2);
    }
    if (consumidor == 0)
    { //Proceso consumidor. Sólo leerá del pipe así que...
        unsigned int monedas_necesarias = int_aleatorio(5, 15);
        printf("[Consumidor]: Se precisan %u monedas.\n", monedas_necesarias);
        unsigned int monedas_disponibles = 0, monedas_recibidas;

        while (monedas_disponibles < monedas_necesarias)
        {
            printf("[Consumidor]: No tengo monedas suficientes. Notificando la situación al padre.\n");
            sleep(1);

            kill(getppid(), SIGUSR1); //Notificamos al padre que necesito monedas.
            fd = open(myfifo, O_RDONLY | O_NONBLOCK);
            printf("[Consumidor]: Esperando una señal antes de leer.\n");
            pause();

            //leo las monedas y las añado a las monedas disponibles
            read(fd, &monedas_recibidas, sizeof(unsigned int));
            monedas_disponibles += monedas_recibidas; //añado las recibidas a las que ya tenía.
            close(fd);
            printf("[Consumidor]: Recibidas %u monedas del productor, ya tengo %u en total.\n", monedas_recibidas, monedas_disponibles);
        }

        printf("[Consumidor]: Ya puedo construir, la construcción tardará 5 segundos.\n");
        sleep(5);
        printf("[Consumidor]: Construcción finalizada, notificando al padre.\n");
        kill(getppid(), SIGUSR2); //desbloqueo al padre
        //final del código del consumidor.
    }
    else
    { // Código del padre, me quedo esperando la señal inicial:
        char buffer[6];
        sprintf(buffer, "%d", consumidor);
        
        pid_t productor = fork();
        if (productor == 0)
        {
            if (execlp("./productor.exe", "./productor.exe", buffer, NULL) == -1)
            {
                perror("Error al lanzar programa");
            }
        }

        else
        {
            pause();
            while (!final)
            {
                //Si he recibido una señal y no se ha acabado la construcción, es que tengo que notificar al prodcutor
                kill(productor, SIGUSR1);
                printf("[Padre]: Esperando una señal...\n");
                pause(); //me quedo esperando la siguiente señal.
            }
            //el consumidor ha terminado, lo espero.
            wait(NULL);
            //enviando la señal de finali al productor para que se desbloquee actualizando su valor de final.
            kill(productor, SIGUSR2);
            //esperando al productor
            wait(NULL);
        }
    }
}