#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kmeans.h"

int main()
{
	double (*centr)[1000] = calloc(1000,sizeof(*centr));
	//float centr[1000][1000];
	FILE *p = fopen("details.txt","r");
	char *buf;
	size_t bufs = 1000;
	buf = (char *) malloc(bufs * sizeof (char));
	fgets(buf, bufs, p);
	char *tok = strtok(buf,"\t");
	int n;
	int g_count;
	int n_clust;
	int itr;
	n = atoi(tok);
	tok = strtok(NULL, " \t ");
	g_count = atoi(tok);
	tok = strtok(NULL, " \t ");
	n_clust = atoi(tok);
	tok = strtok(NULL, " \t ");
	itr = atoi(tok);
	free(buf);
	fclose(p);
	double centroids[n_clust][g_count];
	double datac[n][g_count+1];
	FILE *pt = fopen("data.txt","r");
	char *buffer;
	size_t bufsize = 10000;
	buffer = (char *) malloc(bufsize * sizeof (char)) ;
	for (int m=0;m<n;m++) {
		fgets(buffer, bufsize, pt);
		char* token = strtok(buffer, " \t ");
		for (int n=0; n<g_count; n++){
			if (m < n_clust) {
				centroids[m][n] = atof(token);
			}
			datac[m][n] = atof(token);
			token = strtok(NULL, " \t ");
		}
	}
	printf("%d\t%d\t%d\t%d",n,g_count,n_clust,itr);
	/*int itrr = Kmeans(n,g_count,n_clust,centroids,datac,centr,itr);
	for(int j = 0; j < itrr + 1; j++) {
		for (int i=0; i<n_clust; i++) {
				for (int k=0; k<g_count; k++) {
					printf("%f ", centr[i][k]);
				}
				printf("\n");
		}
		printf("\n");
	}*/
}