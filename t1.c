#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>


FILE *ptr;
int comment;



int main()
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    struct rusage r_usage;
    getrusage(RUSAGE_SELF,&r_usage);

    ptr = fopen("10gb.vcf", "r");
    char ch;
    int columns = 0;
    printf("\n\nContents of this file are -: \n");
        do{
            ch = fgetc(ptr);
		    int n=500;
		    char buf[n];
		    if (ch == '#'){
				ch=fgetc(ptr);
                if(ch =='#'){
					fgets(buf,n,ptr);
                    comment++;
                    continue;
				} 
                else{
                    char *buffer;
                    size_t bufsize = 10000;
                    size_t characters;
                    buffer = (char *)malloc (bufsize * sizeof (char)) ;
                    fgets(buffer,bufsize,ptr);
                    //characters = getline(&buffer,&bufsize,stdin);
                    char* token = strtok(buffer, " \t ");
                    while (token != NULL) {
                        columns ++;
                        //printf("%s ", token);
		                token = strtok(NULL, " \t ");
	                }
                    free(buffer);
                }
            }        
        }while(ch != EOF);

        columns = columns - 1;
        printf("comment:%d columns:%d\n\n",comment,columns);
        fclose(ptr);

        
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Code took %f seconds to execute \n", cpu_time_used);

        printf("Memory usage: %ld megabytes\n",r_usage.ru_maxrss/1024);  //Print the maximum resident set size used (in kilobytes)
         

        return 0;
}