#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    FILE *fichero = NULL;

    char aux[6];

    fichero = popen("pgrep productor", "r");
    if (fichero == NULL)
    {
        perror("No se puede abrir fichero");
        exit(-1);
    }
    char* pidProd = fgets (aux, 6, fichero);
    pid_t pidP = atoi(pidProd);
    

    return 0;
}
