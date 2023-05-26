#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
	if(argc != 4){
    		printf("numero de parametros invalidos\n");
    		return 8;
    	}
    	float result;
    	switch(argv[2][0]){ // e preciso ser assim porque so queremos o primeiro char do array de string que é argv[i]
    		case '+':
    			result = atof(argv[1]) + atof(argv[3]);
	    		break;
	    	case '-':
	    		result = atof(argv[1]) - atof(argv[3]);
	    		break;
	    	case 'x':
	    		result = atof(argv[1]) * atof(argv[3]);
	    		break;
	    	case '/':
	    		result = atof(argv[1]) / atof(argv[3]);
	    		break;
	    	case 'p':
	    		result = pow( atoi(argv[1]),atoi(argv[3]) );
	    		break;
	    	default:
	    		printf("operando errado\n");
	    		return EXIT_FAILURE;
    	}
    	printf("%2.2f\n",result);
}
// alinea d
//ficou por fazer em calculadora_d.c

// alinea e
// nao funciona porque a bash expande o asterisco, ou seja todos os ficheiros da diretoria

