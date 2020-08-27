#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <stdlib.h> 
#include <time.h>

void swap(int *xp, int *yp)  
{  
    int temp = *xp;  
    *xp = *yp;  
    *yp = temp;  
}  
  
void bubbleSort(int arr[], int n)  
{  
    int i, j;  
    for (i = 0; i < n-1; i++)      
      
    // Last i elements are already in place  
    for (j = 0; j < n-i-1; j++)  
        if (arr[j] > arr[j+1])  
            swap(&arr[j], &arr[j+1]);  
}

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv); 
    int size, rank;
    srand(time(NULL));
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    enum role_ranks { SENDER, RECEIVER }; 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int sendSize = 100;
    int chunkSize = 10;
    int recvBuffer[10];
    int bufferUnsorted[100]; 
    int bufferSorted[100];
 
    if(rank == 0){ 
	for(int i=0;i<100;i++)
		bufferUnsorted[i] = int(rand()%101) + 1;
    }
    MPI_Scatter(bufferUnsorted,chunkSize,MPI_INT,recvBuffer,chunkSize,MPI_INT,0,MPI_COMM_WORLD);
    if(rank != 0){
	bubbleSort(recvBuffer,10);
	printf("\n");
	for(int i=0;i<10; i ++)
		printf("%d ", recvBuffer[i]);
	printf("\n");
    }
	
    MPI_Finalize(); 
    return EXIT_SUCCESS;
}

