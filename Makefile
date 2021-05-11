DYNAMIC_ARRAY = src/01_dynamic_array/unit_test
LINKED_LIST = src/02_linked_list/unit_test
STACK = src/03_stack/unit_test
QUEUE = src/04_queue/unit_test
PRIORITY_QUEUE_BINARY_HEAP = src/05_priority_queue/binary_heap/unit_test
PRIORITY_QUEUE_INDEXED_BINARY_HEAP = src/05_priority_queue/indexed_binary_heap/unit_test
UNION_FIND = src/06_union_find/unit_test
BINARY_SEARCH_TREE = src/07_binary_search_tree/unit_test
HASH_TABLE_SEPERATE_CHAINING = src/08_hash_table/hash_table_separate_chaining/unit_test
HASH_TABLE_OPEN_ADDRESSING = src/08_hash_table/hash_table_open_addressing/unit_test
FENWICK_TREE_RANG_QUERY_POINT_UPDATE = src/09_fenwick_tree/fenwickTree_rangeQuery_pointUpdate/unit_test
FENWICK_TREE_RANG_UPDATE_POINT_QUERY = src/09_fenwick_tree/fenwickTree_rangeUpdate_pointQuery/unit_test
SUFFIX_ARRAY = src/10_suffix_array/unit_test

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
	
	@echo "PRIORITY_QUEUE_BINARY_HEAP_TEST"
	@cd $(PRIORITY_QUEUE_BINARY_HEAP) && $(MAKE)
	@echo "\n"

	@echo "PRIORITY_QUEUE_INDEXED_BINARY_HEAP_TEST"
	@cd $(PRIORITY_QUEUE_INDEXED_BINARY_HEAP) && $(MAKE)
	@echo "\n"

	@echo "UNION_FIND_TEST"
	@cd $(UNION_FIND) && $(MAKE)
	@echo "\n"

	@echo "BINARY_SEARCH_TREE_TEST"
	@cd $(BINARY_SEARCH_TREE) && $(MAKE)
	@echo "\n"

	@echo "HASH_TABLE_SEPERATE_CHAINING_TEST"
	@cd $(HASH_TABLE_SEPERATE_CHAINING) && $(MAKE)
	@echo "\n"

	@echo "HASH_TABLE_OPEN_ADDRESSING_TEST"
	@cd $(HASH_TABLE_OPEN_ADDRESSING) && $(MAKE)
	@echo "\n"

	@echo "FENWICK_TREE_RANG_QUERY_POINT_UPDATE_TEST"
	@cd $(FENWICK_TREE_RANG_QUERY_POINT_UPDATE) && $(MAKE)
	@echo "\n"

	@echo "FENWICK_TREE_RANG_UPDATE_POINT_QUERY_TEST"
	@cd $(FENWICK_TREE_RANG_UPDATE_POINT_QUERY) && $(MAKE)
	@echo "\n"

	@echo "SUFFIX_ARRAY_TEST"
	@cd $(SUFFIX_ARRAY) && $(MAKE)
	@echo "\n"

