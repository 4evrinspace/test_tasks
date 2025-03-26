#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>


int i = 0, j = 0, k = 0;

void signal_handle(int nsig) {
    printf("\nCur indexes i=%d, j=%d, k=%d\n", i, j, k);
    (void)signal(SIGINT, SIG_DFL);
}

void sigaction_handle(int nsig, siginfo_t* siginfo, void* context) {
    printf("\nCur indexes i=%d, j=%d, k=%d\n", i, j, k);
    struct sigaction psa;
    psa.sa_handler = SIG_DFL;
    sigaction(SIGINT, &psa, NULL);
}

int main(int argc, char **argv) {
    int n = 1000;
    int** A = (int **)malloc(n * sizeof(int *));
    int **B = (int **)malloc(n * sizeof(int *));
    int **C = (int **)malloc(n * sizeof(int *));
    
    for (int i = 0; i < n; i++) {
        A[i] = (int *)malloc(n * sizeof(int));
        B[i] = (int *)malloc(n * sizeof(int));
        C[i] = (int *)malloc(n * sizeof(int));
    }
    

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 1024;
            B[i][j] = rand() % 1024;
            C[i][j] = 0;
        }
    }
    
    //signal(SIGINT, signal_handle);
    struct sigaction psa;
    psa.sa_sigaction = sigaction_handle;
    sigaction(SIGINT, &psa, NULL);
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
            sleep(1);
        }
    }
    

    for (int i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);
    
    return 0;
}