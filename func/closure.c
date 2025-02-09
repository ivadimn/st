#include <stdio.h>
#include <stdlib.h>



typedef struct closure_t closure_t;

struct closure_t {
    int captured;
    int (*func)(closure_t*, int);
};

int closure_func(closure_t *closure, int x)
{
    return x * closure->captured;
}

closure_t* make_closure(int initial_value)
{
    closure_t *closure = malloc(sizeof(closure_t));
    closure->captured = initial_value;
    closure->func = closure_func;
    return closure;
}


int main()
{
    closure_t* closure1 = make_closure(10);
    closure_t* closure2 = make_closure(20);
    
    printf("%d\n", closure1->func(closure1, 7));
    printf("%d\n", closure2->func(closure2, 8));

    free(closure1);
    free(closure2);
    return 0;
}