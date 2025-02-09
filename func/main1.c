#include <stdio.h>


int double_it(int x)
{
    return x * 2;
}

int add_ten(int x)
{
    return x + 10;
}

void transform_arr(int *arr, int size, int (*f)(int))
{
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = f(arr[i]);
        printf("%d, ", arr[i]);
    }
    printf("\n");
    
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6};

    transform_arr(arr, 6, double_it);

    transform_arr(arr, 6, add_ten);

    return 0;
}


