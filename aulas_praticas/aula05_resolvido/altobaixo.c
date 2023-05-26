#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int upper; int lower;
	if( atoi(argv[1]) > atoi(argv[2] )
		upper = atoi(argv[1]);
		lower = atoi(argv[2]);
	else
		lower = atoi(argv[1]);
		upper = atoi(argv[2]);
	
	int random_number = ( rand() % (upper - lower + 1) )+lower;
	int inserted_number;
	int counter = 0;
	do{
		scanf("%d", &inserted_number);
		counter++;
		if(inserted_number < random_number)
			printf("demasiado baixo\n");
		else if (inserted_number > random_number)
			printf("demasiado alto\n");
		else
			printf("era esse mesmo\n");
	}while(inserted_number != random_number);
	printf("foram precisas %d tentativas\n",counter);
}
