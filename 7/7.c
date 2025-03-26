#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

void copy_file(int fd, int out_fd)
{
    char buf[4096];
    int res = 0;
    while (1)
    {
        res = read(fd, buf, 4096);
        if (res < 0)
        {
            printf("Can\'t read file\n");
            exit(-1);
        }
        if (res == 0)
        {
            break;
        }
        if (res < 4096)
        {
            
            res = write(out_fd, buf, res);
            if (res < 0)
            {
                printf("Can\'t write all string\n");
                exit(-1);
            }
            break;
        }



        res = write(out_fd, buf, 4096);
        if (res < 4096)
        {
            printf("Can\'t write all string\n");
            exit(-1);
        }
    }
}



int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Something is wrong with input\n");
        exit(-1);
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Can\'t open file \n");
        exit(1);
    }


    int result;
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("Can\'t fork process\n");
        exit(-1);
    }
    if (pid == 0)
    {
        char pathname[] = "child_text.txt";
        int out_fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (out_fd < 0)
        {
            perror("Can\'t open file \n");
            exit(1);
        }
        copy_file(fd, out_fd);
        if (close(out_fd) < 0)
        {
            perror("Can\'t close file\n");
            exit(1);
        }

    }
    else
    {
        char pathname[] = "parent_text.txt";
        int out_fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (out_fd < 0)
        {
            perror("Can\'t open file \n");
            exit(1);
        }
        copy_file(fd, out_fd);
        if (close(out_fd) < 0)
        {
            perror("Can\'t close file\n");
            exit(1);
        }
        wait(NULL);

        printf("Parent file : \n");
        out_fd = open(pathname, O_RDONLY);
        if (out_fd < 0)
        {
            perror("Can\'t open file \n");
            exit(1);
        }
        copy_file(out_fd, 1);
        if (close(out_fd) < 0)
        {
            perror("Can\'t close file\n");
            exit(1);
        }
        printf("\nChild file : \n");
        out_fd = open("child_text.txt", O_RDONLY);
        if (out_fd < 0)
        {
            perror("Can\'t open file \n");
            exit(1);
        }
        copy_file(out_fd, 1);
        if (close(out_fd) < 0)
        {
            perror("Can\'t close file\n");
            exit(1);
        }
        
    }
    return 0;
}