#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    FILE *gnu_ptr = popen("gnuplot -persitent", "w");

    char *gnu_commands[] =
        {
         "stats \'final.txt\'",
         "set term gif animate delay 200 size 1280,720",
         "set output \'result.gif\'",
         "splot \"cluster.txt\" using 1:2:3:4 ps 1 pt 5 lt 7 lc variable title \'Cluster Data\'",
         "do for [i = 0:int(STATS_blocks-1)]{replot \'cluster.txt\' index i using 1:2:3:4 ps 2 pt 9 lc variable title \'\', \'final.txt\' index i+1 using 1:2:3 ps 4 pt 7 lc variable title\'\'}"
         };

    for (int i = 0; i < 5; i++)
    {
        fprintf(gnu_ptr, "%s\n", gnu_commands[i]);
    }

    return 0;
}
//         "set style fill transparent solid 0.50 border",
/* {
         "stats \'centroids_data.txt\' name \'no_of_centroid\'",
         "set term gif animate delay 200 size 1280,720",
         "set output \'graph.gif\'",
         "splot \"cluster.txt\" using 1:2:3 ps 1 pt 5 lt 7 lc variable title \'Cluster Data\'",
         "do for [i = 0:int(no_of_centroid_blocks)]{replot \'cluster.txt\' index i using 1:2:3:4 ps 2 pt 9 lc variable title \'\', \'centroids_data.txt\' index i+1 using 1:2:3 ps 4 pt 7 lc variable title \'\'}"
         };*/

         //  w lp (with line connecting)