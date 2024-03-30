#include <stdio.h>
#include <math.h>

void Kmeans()
{
	FILE *fptr1, *fptr2;
	fptr1 = fopen("file1.txt", "w");
	fptr2 = fopen("datapoints.txt", "w");
	int n;
	int dim;
	int n_clust;
	int itr = 0;
	scanf("%d%d%d", &n, &dim, &n_clust);
	double centroids[n_clust][dim];
	for (int i=0; i<n_clust; i++) {
		for (int j=0; j<dim; j++) {
			scanf("%lf", &centroids[i][j]);
			fprintf(fptr1, "%f ", centroids[i][j]);
		}
		fprintf(fptr1, "\n");
	}

	fprintf(fptr1, "\n\n");

	int cen_num[n];
	for (int i=0; i<n; i++) {
		cen_num[i] = -1;
	}
	int data[n][dim + 1];
	for (int i=0; i<n; i++) {
		for (int j=0; j<dim; j++) {
			scanf("%d", &data[i][j]);
		}
	}

	double min=999999;
	double dis =0;
	double sum =0;
	while (itr != 1) {
		int arr[dim];
		for (int i=0; i<n; i++) {
			for(int j = 0; j < dim; j++) {
				fprintf(fptr2, "%d ", data[i][j]);
			}
			min = 999999;
			for (int k=0; k<n_clust; k++) {
				sum =0;
				dis = 0;
				for (int j=0; j<dim; j++) {
					sum = sum + pow((centroids[k][j] - data[i][j]),2);
				}
				dis = sqrt(sum);
				if(min > dis) {
					min = dis;
					cen_num[i]=k;
					data[i][dim] = k;
				}
			}
			fprintf(fptr2, "%d \n", data[i][dim]);
		}
		for (int i=0; i<n_clust; i++) {
			for (int k=0; k<dim; k++) {
				double sum = 0;
				int count = 0;
				for (int j=0; j<n; j++) {
					if (cen_num[j] == i) {
						sum = sum + data[j][k];
						count++;
					}
				}
				if(centroids[i][k] == sum/count) {
					arr[k] = 1;
				}
				centroids[i][k] = sum/count;
				fprintf(fptr1, "%f ", centroids[i][k]);

			}
			fprintf(fptr1, "\n");
		}
		fprintf(fptr1, "\n\n");
		fprintf(fptr2, "\n\n");
		int flag = 0;
		for(int i = 0; i < dim; i++) {
			if(arr[i] != 1) {
				flag = 1;
			}
		}
		if(flag == 0) {
			itr = 1;
		}
				
	}
	printf("Centroid num:\n");
	for (int i=0; i<n; i++) {
		printf("%d\n",cen_num[i]);
	}
	printf("Centroids:\n");
	for (int i=0; i<n_clust; i++) {
		for (int j=0; j<dim; j++) {
			printf("%1f ",centroids[i][j]);
		}
		printf("\n");
	}
}
