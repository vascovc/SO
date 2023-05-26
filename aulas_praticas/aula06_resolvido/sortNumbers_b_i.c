#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* SUGESTÂO: utilize as páginas do manual para conhecer mais sobre as funções usadas:
 man qsort
*/
#define numbers_array_max_size 100
#define LINEMAXSIZE 300

int compareInts(const void *px1, const void *px2)
{
    int x1 = *((int *)px1);
    int x2 = *((int *)px2);
    return(x1 < x2 ? -1 : x1 == x2 ? 0 : 1);
}

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	int *numbers;
	char line [LINEMAXSIZE]; 
	if( argc < 2 ){
		printf("USAGE: %s fileName\n", argv[0]);
		return EXIT_FAILURE;
    }
    fp = fopen(argv[1], "r");
    /* Memory allocation for all the numbers in the arguments */
    numbers = (int *) malloc(sizeof(int) * numbers_array_max_size);
    int counter=0;
    while( fgets(line, sizeof(line), fp) != NULL )
	{
		line[strcspn(line,"\n")];
	    numbers[counter++]=atoi(line);
	}
	//numbers = realloc( numbers, counter*sizeof(int) );
	//isto serve para diminuir o array ao tamanho estritamente necessário
	
    /* void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *)); 
         The qsort() function sorts an array with nmemb elements of size size.*/
    qsort(numbers, counter, sizeof(int), compareInts);

    /* Printing the sorted numbers */
    printf("Sorted numbers: \n");
    for(int i = 0 ; i < counter ; i++)
    {
        printf("%d\n", numbers[i]);
    }

	free(numbers);
    return EXIT_SUCCESS;
}
