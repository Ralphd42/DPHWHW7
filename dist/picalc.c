#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "mpi.h"
#include "timing.h"
#include <omp.h>
#include<time.h>
// constants
#define MASTER 0
#define PI 3.14159265359
const char * piString ="3.14159265359";


// prototypes
int pifunct(  int numTries);
int ompPI(int numTries);
int main(int argc, char*argv[])
{
    timing_start() ;
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
        MPI_Abort(MPI_COMM_WORLD,rc);    
    }
    
    MPI_Comm_size(MPI_COMM_WORLD,&num_proc);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if(rank==MASTER)
    {
        if(argc<=1)
        {
            printf( "Please supply number of attempts");
            MPI_Abort(MPI_COMM_WORLD,rc);

        }else
        {
            num_attempts = atoi( argv[1]);
        }
        

    }
    MPI_Bcast(&num_attempts, 1, MPI_LONG, MASTER, MPI_COMM_WORLD);

    triesPerRank =num_attempts/num_proc;



    MPI_Barrier(MPI_COMM_WORLD);
    
    hitsPerRank =    ompPI(triesPerRank);  //pifunct(triesPerRank);
    MPI_Reduce(&hitsPerRank,&totalHits,1,MPI_INT,MPI_SUM,MASTER,MPI_COMM_WORLD);
    
    
    if(rank==MASTER)
    {
         printf("TotalHits= %d\n",totalHits);
        double mcPi=(double) totalHits/num_attempts*4;
        printf("TargetPI= %s\n",piString);
        printf("Differenece %f\n", fabs( mcPi - PI)  );
        printf("Tries= %d\npi estimate is %.15f \n",num_attempts,mcPi);
    }
    MPI_Finalize(); 
    timing_stop();
    print_timing();
    return 1;
}

int ompPI(int numTries)
{
    int slices = 4;
    int sliceCnt = numTries / slices;
    
    int numhits = 0;
    int i ;
#pragma omp parallel for shared(slices, sliceCnt) private(i) reduction(+:numhits)
    for (i= 0; i < slices; i++)
    {
        numhits += pifunct(sliceCnt); // maybee change to 
    }
    return numhits;





}


/*
    adding omp would be a prformance enhnacement here
*/
int pifunct(  int numTries)
{
     
    int numhits=0;
    time_t t;
    srand((unsigned) time(&t)); 
    int seed1 = rand();
    int seed2 = rand();
//rand_r(&seed2);
    int cntr;      
    int sumSq;
    int numSplits =8;
    int splitSize = numTries/numSplits;
    
    
    for (cntr=0; cntr<numTries; ++cntr )
    {
        double x = (double) rand_r(&seed1)/RAND_MAX;
        double y = (double) rand_r(&seed2)/RAND_MAX;
        //double x = (double) rand( )/RAND_MAX;
       // double y = (double) rand( )/RAND_MAX;
        
        
        //printf( "\n x = %f y= %f" ,x,y);
        sumSq = x*x +y*y;
        if( sumSq<1)
        {
            ++numhits;
        }
    }
    return numhits;
}

  


