#include <stdio.h>
#include "kmeans.h"

int main()
{
	FILE *fptr1, *fptr2;
	fptr1 = fopen("file1.txt", "w");
	fptr2 = fopen("datapoints.txt", "w");
	int n;
	int dim;
	int n_clust;
	int max_itr = 10000;
	scanf("%d%d%d", &n, &dim, &n_clust);
	double centroids[n_clust][dim];
	for (int i=0; i<n_clust; i++) {
		for (int j=0; j<dim; j++) {
			scanf("%lf", &centroids[i][j]);
		}
	}
	double data[n][dim+1];
	for (int i=0; i<n; i++) {
		for (int j=0; j<dim; j++) {
			scanf("%f", &data[i][j]);
		}
	}
	double centr[1000][1000];
	
	int itr = Kmeans(n,dim,n_clust,centroids,data,centr,max_itr);

	for(int j = 0; j < itr; j++) {
		for (int i=0; i<n; i++) {
				for(int j = 0; j < dim; j++) {
					fprintf(fptr2, "%d ", data[i][j]);
				}
				fprintf(fptr2, "%d \n", data[i][dim]);
		}
		fprintf(fptr2, "\n\n");
	}
	for(int j = 0; j < itr + 1; j++) {
		for (int i=0; i<n_clust; i++) {
				for (int k=0; k<dim; k++) {
					fprintf(fptr1, "%f ", centr[i][k]);
				}
				fprintf(fptr1, "\n");
		}
		fprintf(fptr1, "\n\n");
	}
	
	printf("Centroids:\n");
	for (int i=0; i<n_clust; i++) {
		for (int j=0; j<dim; j++) {
			printf("%1f ",centroids[i][j]);
		}
		printf("\n");
	}
}
