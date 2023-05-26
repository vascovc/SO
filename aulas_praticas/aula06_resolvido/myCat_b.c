#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/* SUGESTÂO: utilize as páginas do manual para conhecer mais sobre as funções usadas:
 man fopen
 man fgets
*/

#define LINEMAXSIZE 80 /* or other suitable maximum line size */


int main(int argc, char *argv[])
{
    FILE *fp = NULL;
    char line [LINEMAXSIZE]; 

    /* Validate number of arguments */
    if( argc < 2 )
    {
        printf("USAGE: %s fileName\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    /* Open the file provided as argument */
    errno = 0;
    for(int i=1;i<argc;i++){
	    fp = fopen(argv[i], "r");
	    if( fp == NULL ){
			perror ("Error opening file!");
			return EXIT_FAILURE;
	    }

	    /* Read all the lines of the file */
	    int line_number=1;
	    int control=0;
	    while( fgets(line, sizeof(line), fp) != NULL )
	    {
	        if(control==1)
	            printf("%s",line);
	        else{
	            printf("%d:-> %s",line_number,line);
	            line_number++;
		}
	    	if( strlen(line) == LINEMAXSIZE-1)
	    	    control=1;
		else
		    control=0;
	    }
		printf("\n");
	    fclose(fp);
	}
    return EXIT_SUCCESS;
}
