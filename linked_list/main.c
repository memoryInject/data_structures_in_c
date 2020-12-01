#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkedList.h"

// Driver test code
int main(int argc, char* argv[])
{
	//struct List newList;
	struct List* list;
	list = (struct List*)malloc(sizeof(struct List));
	//list = &newList;
	
	listInit(list, true);
	listAdd(list, 5);
	listAdd(list, 6);
	listAddFirst(list, 3);

	// Fill up the list
	for(int i = 0; i<10; i++){
		listPush(list, i+10);
	}

	printf("size: %d\n", list->size);
	printf("data head next: %d\n", list->head->next->data);
	printf("data peak first: %d\n", listPeekFirst(list));
	printf("data peak last: %d\n", listPeekLast(list));

	listRemoveFirst(list);
	printf("data peak first: %d\n", listPeekFirst(list));

	listPush(list, 7);
	printf("list pop: %d\n", listPop(list));
	printf("data peak last: %d\n", listPeekLast(list));
	printf("list size: %d\n", list->size);
	printf("remove at index 2: %d\n", listRemoveAt(list, 2));
	printf("remove at index 1: %d\n", listRemoveAt(list, 1));
	printf("remove data 14: %s\n", (listRemoveData(list, 14) == 1 ? "true" : "false"));
	printf("Find the index of data 15: %d\n", listIndexOf(list, 15));
	printf("list contains data 16: %s\n", (listContains(list, 16) == 1 ? "true" : "false"));
	
	printf("\nPrint linked list: ");
	listPrint(list);

	listReverse(list);
	printf("Reversed linked list: ");
	listPrint(list);

	listClear(list);
	free(list);
	
	return 0;

}
