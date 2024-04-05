#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>


int main() {
    void *library;
    int (*add)(int, int);
    int (*subtract)(int, int);
    int (*multiply)(int, int);
    int (*divide)(int, int);

    library = dlopen("./function.so", RTLD_LAZY);

    if (!library) {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    add = dlsym(library, "add");
    subtract = dlsym(library, "subtract");
    multiply = dlsym(library, "multiply");
    divide = dlsym(library, "divide");

    int a, b;

    printf("Enter two numbers: ");
    scanf("%d %d", &a, &b);

    printf("Sum: %d\n", add(a, b));
    printf("Sub: %d\n", subtract(a, b));
    printf("Mul: %d\n", multiply(a, b));
    printf("Div: %d\n", divide(a, b));

    dlclose(library);

    return 0;
}

