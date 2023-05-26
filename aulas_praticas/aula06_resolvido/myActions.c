#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
/* SUGESTÂO: utilize as páginas do manual para conhecer mais sobre as funções usadas:
 man system
 man date
*/

int main(int argc, char *argv[])
{
    char text[1024];
    FILE *fp = NULL;
    fp = fopen("command.log", "a");
    do
    {
        printf("Command: ");
        scanf("%1023[^\n]%*c", text);

        /* system(const char *command) executes a command specified in command
            by calling /bin/sh -c command, and returns after the command has been
            completed.
        */
        if(strcmp(text, "end")) {
            time_t rawtime;
            struct tm * timeinfo;
            time ( &rawtime );
            timeinfo = localtime ( &rawtime );
            printf("\n *: Command to be executed: %s\n", text);
            printf("---------------------------------\n");
            system(text);
            printf("---------------------------------\n");
            fprintf(fp,"%sCommand to be executed: %s\n",asctime(timeinfo), text);
        }
    } while(strcmp(text, "end"));

    printf("-----------The End---------------\n");
    fclose(fp);
    return EXIT_SUCCESS;
}
