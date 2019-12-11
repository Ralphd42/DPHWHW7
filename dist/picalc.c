#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "timing.h"
#include "mpi.h"

int main(int argc, char*argv[])
{

    int rc;
    if(rc!=MPI_SUCESS)
    {

        printf("Failed to start MPI");
        MPI_ABORT(MPI_COMM_WORLD,rc);    
    }
    
    timing_start();
    
    
    char* piString ="3.14159265359";
    
    timing_stop();
    printf("TargetPI= %s\n",piString);
    printf("Tries= %lld\npi is %.15f \n",tries,mcPi);
    print_timing();
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
}


