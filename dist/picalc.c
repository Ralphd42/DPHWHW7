#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "mpi.h"

// constants
#define MASTER 0
const char * piString ="3.14159265359";


// prototypes
int pifunct(  int numTries);
int main(int argc, char*argv[])
{
    
    int rc;
    int num_proc;
    int rank;
    int num_attempts;  // command line argument  total num of attempts to be spread between Items
    int triesPerRank;   // each proc will have a number of tries
    int hitsPerRank;    // each proc will have a number of hits
    int totalHits;
    rc =MPI_Init(&argc,&argv);
    if(rc!=MPI_SUCCESS)
    {
        printf("Failed to start MPI");
        MPI_ABORT(MPI_COMM_WORLD,rc);    
    }
    
    MPI_Comm_size(MPI_COMM_WORLD,&num_proc);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank==MASTER)
    {
        if(argc<=1)
        {
            printf( "Please supply number of attempts");
            MPI_ABORT(MPI_COMM_WORLD,rc);

        }else
        {
            num_attempts = atoi( argv[1]);
        }
        

    }
    MPI_Bcast(&num_attempts, 1, MPI_LONG, MASTER, MPI_COMM_WORLD);

    triesPerRank =num_attempts/num_proc;



    MPI_Barrier(MPI_COMM_WORLD);
    
    hitsPerRank = pifunct(triesPerRank);
    MPI_Reduce(&hitsPerRank,&totalHits,1,MPI_INT,MPI_SUM,MASTER,MPI_COMM_WORLD);
    
    double mcPi=(double) totalHits/num_attempts*4;
    /*
         start = MPI_Wtime();
   processNumberInCircle = Toss(numProcessTosses, myRank);
   finish = MPI_Wtime();
    MPI_Reduce(&loc_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD); 
    
    */

printf("TargetPI= %s\n",piString);
    printf("Tries= %d\npi is %.15f \n",num_attempts,mcPi);
    MPI_Finalize(); 
    return 1;
}

int pifunct(  int numTries)
{
     
    int numhits=0;
    time_t t;
    srand((unsigned) time(&t));  
    int cntr;      
    int sumSq;
    for (cntr=0; cntr<numTries; ++cntr )
    {
        double x = (double) rand()/RAND_MAX;
        double y = (double) rand()/RAND_MAX;
        sumSq = x*x +y*y;
        if( sumSq<=1)
        {
            ++numhits;
        }
    }
    return numhits;
}


