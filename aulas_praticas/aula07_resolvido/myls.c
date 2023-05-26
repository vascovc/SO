#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

//codigo nao testado
int main(int argc, char *argv[])
{

    /* The getopt() function parses the command-line arguments. Its arguments
      argc and argv are the argument count and array as passed to the main()
      function on program invocation. An element of argv that starts with
      '-' (and is not exactly "-" or "--") is an option element. The charac‐
      ters of this element (aside from the initial '-') are option charac‐
      ters.  If getopt() is called repeatedly, it returns successively each
      of the option characters from each of the option elements.

      For more information check the man page (man 3 getopt) 
     */
    int opt;
    int file=0;int dir=0;int exten=0;char ext[4];
    while ((opt = getopt(argc, argv, "fde:")) != -1)
    {
        switch (opt)
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
            default: /* '?' */
                fprintf(stderr, "Invalid option");
                exit(EXIT_FAILURE);
        }
    }

    /* By default, getopt() permutes the contents of argv as it scans, so that
      eventually all the nonoptions are at the end.
     */
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
