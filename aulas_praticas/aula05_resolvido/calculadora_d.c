#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// nao ficou a trabalhar!!!!!!!!!!!!!!!!!!!

int main(int argc, char *argv[])
{
	if(argc != 4){
    		printf("numero de parametros invalidos\n");
    		return 8;
    	}
    	float result;
    	char *ptr;
    	int a = strtod( argv[1],&ptr);
    	int b = strtod( argv[3],&ptr);
    	switch(argv[2][0]){ // e preciso ser assim porque so queremos o primeiro char do array de string que é argv[i]
    		case '+':
    			result = a + b;
	    		break;
	    	case '-':
	    		result = a - b;
	    		break;
	    	case 'x':
	    		result = a * b;
	    		break;
	    	case '/':
	    		result = a / b;
	    		break;
	    	case 'p':
	    		result = pow(a,b);
	    		break;
	    	default:
	    		printf("operando errado\n");
	    		return EXIT_FAILURE;
    	}
    	printf("%2.2f\n",result);
}
