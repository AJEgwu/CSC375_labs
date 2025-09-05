#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    struct rlimit rlim;

    getrlimit(RLIMIT_STACK, &rlim);
    printf("stack size: %ld bytes\n", rlim.rlim_cur);

    getrlimit(RLIMIT_NPROC, &rlim);
    printf("process limit: %ld\n", rlim.rlim_cur);

    getrlimit(RLIMIT_NOFILE, &rlim);
    printf("max file descriptors: %ld\n", rlim.rlim_cur);

    return 0;
}
