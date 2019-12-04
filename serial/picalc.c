#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "timing.h"


int main(int argc, char*argv[])
{
    timing_start();
    int cntr=0;
    int tries =__INT_MAX__;
    time_t t;
    srand((unsigned) time(&t));
    double x;
    double y;
    double sumSq;
    double mcPi;
    int numhits =0;
    for (; cntr<tries; ++cntr )
    {
        double x = (double)rand()/RAND_MAX;
        double y =(double)rand()/RAND_MAX;
        sumSq = x*x +y*y;
        if( sumSq<=1)
        {
            ++numhits;
        }
    }
    mcPi=(double) numhits/tries*4;
   printf("# of trials= %d , estimate of pi is %.80f \n",tries,mcPi);
    
    timing_stop();
    print_timing();
    return 1;
}