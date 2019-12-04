#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "timing.h"


int main(int argc, char*argv[])
{
    timing_start();
    long long cntr=0;
    long long  tries =__INT_MAX__;
    tries= tries * 5;
    time_t t;
    srand((unsigned) time(&t));
    double x;
    double y;
    double sumSq;
    double mcPi;
    long long numhits =0;
    char* piString ="3.14159265359";
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
    timing_stop();
    printf("TargetPI= %s\n",piString);
    printf("Tries= %lld\npi is %.15f \n",tries,mcPi);
    print_timing();
    return 1;
}