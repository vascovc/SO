#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct
{
    int age;
    double height;
    char name[64];
} Person;

void printPersonInfo(Person *p)
{
    printf("Person: %s, %d, %f\n", p->name, p->age, p->height);
}

int main (int argc, char *argv[])
{
    FILE *fp = NULL;
    int i;
    Person p;

    /* Validate number of arguments */
    if(argc != 2)
    {
        printf("USAGE: %s fileName\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Open the file provided as argument */
    errno = 0;
    fp = fopen(argv[1], "wb");
    if(fp == NULL)
    {
        perror ("Error opening file!");
        return EXIT_FAILURE;
    }
    printf("numero de pessoas a guardar: ");
    int number_people;
    scanf("%d",&number_people);
    /* Write n itens on a file */
    for(i = 0 ; i < number_people ; i++)
    {    
    	printf("nome: ");
    	scanf("%c",p.name);
    	scanf("%[^\n]",p.name);
    	
    	printf("idade: ");
        scanf("%d",&(p.age));
        
        printf("altura: ");
        scanf("%lf",&(p.height));
        
        fwrite(&p, sizeof(Person), 1, fp);
    }

    fclose(fp);

    return EXIT_SUCCESS;
}
