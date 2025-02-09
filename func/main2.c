#include <stdio.h>

struct pipeline {
    int (*first_operation)(int);
    int (*second_operation)(int);
};


int double_it(int x)
{
    return x * 2;
}

int add_ten(int x)
{
    return x + 10;
}

int process_number(struct pipeline p, int x)
{
    int temp = p.first_operation(x);
    return p.second_operation(temp);
}

int main()
{
    struct pipeline pl = {
        .first_operation = double_it,
        .second_operation = add_ten

    };

    int numbers[] = {1, 2, 3, 4, 5, 6};
    for (size_t i = 0; i < 6; i++)
    {
        printf("%d, ", process_number(pl, numbers[i]));
    }
    printf("\n");   

    return 0;
    
}