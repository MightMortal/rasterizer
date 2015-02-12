#include "list.h"
#include <stdlib.h>

typedef struct TDYN_LIST_ELEMENT {
	DynListElement data;
	struct TDYN_LIST_ELEMENT* next;
	struct TDYN_LIST_ELEMENT* prev;
} DynListElementS;

typedef struct TDYN_LIST {
	DynListElementS* head;
	DynListElementS* tail;
	uint size;
} DynListS;

DynList dynlist_init() {
	DynListS* list = (DynListS*)malloc(sizeof(DynListS));
	list->head = NULL;
	list->size = 0;
	list->tail = NULL;
	return list;
}

void dynlist_destroy(DynList list_descriptor) {
	DynListS* list = (DynListS*) list_descriptor;
	dynlist_clear(list_descriptor);
	free(list);
}

void dynlist_clear(DynList list_descriptor) {
	DynListS* list = (DynListS*)list_descriptor;
	DynListElementS* element = list->head;
	while (element) {
		DynListElementS* prev = element;
		element = element->next;
		free(prev->data);
		free(prev);
	}
	list->head = NULL;
	list->size = 0;
}

DynListElement dynlist_get_element(DynList list_descriptor, uint index) {
	DynListS* list = (DynListS*)list_descriptor;
	if (index >= list->size) 
		return NULL;
	DynListElementS* element = list->head;
	for (uint i = 0; i < index; ++i) {
		element = element->next;
	}
	return element->data;
}

uint dynlist_size(DynList list_descriptor) {
	DynListS* list = (DynListS*)list_descriptor;
	return list->size;
}

void dynlist_set_element(DynList list_descriptor, uint index, DynListElement new_element) {
	DynListS* list = (DynListS*)list_descriptor;
	if (index >= list->size)
		return; // TODO: Write error
	DynListElementS* element = list->head;
	for (uint i = 0; i < index; ++i) {
		element = element->next;
	}
	element->data = new_element;
}

void dynlist_push_back(DynList list_descriptor, DynListElement new_element) {
	DynListS* list = (DynListS*)list_descriptor;
	DynListElementS* element = list->tail;

	DynListElementS* new_elementS = (DynListElementS*)malloc(sizeof(DynListElementS));
	new_elementS->data = new_element;
	new_elementS->next = NULL;
	new_elementS->prev = NULL;

	if (element) {
		element->next = new_elementS;
		new_elementS->prev = element;
	} else {
		list->tail = new_elementS;
		list->head = new_elementS;
	}
	list->tail = new_elementS;
	list->size++;
}

void dynlist_remove(DynList list_descriptor, uint index) {
	DynListS* list = (DynListS*)list_descriptor;
	if (index >= list->size)
		return; // TODO: Write error
	DynListElementS* for_delete = NULL;
	if (index == 0) { // Delete head
		for_delete = list->head;
		list->head = for_delete->next;
		list->head->prev = NULL;
	} else if (index == list->size - 1) {
		for_delete = list->tail;
		list->tail = for_delete->prev;
		list->tail->next = NULL;
	} else {
		DynListElementS* prev_element = list->head;
		for (uint i = 0; i < index - 1; ++i) {
			prev_element = prev_element->next;
		}
		for_delete = prev_element->next;
		for_delete->prev->next = for_delete->next;
		for_delete->next->prev = for_delete->prev;
	}
	free(for_delete->data);
	free(for_delete);
	list->size--;
}
