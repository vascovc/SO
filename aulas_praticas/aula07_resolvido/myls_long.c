#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <dirent.h>

/* https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Option-Example.html */
int main(int argc, char *argv[])
{
    int c;
    int digit_optind = 0;
    int option_index = 0;
    struct option long_options[] = {
            { "file", no_argument, 0,  'f'  },
            { "dir",  no_argument, 0,  'd'  },
            { "ext",  no_argument, 0, 'e' }
    };
    int file=0;int dir=0;int exten=0;char ext[4];
    while ( (c = getopt_long(argc, argv, "fde",
                            long_options, &option_index)
            ) != -1 
          )
    {
        int this_option_optind = optind ? optind : 1;
        switch (c)
        {
            case 'f':
                file=1;
                break;
            case 'd':
                dir=1;
                break;
            case 'e':
                exten=1;
            	strcpy(ext,optarg);
                break;
            case '?':
                break;
            default:
                printf("?? getopt returned character code 0%o ??\n", c);
        }
    }
    
	if (optind >= argc)
    {
        fprintf(stderr, "Expected argument after options\n");
        return EXIT_FAILURE;
    }
    DIR *dp; 
    struct dirent *dent;
	while(optind < argc){
		dp = opendir(argv[optind]); 
		if(dp == NULL)
		{
		    perror("Error opening directory");
		    return EXIT_FAILURE;
		}

		dent = readdir(dp);
		while(dent!=NULL) 
		{
		    if(dent->d_name[0] != '.')
		    {
		        if (dir==1 && dent->d_type==DT_DIR){
		        	printf("d %s/%s\n",argv[optind],dent->d_name);
		        }
		        else if(file==1 && dent->d_type==DT_REG) 
		            printf("  %s/%s\n",argv[optind],dent->d_name);
		        else if(exten==1 && dent->d_type==DT_REG){
		        	char *dot = strrchr(dent->d_name,'.');
		        	if(!strcmp(dot+1,ext))
		        		printf("  %s/%s\n",argv[optind],dent->d_name);
		        }		        	
		    }
		    dent = readdir(dp);
		}
		optind++;
	}
    return EXIT_SUCCESS;
}
