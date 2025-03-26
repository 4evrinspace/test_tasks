#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>




int main(int argc, char *argv[]) {

    static struct option long_options[] = {
        {"elbrus", required_argument, NULL, 'e'},
        {0, 0, 0, 0}
    };
    int mflag = 0, cflag = 0, sflag = 0, tflag = 0;
    char** elbrus_value = NULL;
    int number_elbrus = 0;
    int opt;
    while ((opt = getopt_long(argc, argv, "mcst", long_options, NULL)) != -1) {
        switch (opt) {
            case 'm':
                if (mflag) {
                    printf("Multiple -m options\n");
                    return 0;
                }
                mflag = 1;
                break;
            case 'c':
                if (cflag) {
                    printf("Multiple -c options\n");
                    return 0;
                }
                cflag = 1;
                break;
            case 's':
                if (sflag) {
                    printf("Multiple -s options\n");
                    return 0;
                }
                sflag = 1;
                break;
            case 't':
                if (tflag) {
                    printf("Multiple -t options\n");
                    return 0;
                }
                tflag = 1;
                break;
            case 'e':;
                if (strcmp(optarg, "1c+") != 0 && strcmp(optarg, "2c+") != 0 &&
                    strcmp(optarg, "2c3") != 0 && strcmp(optarg, "4c") != 0 &&
                    strcmp(optarg, "8c") != 0 && strcmp(optarg, "16c") != 0) {
                    printf("Invalid --elbrus value: %s\n", optarg);
                    return 0;
                }
                if (elbrus_value) {
                    number_elbrus++;
                    elbrus_value = realloc(elbrus_value, number_elbrus * sizeof(char*));
                    elbrus_value[number_elbrus - 1] = optarg;
                    return 0;
                } else {
                    elbrus_value = (char**)malloc(sizeof(char*));
                    elbrus_value[0] = optarg;
                }
                break;
            default:
                printf("Invalid option: %c\n", opt);
                return 0;
        }
    }

    printf("Options are correct: ");
    if (mflag) {
        printf("m,");
    }
    if (cflag) {
        printf("c,");
    }
    if (sflag) {
        printf("s,");
    }
    if (tflag) {
        printf("t");
    }
    if (elbrus_value) {
        for (int i = 0; i < number_elbrus; i++) {
            printf(",elbrus=%s", elbrus_value[i]);
        }
    }

    printf(",non-option arguments:");
    for (int i = optind; i < argc; i++) {
        printf("  %s\n", argv[i]);
    }

    return 0;
}