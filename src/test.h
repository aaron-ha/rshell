#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

class Test{
    private:
        struct stat sb; 
    public: 
        runTest(const char*, struct stat);
        
}