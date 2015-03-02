#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct Node {
    int value;
    struct Node *next;
};

struct Stack {
    struct Node *head;
    int size;
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
    stack->head = NULL;
    stack->size = 0;
    
    return stack;
}

void push(struct Stack *stack, int value)
{
    struct Node *old_head = stack->head;
    
    stack->head = malloc(sizeof(struct Node));
    stack->head->value = value;
    stack->head->next = old_head;
    stack->size++;
}

int pop(struct Stack *stack) 
{
    if (stack->size == 0) {
        free_stack(stack);
        
        die("Stack is empty!");
    } else {
        struct Node *new_head = stack->head->next;
        int value = stack->head->value;
        
        free(stack->head);
        
        stack->head = new_head;
        stack->size--;
        
        return value;
    }
    
    return 0;
}

void free_stack(struct Stack *stack)
{
    if (stack) {
        struct Node *head = stack->head;
        
        if (head) {
            struct Node *next = head->next;
            
            while (next) {
                free(head);
                
                head = next;
                next = next->next;
            }
            
            free(head);
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