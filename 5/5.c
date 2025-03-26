#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main()
{
    char pathname[] = "test";

    open(pathname, O_RDONLY);
    printf("errno = %d\n", errno);
    printf("strerror = %s\n", strerror(errno));/*
    Гугл пишет что depricated
        printf("sys_errlist: %s\n", _sys_errlist[errno]);

        */
    perror("perror ");

    return 0;
}
