#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

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
    Person p;
	Person array_p[100];
	
    /* Validate number of arguments */
    if(argc != 2)
    {
        printf("USAGE: %s fileName\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Open the file provided as argument */
    errno = 0;
    fp = fopen(argv[1], "r+w+b");
    if(fp == NULL)
    {
        perror ("Error opening file!");
        return EXIT_FAILURE;
    }
	int counter=0;
    /* read all the itens of the file */
    while(fread(&p, sizeof(Person), 1, fp) == 1)
    {
        printPersonInfo(&p);
        array_p[counter++]=p;
    }
    
	printf("Pretende adicionar pessoas ao ficheiro? y or n: ");
    char input[2];
    scanf("%s", input);
    scanf("%[^\n]",input);
    
    if( !strcmp(input, "y") ){
    	printf("Quantas pessoas quer guardar? ");
        int newp;
        scanf("%d",&newp);
        int cc=0;
        while(cc < newp){
        
			printf("\nnome: ");
			scanf("%c",p.name);
			scanf("%[^\n]",p.name);
			
			printf("idade: ");
		    scanf("%d",&(p.age));
		    
		    printf("altura: ");
		    scanf("%lf",&(p.height));
		   
		    array_p[counter++]=p;
		    cc++;
		}
	fseek(fp, 0, SEEK_SET);
	for(int i=0;i<counter;i++){
		printf("Person: %s, %d, %f\n", array_p[i].name, array_p[i].age, array_p[i].height);
		fwrite(&array_p[i],sizeof(Person),1,fp);
	}
    }
	else if ( !strcmp(input, "n") ){}
	else{
		printf("invalid option");
    }
    
    fclose(fp);

    return EXIT_SUCCESS;
}
