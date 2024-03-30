Project Title: VCF Processing and K-Means Clustering for Genomic Analysis

Purpose:
    This project is designed for population analysis using genomic data. It preprocesses VCF files and applies K-means clustering to discover sub-populations based on genetic similarities.

Software to be used:
    1. C compiler (e.g., GCC)
    2. GNUplot (if using the visualization component)
    3. Libraries/Tools:
    -----

Code Files:
    vcf_read.c: VCF file parsing, data filtering, and transformation.
    kmeans.c: Core K-means clustering algorithm implementation.
    kmeans.h: Header file declaring the K-means function.
    main.c (or pp.c): Main project driver, handles input, function calls, and output.
    gnu.c: GNUplot interaction for visualization (optional).

Data Files:
    gid.txt: Genome ID to VCF column mapping.
    smat.dat: Scoring matrix for data transformation.
    sample_big.vcf: An example VCF file.

Output Files:
    data.txt: Transformed data ready for clustering.
    final.txt (or file1.txt): Centroid coordinates (potentially across iterations).
    cluster.txt: Potentially, cluster assignments for data points.
    result.gif: Animation of clustering process (if using GNUplot).

Compilation Instructions - 
    1. Ensure you have a C compiler (e.g., GCC) installed.
    2. Navigate to the project directory in your terminal.
    3. Compile the code:
        gcc -o project_name vcf_read.c kmeans.c main.c -lm  # '-lm' for math functions
        (Replace project_name with your desired executable name.)

Usage:-
    ./project_name <chromosome_of_interest> <path_to_vcf_file> <min_mutation_rate> <max_mutation_rate> <path_to_gid_file> <path_to_scoring_matrix> <num_clusters> <max_iterations> 

Example
    ./project_name 3 ../data/sample_big.vcf 10.0 20.0 ../data/gid.txt ../data/smat.dat 5 100

Visualization:-
    1. Ensure you have GNUplot installed.
    2. After running the program, result.gif should be generated. You can view this animation using image viewing software or a web browser.

Notes:-
    1. Adjust file paths and parameters as needed for your specific project setup.
    2. Consider providing more details about input file formats (VCF, gid, scoring matrix).
    3. You may want to include an example of interpreting the clustering results.

Contact:
    Include your name and contact information if you're open to questions or feedback.

