#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct Stack {
    int *nodes;
    int size;
    int capacity;
};

void free_stack(struct Stack *stack);

void die(const char *message)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    
    exit(1);
}

struct Stack *new()
{
    struct Stack *stack = malloc(sizeof(struct Stack));
    
    stack->nodes = malloc(sizeof(int));
    stack->size = 0;
    stack->capacity = 1;
    
    return stack;
}

void resize(struct Stack *stack, int max)
{
    int i = 0;
    int *nodes = malloc(sizeof(int) * max);

    for (i = 0; i < stack->size; i++) {
        nodes[i] = stack->nodes[i];
    }
    
    free(stack->nodes);
    
    stack->nodes = nodes;
    stack->capacity = max;
}

void push(struct Stack *stack, int value)
{
    if (stack->size == stack->capacity) {
        resize(stack, stack->capacity * 2);
    }
    
    stack->nodes[stack->size++] = value;
}

int pop(struct Stack *stack) 
{
    if (stack->size == 0) {
        free_stack(stack);
        
        die("Stack is empty!");
    } else {
        int value = stack->nodes[--stack->size];
        
        if (stack->size > 0 && stack->size == stack->capacity / 4) {
            resize(stack, stack->capacity / 2);
        }
        
        return value;
    }
    
    return 0;
}

void free_stack(struct Stack *stack)
{
    if (stack) {
        if (stack->nodes) {
            free(stack->nodes);
        }
        
        free(stack);
    }
}

int main(int argc, char *argv[])
{
    struct Stack *stack = new();

    int i = 0;
    
    for (i = 0; i < 10; i++) {
        push(stack, i);
    }
    
    for (i = 0; i < 10; i++) {
        printf("%d\n", pop(stack));
    }

    free_stack(stack);
    
    return 0;
}