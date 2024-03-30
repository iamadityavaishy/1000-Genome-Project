#!/bin/bash

	clear

	# directories required in main folder are data and src
	# data    : vcf and scoring matrix
	# src     : submitted zip file

	# directories required in the zip files are src and include
       	# include : header files
	# src     : C codes

	# script file
	# file    : evaluate.sh

	# Note    : Library file is created by the script

	rm -rf sandbox
	mkdir sandbox
	cd sandbox

	echo "Group,Time,Output,Error"
	#for prj in `ls ../src | grep group_[0-9][0-9].zip`; do
	for prj in `ls ../src | grep _06 | grep group_[0-9][0-9].zip`; do
		dir=`echo $prj | sed 's/.zip$//'`

		# create and enter user dir
		mkdir $dir
		cd $dir
		if [ -s a.out ];then
			rm a.out
		fi

		cp -a ../../src/$prj .
		rm -rfv $dir
		unzip -oqq $prj > /dev/null
		rm -f $prj

		# enter project dir
		if [ -d $dir ]; then
			cd $dir

			if [ -s a.out ]; then
				rm -f a.out
			fi

			rm -rf lib bin
			mkdir lib bin

			gcc -c src/kmeans.c -o bin/kmeans.o
			ar rcs lib/libmean.a bin/kmeans.o

			gcc -O3 -Iinclude -Llib src/main.c -lm -lkmeans 2> /dev/null

			if [ -s a.out ]; then
				STARTTIME=$(date +%s)
				# ./a.out chr_num vcf_file min_mut max_mut gid_list score_mat num_clust max_iter threshold
				ret=`{ timeout 300 ./a.out 22 ../../../data/data_big.vcf 10.0 20.0 ../../../data/gid.txt ../../../data/smat.dat 6 100 0.0001 > out 2> err; } 2>&1`
				ENDTIME=$(date +%s)
				dtime=$(($ENDTIME - $STARTTIME))
			fi

			sleep 1
			if [ -s out ]; then
				out=`head -1 out`
				err=`head -1 err 2> /dev/null`
				echo "$dir,$dtime,$out,$err"
			else
				err=`head -1 err 2> /dev/null`
				echo "$dir,-1,,NO_OUT ($err)"
			fi

			cd ..
		else
			echo "$dir,-1,,NO_DIR"
		fi

		# exit user dir
		cd ..
	done

exit 0
