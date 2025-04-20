#include <stdio.h>


typedef int (*Operation) (int, int);


int sum(int x, int y)
{
    return x + y;
}

int mult(int x, int y)
{
    return x * y;
}

int apply_operation(int x, int y, Operation op)
{
    return op(x, y);
}

int main()
{
    int result1 = apply_operation(3, 5, sum);
    int result2 = apply_operation(3, 5, mult);

    printf("3 + 5 = %d\n", result1);
    printf("3 * 5 = %d\n", result2);

    return 0;
}