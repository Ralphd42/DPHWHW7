#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "mpi.h"

// constants
#define MASTER 0
const char * piString ="3.14159265359";


// prototypes
long pifunct(  long numTries);
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
    if(rc!=MPI_SUCESS)
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
    MPI_Bcast(totalNumTosses_p, 1, MPI_LONG, MASTER, MPI_COMM_WORLD);

    int triesPerRank =num_attempts/num_proc;



    MPI_Barrier(MPI_COMM_WORLD);
    
    hitsPerRank = pifunct(triesPerRank);
    MPI_Reduce(&hitsPerRank,&totalHits,1,MPI_SUM,MASTER,MPI_COMM_WORLD);
    
    
    MPI_Finalize(); 
    return 1;
}

long pifunct(  long numTries)
{
    time_t t;
    long numhits=0;
    srand((unsigned) time(&t));        
    for (long cntr=0; cntr<tries; ++cntr )
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


