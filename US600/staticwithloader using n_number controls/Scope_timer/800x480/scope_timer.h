#ifndef SCOPE_TIMER_H
#define SCOPE_TIMER_H

#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

class scope_timer
{
private:
    scope_timer *ptr = nullptr;
    const char *m_tag;
    timeval start, end;
    scope_timer(const char *t):m_tag{t}
    {
        gettimeofday(&start, NULL);
        printf(/*stderr,*/ "scope_timer:%s\n", m_tag);
        fflush(stdout);
    }
public:
    scope_timer():
        scope_timer("_default")
    {
    }
    void Reset(const char *tag)
    {
        if(ptr) Dispose();

        ptr = new scope_timer(tag);
    }
    void Dispose()
    {
        if(ptr)
        {
            delete ptr;
            ptr = nullptr;
            m_tag = '\0';
        }
    }
    ~scope_timer()
    {
        gettimeofday(&end, NULL);
        printf(/*stderr, */"Total time was %ld uSec. %s\n", ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)), m_tag);
        fflush(stdout);
    }
};

#endif // SCOPE_TIMER_H
