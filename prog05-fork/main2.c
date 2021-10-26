#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]){
    int estado_proc;
    //duplico el proceso
    pid_t pid_padre = getpid();
    pid_t pid_hijo;
    pid_t pid_proceso = fork();
    if(pid_proceso != 0)
        pid_hijo = pid_proceso;
    else
        pid_hijo = getpid();
    //Duplico el proceso, tanto padre como hijo se duplican
    fork();
    //Se devolverán 4 mensajes, uno por proceso
    printf("[Proceso %d]: Hola.\n", getpid());
    if(getpid() == pid_padre){
        wait(&estado_proc);
        wait(&estado_proc);
    }
    if(getpid() == pid_hijo){
        wait(&estado_proc);
    }
    return 0;
}