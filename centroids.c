#include <stdio.h>
#include <math.h>

int main()
{
    int n;
    int dim;
    int n_clust;
    int itr = 50;
    scanf("%d%d%d", &n, &dim, &n_clust);
    double centroids[n_clust][dim];
    for (int i=0; i<n_clust; i++) {
        for (int j=0; j<dim; j++) {
            scanf("%lf", &centroids[i][j]);
        }
    }
    int cen_num[n];
    for (int i=0; i<n; i++) {
        cen_num[i] = -1;
    }
    int data[n][dim];
    for (int i=0; i<n; i++) {
        for (int j=0; j<dim; j++) {
            scanf("%d", &data[i][j]);
        }
    }
    double min=999999;
    double dis =0;
    double sum =0;
    while (itr) {
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
            	}
        	}
		printf("\n");
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
			centroids[i][k] = sum/count;
		}
	}
    	itr--;
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
