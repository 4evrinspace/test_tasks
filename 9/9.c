#include <stdio.h>
#include <stdlib.h>

//Тут стоит сделать оговорку
//Я понимаю в качестве задачи - найти максимальную восзрастающую цепочку чисел в данном массиве
//Так как все писалось на С, не буду далеко отходить
// Буду считать для усложнения, что в начале не даются кол-во чисел в массиве, поэтому делаем вектор свой 

int main()
{
    int capacity = 10;
    int size = 0;
    int *arr = (int *)malloc(capacity * sizeof(int));
    while (scanf("%d", &arr[size]) == 1)
    {
        size++;
        if (size == capacity)
        {
            capacity *= 2;
            arr = (int *)realloc(arr, capacity * sizeof(int));
        }
    }
    if (size == 0)
    {
        printf("No numbers\n");
        return 0;
    }
    int left_ans = 0, right_ans = 0;
    int left = 0, right = 0;
    long long sum_ans = arr[0], sum = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > arr[i - 1])
        {
            right++;
            sum += arr[i];
        }
        else
        {
            if (right_ans - left_ans < right - left)
            {
                left_ans = left;
                right_ans = right;
                sum_ans = sum;
            }
            left = i;
            right = i;
            sum_ans = arr[i];
        }
    }
    

    free(arr);
    return 0;
}