#include <stdio.h>
#include <string.h> // for strtok, strcmp, atof, atoi, calloc, malloc
#include <stdlib.h> 	// for atof, atoi, calloc, malloc, strcmp
//#include <time.h>
//#include <sys/resource.h>
//#include <sys/time.h>
//#include <unistd.h>
#include "kmeans.h"

FILE *ptr;
FILE *ptr_w;
int row_count, cnt = 10;
void filter(char [], int, char [], char [], char [], int, int [], int, float [][4]);
void ref_access(char [], int, char [], char [], char [], int, int [], int, float [][4]);
void alt_access(char [], int, char [], char [], char [], int, int [], int, float [][4]);
void mut(char [], int, char [], char [],char [], int, int [], int, float [][4]);
int gid_pos_no(char [], int *, char []);
void data_map(char [],char [], int, int, int, int,float [][4]);

int main(int arg_count, char** arg_vector)
{
	ptr = fopen(arg_vector[2], "r");
	ptr_w = fopen("data.txt","w");
	char ch;
	int columns = 0,comment;
	int g_count;
	char genome[6];
	int b;
	int gid_pos[100];
	float scoring_matrix[4][4];
	FILE *ptr_s = fopen(arg_vector[6],"r");
	char *buffer_s;
	size_t bufsize_s = 25;
	buffer_s = (char *) malloc(bufsize_s * sizeof(char));
	for (int i=0; i<4; i++) {
		int j=0;
		fgets(buffer_s,bufsize_s,ptr_s);
		char* tok_s = strtok(buffer_s, " ");
		while (tok_s != NULL) {
			scoring_matrix[i][j] = atof(tok_s);
			j++;
			tok_s = strtok(NULL, " ");
		}
	} 
	free(buffer_s);
	fclose(ptr_s);
	//printf("\n\nContents of this file are -: \n");
	do {
		ch = fgetc(ptr);
		int n=500;
		char buf[n];
		if (ch == '#') {
			ch = fgetc(ptr);
			if (ch == '#') {
				fgets(buf, n, ptr);
				comment++;
				continue;
			} else {
				char *buffer;
				size_t bufsize = 100000;
				//size_t characters;
				buffer = (char *) malloc(bufsize * sizeof (char)) ;
				fgets(buffer, bufsize, ptr);
				g_count = gid_pos_no(arg_vector[5],gid_pos,buffer);
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

	//printf("comment:%d \ncolumns:%d\n", comment, columns);
	//passing chrom_no,no_of_cols,min_mut,max_mut
	ref_access(arg_vector[1], columns, arg_vector[3], arg_vector[4], genome, b, gid_pos, g_count, scoring_matrix);
	printf("%d\n", row_count);
	fclose(ptr);
	fclose(ptr_w);
	int n_clust = atoi(arg_vector[7]);
	double centroids[n_clust][g_count];
	double datac[row_count][g_count];
	FILE *pt = fopen("data.txt","r");
	char *buffer;
	size_t bufsize = 10000;
	buffer = (char *) malloc(bufsize * sizeof (char)) ;
	for (int m=0;m<row_count;m++) {
		fgets(buffer, bufsize, pt);
		char* token = strtok(buffer, " \t ");
		for (int n=0; n<g_count; n++){
			if (m<n_clust) {
				centroids[n][m] = atof(token);
			}
			datac[n][m] = atof(token);
			token = strtok(NULL, " \t ");
		}
	}
	for (int m=0;m<g_count;m++) {
		printf("%d : \n",m);
		for (int n=0; n<row_count; n++){
			printf("%f,",datac[m][n]);
		}
		printf("\n");
	}
	printf("%d\t%d\t%d\t%d",row_count,g_count,n_clust,atoi(arg_vector[8]));
	double (*centr)[1000] = calloc(1000,sizeof(*centr));
	int itrr = Kmeans(row_count,g_count,n_clust,centroids,datac,centr,atoi(arg_vector[8]));
	for (int i=0; i<n_clust; i++) {
		printf("%d", gid_pos[i]);
		for (int k=0; k<4; k++) {
			printf("%.3f,", centroids[i][k]);
		}
		printf(" %d\n",i);
	}
return 0;			// remember to use "time ./a.out" after compilation
}

int gid_pos_no(char g_file[],int gid_pos[],char header[])
{
	FILE *g_ptr = fopen(g_file,"r");
	int count = 0;
	int c = 0;
	char arr[100000];
	strcpy(arr,header);
	char *buffer;
	size_t bufsize = 8;
	//size_t characters;
	buffer = (char *) malloc(bufsize * sizeof (char)) ;
	fgets(buffer, bufsize, g_ptr);
	do{
		strcpy(arr,header);
		c++;
		int count =0;
		char* token = strtok(arr, " \t ");
		while (token != NULL) {
			count ++;
			if (strcmp(buffer,token)==0) {
				*gid_pos = count;
				gid_pos++;
				break;
			}
			token = strtok(NULL, " \t ");
		}
		fgets(buffer, bufsize, g_ptr);     
	} while(fgets(buffer, bufsize, g_ptr) != NULL);
	return c;
}

void filter(char string[], int columns, char min[], char max[], char genome[], int b, int gid_pos[], int g_count, float scoring_matrix[][4])
{
	char* token = strtok(string, "\t");
	token = strtok(NULL, "\t");
	if (token[0] == 'P' && token[1] == 'A' && token[2] == 'S' && token[3] == 'S') {
		token = strtok(NULL, "\n");
		mut(token, columns, min, max, genome, b, gid_pos, g_count, scoring_matrix);
	} else {
		return;
	}
}

void alt_access(char string[], int columns, char min[], char max[],char genome[], int b, int gid_pos[], int g_count, float scoring_matrix[][4])
{
	char* token = strtok(string, "\t");
	char ch = token[0];
	int h=0;
	//char *str;
	int flag = 0;
	while (ch != '\0') {
		h++;
		char w = token[h];
		if (w == ',' || w == '\0') {
			if (ch != 'A' && ch != 'G' && ch != 'T' && ch != 'C') {
				flag = 0;
				break;
			} else {
				genome[b] = ch;
				b++;
				flag = 1;
			}
		} else {
			break;
		}
		h++;
		ch = token[h];
	}
	if (flag == 1) {
		token = strtok(NULL, "\n");
		filter(token, columns, min, max,genome, b, gid_pos, g_count,scoring_matrix);
	}
}

void ref_access(char given_chrom[2], int columns, char min[], char max[], char genome[], int b, int gid_pos[], int g_count, float scoring_matrix[][4])
{
	int count_tab = 0;
	char *buffer;
	size_t bufsize = 100000;
				//size_t characters;
	buffer = (char *) malloc(bufsize * sizeof (char));
	while(fgets(buffer,bufsize,ptr)) {
		count_tab = 0;
		char* token = strtok(buffer, "\t");
		count_tab++;
		if (strcmp(token, given_chrom) == 0) {
			while (count_tab != 3) {
				token = strtok(NULL, "\t");
				count_tab++;
			}
			if (count_tab == 3) {
				token = strtok(NULL, "\t");
				if(strcmp(token,"A")==0 || strcmp(token,"G")==0 || strcmp(token,"T")==0 || strcmp(token,"C")==0) {
					b=0;
					genome[b]=token[0];
					b++;
					count_tab = 0;
					token = strtok(NULL, "\n");
					//row_count++;
					alt_access(token, columns, min, max,genome, b, gid_pos, g_count, scoring_matrix);
				}
			}
		}
	}
}

void mut(char string[], int columns, char min[], char max[],char genome[], int b, int gid_pos[], int g_count, float scoring_matrix[][4])
{
	char* token = strtok(string, "\t");
	token = strtok(NULL, "\t");
	int count_tab = 0;
	double mut_count = 0;
	token = strtok(NULL, "\n");
	char arr[1000000] ;
	char arr1[1000000];
	strcpy(arr,token);
	strcpy(arr1,token);
	char* tok = strtok(token, "\t");
	while (tok != NULL) {
		if (tok[0] != '0' || tok[2] != '0') {
			mut_count++;
		}
		tok = strtok(NULL, "\t");
	}
	columns = columns - 9;
	mut_count = ((mut_count/columns) * 100);
	//printf("%f \n", mut_count);
	if (mut_count <= atof(max) && mut_count >= atof(min)) {
		row_count++;
		for (int i=0; i<g_count; i++) {
			data_map(arr, genome, b, gid_pos[i], g_count,columns, scoring_matrix);
			strcpy(arr,arr1);
		}
		fprintf(ptr_w,"\n");
	}
}

void data_map(char arr[], char genome[], int b, int gid_pos, int g_count, int columns, float scoring_matrix[][4])
{
   //printf("%s", arr);
	int pos = 0;
	char* token = strtok(arr, "\t");
	while (pos != gid_pos-10) {
		token = strtok(NULL, "\t");
		pos++;
	}
	int x=0,y=0;
	switch(genome[token[0]-48]) {
		case 'A': 
			x = 0;
			break;
		case 'C':
			x = 1;
			break;
		case 'G':
			x = 2;
			break;
		case 'T':
			x = 3;
			break;
		}
		switch(genome[token[2]-48]) {
			case 'A': 
				y = 0;
				break;
			case 'C':
				y = 1;
				break;
			case 'G':
				y = 2;
				break;
			case 'T':
				y = 3;
				break;
		}
		//printf("x: %d y: %d smat:%f\n",x, y, scoring_matrix[x][y]);
		fprintf(ptr_w,"%f ",scoring_matrix[x][y]);
}
