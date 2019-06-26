#ifndef MEMSELF_H
#define MEMSELF_H
#include <cstring>

class memself
{
    int parseLine(char *line)
    {
        int i = strlen(line);
        const char *p = line;
        while (*p < '0' || *p > '9')
            p++;
        line[i - 3] = '\0';
        i = atoi(p);
        return i;
    }

public:
    memself() = default;

    typedef struct 
    {
        uint32_t virtualMem;
        uint32_t physicalMem;
    }processMem_t;

    processMem_t GetProcessMemory()
    {
        FILE *file = fopen("/proc/self/status", "r");
        char line[128];
        processMem_t processMem;

        bool sz, rss;
        while (fgets(line, 128, file) != NULL)
        {
            printf(line);
            if (!sz && (strncmp(line, "VmSize:", 7) == 0))
            {
                processMem.virtualMem = parseLine(line);
                sz = true;
            }

            if (!rss && (strncmp(line, "VmRSS:", 6) == 0))
            {
                processMem.physicalMem = parseLine(line);
                rss = true;
            }
            if(sz && rss) break;
        }
        fclose(file);
        return processMem;
    }

    ~memself() = default;
};
#endif //MEMSELF_H