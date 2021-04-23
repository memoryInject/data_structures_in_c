#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"


int main(int argc, char* argv[])
{
	struct Stack* stack = stackInit();
	stackPush(stack, 5);
	printf("Stack Head: %d\n", stack->head->data);
	printf("Stack is empty: %s\n", stackIsEmpty(stack)==0 ? "false": "true");
	printf("Stack size: %d\n", stackSize(stack));

	for(int i = 0; i < 10; i++){
		stackPush(stack, i);
	}
	printf("Stack Head: %d\n", stack->head->data);
	printf("Stack Pop: %d\n", stackPop(stack));
	printf("Stack size: %d\n", stackSize(stack));
	printf("Stack Head: %d\n", stack->head->data);
	printf("Stack Stack Peek: %d\n", stackPeek(stack));
	printf("Stack Head->next: %d\n", stack->head->next->data);

	printf("Stack Print: \n");
	stackPrint(stack);
	
	// Clear stack and deallocate memory
	stackClear(stack);

	return 0;
}
