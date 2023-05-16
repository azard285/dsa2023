#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    double res = (double)t.tv_sec + (double)t.tv_usec * 1E-6;
    return res;
}
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
int maxElement(int *arr, int size)
{
    int res = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] > res)
        {
            res = arr[i];
        }
    }
    return res;
}

void countingSort(int *arr, int size, int place)
{
    int newArr[size];
    int count[10] = {0};
    for (int i = 0; i < size; i++)
    {
        count[(arr[i] / place) % 10]++;
    }
    for (int i = 1; i < 10; i++) //{1,0,1} => {1,1,2}
    {
        count[i] += count[i - 1];
    }
    for (int i = size - 1; i >= 0; i--)
    {
        newArr[count[(arr[i] / place) % 10] - 1] = arr[i];
        count[(arr[i] / place) % 10]--;
    }
    for (int i = 0; i < size; i++)
    {
        arr[i] = newArr[i];
    }
}

void radixSort(int *arr, int size)
{
    int max = maxElement(arr, size);
    for (int i = 1; max / i > 0; i *= 10)
    {
        countingSort(arr, size, i);
    }
}
void oddEvenSort(int *arr, int size)
{
    int sorted = 0;
    do
    {
        sorted = 0;
        for (int i = 1; i < size - 1; i += 2)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(&arr[i], &arr[i + 1]);
                sorted = 1;
            }
        }
        for (int i = 0; i < size - 1; i += 2)
        {
            if (arr[i] > arr[i + 1])
            {
                swap(&arr[i], &arr[i + 1]);
                sorted = 1;
            }
        }

    } while (sorted);
}
void merge(int *arr, int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[low + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int l = 0;
    int r = 0;
    int i = low;
    while ((l < n1) && (r < n2))
    {
        if (L[l] <= R[r])
        {
            arr[i] = L[l];
            l++;
        }
        else
        {
            arr[i] = R[r];
            r++;
        }
        i++;
    }
    while (l < n1)
    {
        arr[i] = L[l];
        l++;
        i++;
    }
    while (r < n2)
    {
        arr[i] = R[r];
        r++;
        i++;
    }
}
void mergeSort(int *arr, int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}
int main()
{
    srand(time(NULL));

    int *arr1, *arr2, *arr3;
    double toddeven, tmerge, tradix;
    for (int size = 100000; size <= 1000000; size += 100000)
    {
        arr1 = (int *)malloc(sizeof(int) * size);
        assert((arr1 != NULL) && "Can't allocate memory!");

        arr2 = (int *)malloc(sizeof(int) * size);
        assert((arr2 != NULL) && "Can't allocate memory!");

        arr3 = (int *)malloc(sizeof(int) * size);
        assert((arr3 != NULL) && "Can't allocate memory!");

        for (int i = 0; i < size; ++i)
        {
            arr1[i] = arr2[i] = arr3[i] = rand() % 10000;
        }

        tradix = wtime();
        radixSort(arr1, size);
        tradix = wtime() - tradix;

        toddeven = wtime();
        oddEvenSort(arr2, size);
        toddeven = wtime() - toddeven;

        tmerge = wtime();
        mergeSort(arr3, 0, size - 1);
        tmerge = wtime() - tmerge;

        for (int i = 0; i < size - 1; ++i)
        {
            assert((arr1[i] <= arr1[i + 1]) && "Array radix not sorted");
        }
        for (int i = 0; i < size - 1; ++i)
        {
            assert((arr2[i] <= arr2[i + 1]) && "Array oddeven not sorted");
        }
        for (int i = 0; i < size - 1; ++i)
        {
            assert((arr3[i] <= arr3[i + 1]) && "Array merge not sorted");
        }
        printf("%d\t%.6lf\t%.6lf\t%.6lf\n", size, tradix, toddeven, tmerge);
        free(arr1);
        free(arr2);
        free(arr3);
    }
    return 0;
}