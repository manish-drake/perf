#include <iostream>
#include "test.h"

using namespace std;
#define UNUSED(x) (void)(x)
int main(int argc, char* argv[]){
    UNUSED(argc);
    UNUSED(argv);
    
    Test test;
    
    test.Setup();

    test.Run();

    test.Teardown();

    cin.ignore();
    return 0;
}
