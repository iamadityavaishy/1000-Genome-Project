#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <unistd.h>

FILE *ptr;
int  row_count, cnt = 10;
void filter(int, char [], char []);
void ref_access(char [], int, char [], char []);
void alt_access(int, char [], char []);
void mut(int, char [], char []);

int main(int arg_count, char** arg_vector)
{
	ptr = fopen(arg_vector[2], "r");
	char ch;
	int columns = 0;
	//printf("\n\nContents of this file are -: \n");

	do {
		ch = fgetc(ptr);
		int n=500;
		char buf[n];
		if (ch == '#') {
			ch = fgetc(ptr);
			if (ch == '#') {
				fgets(buf, n, ptr);
				//comment++;
				continue;
			} else {
				char *buffer;
				size_t bufsize = 100000;
				//size_t characters;
		
				buffer = (char *) malloc(bufsize * sizeof (char)) ;
			
				fgets(buffer, bufsize, ptr);
				char* token = strtok(buffer, " \t ");
				while (token != NULL) {
					columns ++;
					token = strtok(NULL, " \t ");
				}

				free(buffer);
				break;
			}
		}
	}while (ch != EOF);

	//printf("comment:%d \ncolumns:%d", comment, columns);
	ref_access(arg_vector[1], columns, arg_vector[3], arg_vector[4]);

	printf("%d\n", row_count);
	fclose(ptr);

	return 0;			// remember to use "time ./a.out" after compilation
}

void filter(int columns, char min[], char max[])
{
	char ch = fgetc(ptr);
	while (ch != '\t') {
		ch = fgetc(ptr);
	}

	char buffer[4];
	int i=0;
	ch = fgetc(ptr);

	while (ch != '\t' && i < 4) {
		buffer[i] = ch;
		ch = fgetc(ptr);
		i++;
	}

	if (buffer[0] == 'P' && buffer[1] == 'A' && buffer[2] == 'S' && buffer[3] == 'S') {
		mut(columns, min, max);
	} else {
			return;
		}
}

void alt_access(int columns, char min[], char max[])
{
	char ch = fgetc(ptr);
	//char *str;
	int flag = 0;

	while (ch != '\t') {
		char w = fgetc(ptr);
		if (w == ',' || w == '\t') {
			if (ch != 'A' && ch != 'G' && ch != 'T' && ch != 'C') {
				flag = 0;
				break;
			} else {
				//genome[i] = ch;
				//i++;
				flag = 1;
			}
		} else {
			break;
		}
		ch = fgetc(ptr);
	}
	if (flag == 1) {
		filter(columns, min, max);
		//printf("%s\n",genome);
	}
}

void ref_access(char given_chrom[2], int columns, char min[], char max[])
{
	int count_tab = 0;
	char chrom[2] = "\0";
	char ch = fgetc(ptr);
	chrom[0] = ch;
	ch = fgetc(ptr);
	chrom[1] = ch;
	int flag = 1;
	while (ch != EOF) {
		if (flag == 1) {
			if(strcmp(chrom, given_chrom) != 0) {
				char *buffer;
				size_t bufsize = 100000;
				//size_t characters;
				buffer = (char *) malloc(bufsize * sizeof (char));
				count_tab = 0;
				fgets(buffer,bufsize,ptr);
				free(buffer);
				ch = fgetc(ptr);
				chrom[0] = ch;
				ch = fgetc(ptr);
				chrom[1] = ch;
				flag = 1;
				buffer = NULL;
			} else {
				flag = 0;
			}
		}
		if (ch == '\t') {
			count_tab++;
		}
		if (count_tab == 3) {
			ch = fgetc(ptr);

			if((ch == 'A' || ch == 'G' || ch == 'T' || ch == 'C') && fgetc(ptr) == '\t') {
				//i=0;
				//genome[i]=ch;
				//i++;
				count_tab = 0;
				alt_access(columns, min, max);
				continue;
			}
			char *buffer;
			size_t bufsize = 100000;
			//size_t characters;
			buffer = (char *) malloc(bufsize * sizeof (char));
			count_tab = 0;
			fgets(buffer,bufsize,ptr);
			free(buffer);
			ch = fgetc(ptr);
			chrom[0] = ch;
			ch = fgetc(ptr);
			chrom[1] = ch;
			flag = 1;
			buffer = NULL;
		}
		ch = fgetc(ptr); 
	}
}

void mut(int columns, char min[], char max[])
{
	char ch = fgetc(ptr);
	int q = columns - 9;
	int count_tab = 0;
	double mut_count = 0;
	while(q != 0) {
		mut_count = 0;
		if (ch == '\t') {
			count_tab++;
			q--;
		}
		if (count_tab == 2){
			char *buffer;
			size_t bufsize = 1000000;
			//size_t characters;
			buffer = (char *)malloc (bufsize * sizeof (char)) ;
			fgets(buffer,bufsize,ptr);
			char* token = strtok(buffer, "\t");
			while (token != NULL) {
				if (token[0] != '0' || token[2] != '0') {
					mut_count++;
				}
				token = strtok(NULL, "\t");
			}
			columns = columns - 9;
			mut_count = ((mut_count/columns) * 100);
			if (mut_count <= atof(max) && mut_count >= atof(min)) {
				row_count++;
			}
			free(buffer);
			break;
		}
		ch = fgetc(ptr);
	}
}
