#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//#define strcmp strcasecmp // isto resolve a alinea a)
int main(int argc, char **argv){
	char array[argc-1][30];
	int count = 0;
	for(int i=1;i<argc;i++)
		if(isalpha(argv[i][0])){
			strcpy(array[count], argv[i]);
			count++;
		}	
	int i, j;
	// export SORTORDER="Descending"
	if (strcmp( getenv("SORTORDER") , "Descending") == 0){
		for (i = 1; i < count; i++){ 
			j = i;
			while (j > 0 && strcmp(array[j-1],array[j]) > 0){
				char temp[30]; 
				strcpy(temp, array[j-1]);
				strcpy(array[j-1],array[j]);
				strcpy(array[j],temp);
				j--;
			}
		}	
	}
	else if( strcmp( getenv("SORTORDER"),"Ascending") == 0 ){
		for (i = 1; i < count; i++){ 
			j = i;
			while (j > 0 && strcmp(array[j],array[j-1]) > 0){
				char temp[30]; 
				strcpy(temp, array[j-1]);
				strcpy(array[j-1],array[j]);
				strcpy(array[j],temp);
				j--;
			}
		}
	}
	else{
		printf("Order sort not defined\n");
		return EXIT_FAILURE;
	}
	for(int i=0; i<count;i++)
		printf("%s\n",array[i]);
}

//alinea a
// utilizando tolower apenas se consegue fazer caracter a caracter
//mas pode-se utilizar a funcao strcasecmp em vez de strcmp


