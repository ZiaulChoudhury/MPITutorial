/**
 * @author RookieHPC
 * @brief Original source code at https://www.rookiehpc.com/mpi/docs/mpi_comm_create.php
 **/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 
/**
 * @brief Illustrates how to create a communicator.
 * @details This code extracts the group of processes in the default
 * communicator, then it keeps only the first 2 processes and creates a group
 * containing only these two. Finally, it creates a communicator based on that
 * group of 2, and proceeds to two broadcasts: one in the global communicator,
 * one in the communicator just created.
 * This application is meant to be run with at least 3 processes.
 **/
int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
 
    // Check that the application is run with at least 3 processes.
    int size,rank, rank2; 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank2);
    MPI_Group world_group;
    MPI_Comm_group(MPI_COMM_WORLD, &world_group);
 
    // Keep only the processes 0 and 1 in the new group.
    int ranks[2] = {0, 1};
    MPI_Group new_group;
    MPI_Group_incl(world_group, 2, ranks, &new_group); 
    MPI_Comm new_communicator;
    MPI_Comm_create(MPI_COMM_WORLD, new_group, &new_communicator);
	
    if(rank2 == 0 || rank2 == 1){
        
	MPI_Comm_set_name(new_communicator,"Shire"); 
	int  comm_size;
        char name[MPI_MAX_OBJECT_NAME];
        int  name_length;
		
	MPI_Comm comm = new_communicator;
        MPI_Comm_size(comm, &comm_size);
        MPI_Comm_get_name(comm, name, &name_length);
        MPI_Comm_rank(comm, &rank);
        MPI_Comm_size(comm, &size);
        printf("I am %d of %d in belonging to world %s  \n", rank,size,name);
    }
    else{
	MPI_Comm_set_name(MPI_COMM_WORLD,"Mordor");
        int  comm_size;
        char name[MPI_MAX_OBJECT_NAME];
        int  name_length;

        MPI_Comm comm = MPI_COMM_WORLD;
        MPI_Comm_size(comm, &comm_size);
        MPI_Comm_get_name(comm, name, &name_length);
        MPI_Comm_rank(comm, &rank);
        MPI_Comm_size(comm, &size);
        printf("I am %d of %d in belonging to world %s  \n", rank,size,name);
    }
    MPI_Finalize();
 
    return EXIT_SUCCESS;
}

