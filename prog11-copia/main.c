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

//creamos una variable global que guarde la condicion de finalización.
//tiene que ser global porque la vamos a modificar desde las funciones de
//tratamiento de las señales y las funciones no pueden acceder a las variables
//locales del main, ni tienen un valor de retorno, ni se les puede pasar
//un parámetro de entrada salida.

//aunque sea global, al hacer un fork se duplicará igualmente, es decir
//no se compartirá el valor entre el padre y los hijos, por eso todos los que
//sean notificados para finalizar tendrán que gestionar su notificación
bool final = false;

void gestor_senyal(int senyal)
{
    if (senyal == SIGUSR2)
    { //La señal 2 la usaremos para finalizar.
        final = true;
    }
    //cualquier otra señal que hayamos asociado a la función, no hará nada.
}

int main()
{
    pid_t consumidor;

    signal(SIGUSR1, gestor_senyal); //registramos el tratamiento de SIGUSR1
    signal(SIGUSR2, gestor_senyal); //registramos el tratamiento de SIGUSR2

    int static fd1;
    char *myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);

    char str1[80], str2[80];
    fd1 = open(myfifo, O_RDONLY);

    consumidor = fork();
    if (consumidor == -1)
    {
        perror("Error creando al consumidor.");
        exit(2);
    }

    if (consumidor == 0)
    {
        unsigned int monedas_necesarias = int_aleatorio(5, 15);
        printf("[Consumidor]: Se precisan %u monedas.\n", monedas_necesarias);
        unsigned int monedas_disponibles = 0, monedas_recibidas;
        while (monedas_disponibles < monedas_necesarias)
        {
            printf("[Consumidor]: No tengo monedas suficientes. Notificando la situación al padre.\n");
            sleep(1);
            kill(getppid(), SIGUSR1); //Notificamos al padre que necesito monedas.
            printf("[Consumidor]: Esperando una señal antes de leer.\n");
            pause();
            //leo las monedas y las añado a las monedas disponibles
            read(fd1, &monedas_recibidas, sizeof(unsigned int));
            monedas_disponibles += monedas_recibidas; //añado las recibidas a las que ya tenía.
            printf("[Consumidor]: Recibidas %u monedas del productor, ya tengo %u en total.\n", monedas_recibidas, monedas_disponibles);
        }
        //ya no voy a leer más.
        close(fd1);
        printf("[Consumidor]: Ya puedo construir, la construcción tardará 5 segundos.\n");
        sleep(5);
        printf("[Consumidor]: Construcción finalizada, notificando al padre.\n");
        kill(getppid(), SIGUSR2); //desbloqueo al padre
        //final del código del consumidor
    }
    else
    {
execl("./productor.exe")
        // Código del padre, me quedo esperando la señal inicial:
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
        //enviando señal de finali al productor para que se desbloquee actualizando su valor de final.
        kill(productor, SIGUSR2);
        //esperando al productor
        wait(NULL);
    }
}

//preguntas: En este caso. ¿Importa el orden de creación de los hijos?¿Por qué sí o por qué no?