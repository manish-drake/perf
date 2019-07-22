#ifndef SCOPE_MEMSELF_H
#define SCOPE_MEMSELF_H
#include "memself.h"
using std::string;
class scope_memself
{
    memself::processMem_t procMem;
    memself m_memself;
    scope_memself *ptr = nullptr;
    const char *m_tag = '\0';
    scope_memself(const char *t):m_tag{t}
    {
        procMem = m_memself.GetProcessMemory();
        fprintf(stderr, "scope_memself:%s\n", m_tag);
//        fflush(stdout);
    }
  public:
    scope_memself():
        scope_memself("_default"){
    }

    void Reset(const char *tag)
    {
        if(ptr) Dispose();

        ptr = new scope_memself(tag);
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
    ~scope_memself(){
        auto mem = m_memself.GetProcessMemory();
        fprintf(stderr, "sz:%i, rss:%i\n", mem.virtualMem - procMem.virtualMem, mem.physicalMem - procMem.physicalMem);
//        fflush(stdout);
    }
};
#endif //SCOPE_MEMSELF_H
