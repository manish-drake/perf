#ifndef SCOPE_TIMER
#define SCOPE_TIMER
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
class scope_timer
{
private:
    struct timeval start, end;

public:
    scope_timer(/* args */)
    {
        gettimeofday(&start, NULL);
    }

    ~scope_timer()
    {
        gettimeofday(&end, NULL);
        printf("Total time was %ld uSec.\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
    }
};

#endif //SCOPE_TIMER