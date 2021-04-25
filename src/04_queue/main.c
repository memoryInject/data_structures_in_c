#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

// Test drive code
int main(int argc, char* argv[])
{
	struct Queue* queue = queueInit();
	queuePush(queue, 5);
	printf("Queue Head: %d\n", queue->head->data);
	printf("Queue is empty: %s\n", queueIsEmpty(queue)==0 ? "false": "true");
	printf("Queue size: %d\n", queueSize(queue));

	for(int i = 0; i < 10; i++){
		queuePush(queue, i);
	}
	printf("Queue Head: %d\n", queue->head->data);
	printf("Queue Pop: %d\n", queuePop(queue));
	printf("Queue size: %d\n", queueSize(queue));
	printf("Queue Head: %d\n", queue->head->data);
	printf("Queue Peek: %d\n", queuePeek(queue));
	printf("Queue Head->next: %d\n", queue->head->next->data);

	printf("Queue Print: \n");
	queuePrint(queue);
	
	// clear queue
	queueClear(queue);

	return 0;
}
