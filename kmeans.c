#include <math.h>

int Kmeans(int n, int dim, int n_clust, double centroids[][dim], double data[][dim+1], double centr[][1000],int max_itr)
{
	int itr = 0;
	int cen_num[n];
	for (int i=0; i<n; i++) {
		cen_num[i] = -1;
	}
	for (int i=0; i<n_clust; i++) {
		for (int j=0; j<dim; j++) {
			centr[i][j] = centroids[i][j];
		}
	}
	double min=999999;
	double dis =0;
	double sum =0;
	int count = 0;
	while (itr != 1) {
		int arr[dim];
		for (int i=0; i<n; i++) {
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
				centr[i][k] = centroids[i][k];
			}
		}
		int flag = 0;
		for(int i = 0; i < dim; i++) {
			if(arr[i] != 1) {
				flag = 1;
			}
		}
		if(flag == 0) {
			itr = 1;
		}
		count++;
				
	}
	return count;
}
