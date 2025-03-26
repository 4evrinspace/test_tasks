#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

void print_info(const char *pathname, int link)
{
    struct stat sb;
    if (link == 0)
    {
        if (lstat(pathname, &sb) < 0)
        {
            printf("Can\'t get stats of %s\n", pathname);
            exit(-1);
        }
    }
    else
    {
        if (stat(pathname, &sb) < 0)
        {
            printf("Can\'t get stats of %s\n", pathname);
            exit(-1);
        }
        char buf[FILENAME_MAX] = {0};
        if (readlink(pathname, (char *)&buf, FILENAME_MAX - 1) < 0)
        {
            printf("Can\'t to read link %s\n", pathname);
            exit(-1);
        }
        printf("%s\n", buf);
        return;
    }
    switch (sb.st_mode & S_IFMT)
    {
    case S_IFBLK:
        printf("b");
        break;
    case S_IFCHR:
        printf("c");
        break;
    case S_IFDIR:
        printf("d");
        break;
    case S_IFIFO:
        printf("f");
        break;
    case S_IFLNK:
        printf("l");
        break;
    case S_IFREG:
        printf("-");
        break;
    case S_IFSOCK:
        printf("s");
        break;
    default:
        printf("?");
        break;
    }
    if (sb.st_mode & S_IRUSR)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if (sb.st_mode & S_IWUSR)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }

    if (sb.st_mode & S_IXUSR)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }

    if (sb.st_mode & S_IRGRP)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }

    if (sb.st_mode & S_IWGRP)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }

    if (sb.st_mode & S_IXGRP)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }

    if (sb.st_mode & S_IROTH)
    {
        printf("r");
    }
    else
    {
        printf("-");
    }
    if (sb.st_mode & S_IWOTH)
    {
        printf("w");
    }
    else
    {
        printf("-");
    }
    if (sb.st_mode & S_IXOTH)
    {
        printf("x");
    }
    else
    {
        printf("-");
    }
    printf(" %s ", pathname);
    if ((sb.st_mode & S_IFMT) == S_IFLNK)
    {
        printf("is symbol link to: ");
        print_info(pathname, 1);
    }
    printf("\nAtime: %sMtime: %sCtime: %s", asctime(gmtime(&sb.st_atime)), asctime(gmtime(&sb.st_mtime)),
           asctime(gmtime(&sb.st_ctime)));
    printf("\n");
    return;
}

int main(int argc, char **argv)
{
    char dir_name[4096] = "./";
    if (argc > 1)
    {
        strncpy(dir_name, argv[1], 4095);
    }
    printf("Directory %s has following files:\n", dir_name);
    DIR *directory;
    if ((directory = opendir(dir_name)) == NULL)
    {
        printf("Can\'t open directory %s", dir_name);
        exit(-1);
    }

    struct dirent *entry;
    while ((entry = readdir(directory)))
    {
        char file[FILENAME_MAX] = {0};
        strncat(file, dir_name, sizeof(file) - strlen(dir_name) - 1);
        file[FILENAME_MAX - 1] = 0;
        strncat(file, "/", sizeof(file) - strlen("/") - 1);
        file[FILENAME_MAX - 1] = 0;
        strncat(file, entry->d_name, sizeof(file) - strlen(entry->d_name) - 1);
        file[FILENAME_MAX - 1] = 0;
        print_info(file, 0);
    }
    closedir(directory);
    return 0;
}