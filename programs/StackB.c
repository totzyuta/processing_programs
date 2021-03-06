/*
 * 春課題 I' : スタックアドレス参照版
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACKMAX 50
#define STACK_NAME_MAX 16

typedef struct stack {
  int size;
  char name[STACK_NAME_MAX];
  int *pointer;
  int *limit;
  int data[1];
} Stack;

Stack *
newStack(char *name, int size) {
  Stack *stack = NULL;

  if (size > 0) {
    stack = (Stack *) malloc(sizeof(Stack) + 
                             sizeof(int) * size);
    if (stack != NULL) {
      stack->size = size;
      strncpy(stack->name, name, STACK_NAME_MAX);
      stack->pointer = &stack->data[0];
      stack->limit = stack->data + sizeof(int) * size;
    }
  }
  return stack;
} /* newStack */

void
push(Stack *stack, int value) {
  if (stack->pointer < stack->limit) {  // (3)
    *stack->pointer = value;
    stack->pointer++;
  } else {
    printf("%s: stack overflow.\n", stack->name);
  }
} /* push */

int
pop(Stack *stack) {
  if (stack->pointer > &stack->data[0]) {  // (4)
    return *(--stack->pointer); // (5)
  } else {
    printf("%s: stack underflow.\n", stack->name);
    exit(1);
  }
} /* pop */

void
printStack(Stack *stack) {
  int *p;

  printf("%15s:", stack->name);
  for (p = stack->data; 
       p < stack->limit && p < stack->pointer; p++) {
    printf(" %d", *p);
  }
  printf("\n");
} /* printStack */
    
int
main(int argc, char *argv[]) {
  int i;
  Stack *stack1 = newStack("Stack1", STACKMAX);
  Stack *stack2 = newStack("Stack2", STACKMAX);

  push(stack1, 1);
  push(stack2, 2);

  push(stack1, 3);
  push(stack2, 4);

  push(stack1, 5);

  printStack(stack1);
  printStack(stack2);

  for (i = 0; i < 3; i++) 
    printf("From %s: %d\n", stack1->name, pop(stack1));

  for (i = 0; i < 3; i++) 
    printf("From %s: %d\n", stack2->name, pop(stack2));

} /* main */
