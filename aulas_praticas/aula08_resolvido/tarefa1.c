#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int ret;
    int before=getpid();
    printf("Antes do fork: PID = %d, PPID = %d\n", before, getppid());
    if ((ret = fork()) < 0) { 
        perror("erro na duplicação do processo");
        return EXIT_FAILURE;
    }
    //usando o ret podemos ver mas tambem se pode usar o getpid para ver se e igual ao anterior
    if (ret > 0){
    	sleep(1);
    	printf("Quem sou eu?\nO PAI\nApós o fork: PID = %d, PPID = %d, retorno do fork = %d\n",
           getpid(), getppid(), ret);
    }
    else
    	printf("Quem sou eu?\nO FILHO\nApós o fork: PID = %d, PPID = %d, retorno do fork = %d\n",
           getpid(), getppid(), ret);
    return EXIT_SUCCESS;
}
