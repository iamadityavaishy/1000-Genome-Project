
# Hi, I'm Aditya! 👋


# This is the famous 1000 Genome Project

The 1000 Genomes Project set out to provide a comprehensive description of common human genetic variation by applying whole-genome sequencing to a diverse set of individuals from multiple populations. The central goal of this project is to describe most of the genetic variation that occurs at a population frequency greater than 1 percentage, the human genome comprises three billion bases, of which millions differences between any two genomes from different people.

## 🚀 Purpose

This project is designed for population analysis using genomic data. It preprocesses VCF files and applies K-means clustering to discover sub-populations based on genetic similarities.

## About the Dataset
We are given ‘.tsv’ (Tab Separated Values) files of the Genome dataset and each file has thousands of columns and millions of rows.

## Implementation

- Decompress the zipped file to VCF format
- Read the file
- Removed the lines starting with ’##’ (contains Meta-information)
- Calculated the number of features in the dataset available
- Applied Chromosome number filter : an identifier from the reference genome
- Applied REF filter : Each base must be one of A,C,G,T (case insensitive).
- ALT filter : Comma separated list of alternate non-reference alleles.
- ’Filter’ filter : PASS if this position has passed all filters, i.e., a call is made at this position. Otherwise, if the site has not passed all filters


## Software to be used

**Client:** React, Redux, TailwindCSS

**Server:** Node, Express

**C compiler:** GCC 

**GUI program:** GNUplot (if using the visualization component)

**Libraries/Tools:** stdio.h, string.h, stdlib.h, math.h, HTSlib
## Files

Code Files
- vcf_read.c: VCF file parsing, data filtering, and transformation. 
- kmeans.c: Core K-means clustering algorithm implementation. 
- kmeans.h: Header file declaring the K-means function. 
- main.c (or pp.c): Main project driver, handles input, function calls, and output.
- gnu.c: GNUplot interaction for visualization (optional).

Data Files: 
- gid.txt: Genome ID to VCF column mapping. 
- smat.dat: Scoring matrix for data transformation. 
- sample_big.vcf: An example VCF file.

Output Files: 
- data.txt: Transformed data ready for clustering. 
- final.txt (or file1.txt): Centroid coordinates (potentially across iterations). 
- cluster.txt: Cluster assignments for data points. 
- result.gif: Animation of clustering process (if using GNUplot).


## Compilation Instructions

- Ensure you have a C compiler (e.g., GCC) installed.
- Navigate to the project directory in your terminal.
- Compile the code: gcc -o project_name vcf_read.c kmeans.c main.c -lm # '-lm' for math functions (Replace project_name with your desired executable name.)


## Usage

General Commandline Arguments

```bash
 ./project_name <chromosome_of_interest> <path_to_vcf_file> <min_mutation_rate> <max_mutation_rate> <path_to_gid_file> <path_to_scoring_matrix> <num_clusters> <max_iterations>
 ```

Example
```bash
./project_name 3 ../data/sample_big.vcf 10.0 20.0 ../data/gid.txt ../data/smat.dat 5 100
```

## Visualization:- 
1. Ensure you have GNUplot installed. 
2. After running the program, result.gif should be generated.
3. You can view this animation using image viewing software or a web browser.

## Notes:- 
1. Adjust file paths and parameters as needed for your specific project setup. 
2. Consider providing more details about input file formats (VCF, gid, scoring matrix). 
3. You may want to include an example of interpreting the clustering results.

## Contact: 
Include your name and contact information if you're open to questions or feedback.
