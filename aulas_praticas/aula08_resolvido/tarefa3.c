#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int stat;

    printf("==========================================\n");
    switch (fork())
    {
      case -1: /* fork falhou */
               perror("Erro no fork\n");
               return EXIT_FAILURE;
      case 0:  /* processo filho */
               if (execl("/bin/ls", "ls", "-la", NULL) < 0) { 
                   perror("erro no lancamento da aplicacao");
                   return EXIT_FAILURE;
               }
               break;
      default: /* processo pai */
               if (wait(&stat) < 0) { 
                   perror("erro na espera da terminação do processo-filho");
                   return EXIT_FAILURE;
               }
               printf("============================================\n");
    }

    return EXIT_SUCCESS;
}
