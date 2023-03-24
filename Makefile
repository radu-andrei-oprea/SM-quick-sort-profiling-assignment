#builds
TARGETS= serial mpi omp posix hybrid
N= 6

build: $(TARGETS)

serial:
	gcc 1/q_serial.c -o 1/q_serial
mpi:
	mpicc 1/q_mpi.c -o 1/q_mpi
omp:
	gcc -fopenmp 1/q_omp.c -o 1/q_omp
posix:
	gcc -pthread 2/q_posix.c -o 2/q_posix
hybrid:
	mpicc -fopenmp 2/q_ompi.c -o 2/q_ompi

# run executables
run_serial:
	cd 1 && ./q_serial > ../output_serial
run_mpi:
	cd 1 && mpirun -np $(N) ./q_mpi < ../input > ../output_mpi
run_omp:
	cd 1 && ./q_omp > ../output_omp
run_posix:
	cd 2 && ./q_posix > ../output_posix
run_hybrid:
	cd 2 && mpirun -np $(N) ./q_ompi < ../input > ../output_hybrid 

#clean executables
clean:
	rm 1/q_serial 1/q_mpi 1/q_omp 2/q_posix 2/q_ompi

