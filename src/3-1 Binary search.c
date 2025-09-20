#include <stdio.h>

#define ARR_LEN 1000
#define STEP    4

void fillarr(int arr[], int start, int step, int len)
{
    int i = 0;
    int j = 0;

    for (i=start; j < len; ++i)
        if (i%step == 0)
            arr[j++] = i;
}

/* Number to look for, arr to look in, length of the array */
/* Returns the index position of the number in the array */
int binsearch(int n, int arr[], int len)
{
    int low = 0;        // Index first element
    int mid;
    int high = len-1;   // Index last element
    int iter = 0;       // Amount of iterations it took

    while (low <= high && arr[mid] != n){
        mid = (low+high)/2;

        if (arr[mid] > n)
        // Mid-1 because you already know mid isn't it, the same below...
            high = mid-1;
        else
            low = mid+1;
        ++iter;
    }

    if (arr[mid] == n)
        return mid;
    else
        return -1;
}

int main()
{
    int arr[ARR_LEN];
    int i;
    fillarr(arr, 4, 4, ARR_LEN);
    
    // for (i=0; i < ARR_LEN; ++i)
    //     printf("%4d%c", arr[i], (i%10==9) ? '\n': ' ');

    int x = binsearch(124, arr, ARR_LEN);
    printf("%d\n", x);


    return 0;
}