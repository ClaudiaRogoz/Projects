#! /bin/bash
NR=$1
FISIN=$2
FISOUT1=$3
FISOUT2=$4
FISOUT3=$5
SCHEDULE=$6
NTH=$7
N=$#

if [ $N -eq 7 ] ; then 
	export OMP_SCHEDULE=$6
	export OMP_NUM_THREADS=$7
	time ./optim $NR $FISIN $FISOUT3
	time ./serial $NR $FISIN $FISOUT1
	time ./paralel $NR $FISIN $FISOUT2
else
	echo "proper use is: ./script nrani fisintrat fisiesire1 fisiersire2 fisieriesire3 schedule numthreads"
fi

