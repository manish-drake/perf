#ifndef SCOPE_MEMSELF_H
#define SCOPE_MEMSELF_H
#include "memself.h"
using std::string;
class scope_memself
{
    memself::processMem_t procMem;
    memself m_memself;
  public:
    scope_memself(){
        procMem = m_memself.GetProcessMemory();
    }
    ~scope_memself(){
        auto mem = m_memself.GetProcessMemory();
        printf("sz:%i, rss:%i\n", mem.virtualMem - procMem.virtualMem, mem.physicalMem - procMem.physicalMem);
    }
};
#endif //SCOPE_MEMSELF_H