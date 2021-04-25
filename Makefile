DYNAMIC_ARRAY = src/01_dynamic_array/unit_test
LINKED_LIST = src/02_linked_list/unit_test
STACK = src/03_stack/unit_test
QUEUE = src/04_queue/unit_test

all: default

default: 
	@echo "Unity started..."
	@echo "\n"

	@echo "DYNAMIC_ARRAY_TEST"
	@cd $(DYNAMIC_ARRAY) && $(MAKE)
	@echo "\n"
	
	@echo "LINKED_LIST_TEST"
	@cd $(LINKED_LIST) && $(MAKE)
	@echo "\n"
	
	@echo "STACK_TEST"
	@cd $(STACK) && $(MAKE)
	@echo "\n"
	
	@echo "QUEUE_TEST"
	@cd $(QUEUE) && $(MAKE)
	@echo "\n"
