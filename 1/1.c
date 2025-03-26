#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SMALL_ARRAY_LEN 200
int* arr;

int* tmp;
// для удобства при передачи параметров
typedef struct
{
    int left;
    int right;
} thread_args;

void merge(int left, int right)
{
    int mid = (left + 0ll + right) / 2;
    int i = left;
    int j = mid + 1;
    
    int index = 0;
    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
        {
            tmp[index++] = arr[i++];
        }
        else
        {
            tmp[index++] = arr[j++];
        }
    }
    
    while (i <= mid)
    {
        tmp[index++] = arr[i++];
    }

    while (j <= right)
    {
        tmp[index++] = arr[j++];
    }

    for (int t = 0; t < index; t++)
    {
        arr[t + left] = tmp[t];
    }
}

void merge_sort(int left, int right)
{
    if (left >= right)
        return;
    int mid = (left + 0ll + right) / 2;
    merge_sort(left, mid);
    merge_sort(mid + 1, right);
    merge(left, right);
}

void *sort(void *args)
{
    thread_args *arg = (thread_args *)args;
    if (arg->left >= arg->right)
    {
        return NULL;
    }
    //Однако, если размер массив очень маленький, то время создания нити исолнения будет значительно больше чем сортировка олним потоком
    if (arg->right - arg->left < SMALL_ARRAY_LEN)
    {
        merge_sort(arg->left, arg->right);
        return NULL;
    }

    // На всякий случай сконвертируем в лонги
    int mid = (arg->left + 0ll + arg->right) / 2;

    thread_args left_args = {arg->left, mid};
    thread_args right_args = {mid + 1, arg->right};

    pthread_t left_thread, right_thread;
    int result;
    result = pthread_create(&left_thread, NULL, sort, &left_args);
    if (result != 0)
    {
        printf("Error on thread create, return value = %d\n", result);
        exit(-1);
    }

    result = pthread_create(&right_thread, NULL, sort, &right_args);
    if (result != 0)
    {
        printf("Error on thread create, return value = %d\n", result);
        exit(-1);
    }

    result = pthread_join(left_thread, NULL);
    if (result != 0) {
        printf ("Error on join, return value = %d\n", result);
        exit(-1);
      }
    
    result = pthread_join(right_thread, NULL);
    if (result != 0) {
        printf ("Error on join , return value = %d\n", result);
        exit(-1);
      }
    

    merge(arg->left, arg->right);

    return NULL;
}

int main()
{
    tmp = (int *)malloc((SMALL_ARRAY_LEN + 1) * sizeof(int));
    int n;
    scanf("%d", &n);
    arr = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    thread_args args = {0, n - 1};

    pthread_t sort_thread;
    int result = pthread_create(&sort_thread, NULL, sort, &args);
    if (result != 0)
    {
        printf("Can\'t create thread, error = %d\n", result);
        exit(-1);
    }

    result = pthread_join(sort_thread, (void **)NULL);
    if (result != 0) {
        printf ("Error on join create, return value = %d\n", result);
        exit(-1);
      }
    

    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    free(arr);
    free(tmp);
    return 0;
}